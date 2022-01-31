//*****************************************************************************
// Filename: UserSettingsScreen.cpp
//
// Date: Aug 28, 2020
//
// Author: G. Chopcinski, Kg Solutions, LLC
// 
//*****************************************************************************

#include "ASL165_System.h"

//*************************************************************************************
// Local/Global variables
//*************************************************************************************

char g_TimeoutValueString[8] = "OFF";

//*************************************************************************************
// This function handles the callbacks that support the User Selection Screen.
//*************************************************************************************

UINT UserSettingsScreen_event_process (GX_WINDOW *window, GX_EVENT *event_ptr)
{
	UINT myErr = -1;
    char tmpChar[8];
	USHORT lineNumber, featureCount;

	switch (event_ptr->gx_event_type)
	{
	case GX_EVENT_SHOW:
		if (g_ClicksActive)
		{
			gx_button_select ((GX_BUTTON*) &UserSettingsScreen.UserSettingsScreen_ClicksToggleBtn);
		}
		// Power Up in Idle
		if (g_PowerUpInIdle)    // If powering up in idle state is enable
		{
			gx_button_select ((GX_BUTTON*) &UserSettingsScreen.UserSettingsScreen_PowerUpToggleBtn);
		}
		// RNet Enabled setting
		if (g_RNet_Active)
		{
			gx_button_select ((GX_BUTTON*) &UserSettingsScreen.UserSettingsScreen_RNET_ToggleBtn);
		}
		// Mode Switch Reverse/Pin5 setting
		if (g_Mode_Switch_Schema == MODE_SWITCH_REVERSE)
		{
			gx_button_select ((GX_BUTTON*) &UserSettingsScreen.UserSettingsScreen_ModeSwitchSchema_ToggleBtn);
		}
		// Populate the Timeout button with the current setting or "OFF".
		if (g_TimeoutValue == 0)
			strcpy_s (g_TimeoutValueString, sizeof (g_TimeoutValueString), "OFF");
		else
		{
			// sprintf_s (g_TimeoutValueString, "%1.1g", (float) (g_TimeoutValue / 10.0f));
			// Floating point doesn't work for some odd reason.
			// I'm doing a hack to display the value in a X.X format.
			sprintf_s (g_TimeoutValueString, sizeof (g_TimeoutValueString), "%d.", g_TimeoutValue / 10);
			sprintf_s (tmpChar, sizeof (tmpChar), "%d", g_TimeoutValue % 10);
			strcat_s (g_TimeoutValueString, sizeof (g_TimeoutValueString), tmpChar);
		}
		gx_text_button_text_set (&UserSettingsScreen.UserSettingsScreen_Timeout_Button, g_TimeoutValueString);
		break;

	case GX_SIGNAL(OK_BTN_ID, GX_EVENT_CLICKED):
        screen_toggle((GX_WINDOW *)&UserSelectionScreen, window);
		// Adjust available features based upon RNet setting.
		if (g_RNet_Active)
		{
		    g_MainScreenFeatureInfo[RNET_SLEEP_FEATURE_ID].m_Available = TRUE;
		    g_MainScreenFeatureInfo[RNET_SEATING_ID].m_Available = TRUE;
		}
		else
		{
		    g_MainScreenFeatureInfo[RNET_SLEEP_FEATURE_ID].m_Available = FALSE;
		    g_MainScreenFeatureInfo[RNET_SEATING_ID].m_Available = FALSE;
		}
		break;

	//----------------------------------------------------------
	// CLICK toggle button processing
	case GX_SIGNAL(CLICKS_TOGGLE_BTN, GX_EVENT_TOGGLE_ON):
		g_ClicksActive = TRUE;
		break;
	case GX_SIGNAL(CLICKS_TOGGLE_BTN, GX_EVENT_TOGGLE_OFF):
		g_ClicksActive = FALSE;
		break;

	//----------------------------------------------------------
	// Power Up in IDLE toggle button
	case GX_SIGNAL(POWER_UP_TOGGLE_BTN, GX_EVENT_TOGGLE_ON):
		g_PowerUpInIdle = TRUE;
		break;
	case GX_SIGNAL(POWER_UP_TOGGLE_BTN, GX_EVENT_TOGGLE_OFF):
		g_PowerUpInIdle = FALSE;
		break;

	//----------------------------------------------------------
	// RNet Enable toggle button
	case GX_SIGNAL(RNET_TOGGLE_BTN, GX_EVENT_TOGGLE_ON):
		g_RNet_Active = TRUE;
		break;
	case GX_SIGNAL(RNET_TOGGLE_BTN, GX_EVENT_TOGGLE_OFF):
		g_RNet_Active = FALSE;
		break;

	//----------------------------------------------------------
	// Mode Switch schema selection
	case GX_SIGNAL(MODE_SWITCH_SCHEMA_TOGGLE_BTN, GX_EVENT_TOGGLE_ON):
		g_Mode_Switch_Schema = MODE_SWITCH_REVERSE;
		break;
	case GX_SIGNAL(MODE_SWITCH_SCHEMA_TOGGLE_BTN, GX_EVENT_TOGGLE_OFF):
		g_Mode_Switch_Schema = MODE_SWITCH_PIN5;
		break;

	//----------------------------------------------------------
	case GX_SIGNAL(TIMEOUT_BTN_ID, GX_EVENT_CLICKED):
		switch (g_TimeoutValue)
		{
			case 0:
				g_TimeoutValue = 10;
				break;
			case 10:
			case 15:
			case 20:
			case 25:
				g_TimeoutValue += 5;
				break;
			case 30:
			case 40:
				g_TimeoutValue += 10;
				break;
			case 50:
				g_TimeoutValue = 0;
				break;
		} // end switch
		if (g_TimeoutValue == 0)
			strcpy_s (g_TimeoutValueString, sizeof (g_TimeoutValueString), "OFF");
		else 
			sprintf_s (g_TimeoutValueString, sizeof (g_TimeoutValueString), "%1.1f", (float) (g_TimeoutValue / 10.0));
		gx_text_button_text_set (&UserSettingsScreen.UserSettingsScreen_Timeout_Button, g_TimeoutValueString);
		break;
	}

	    // Adjust available features based upon RNet setting.
    if (g_RNet_Active)
    {
        g_MainScreenFeatureInfo[RNET_SLEEP_FEATURE_ID].m_Available = TRUE;
        g_MainScreenFeatureInfo[RNET_SEATING_ID].m_Available = TRUE;
    }
    else
    {
        g_MainScreenFeatureInfo[RNET_SLEEP_FEATURE_ID].m_Available = FALSE;
        g_MainScreenFeatureInfo[RNET_SEATING_ID].m_Available = FALSE;
    }

    lineNumber = 0;                     // Need to keep track of which line is next.
    for (featureCount = 0; featureCount < NUM_FEATURES; ++featureCount)
    {
        if ((g_MainScreenFeatureInfo[featureCount].m_Enabled) && (g_MainScreenFeatureInfo[featureCount].m_Available))
        {
            g_MainScreenFeatureInfo[featureCount].m_Location = lineNumber;
            ++lineNumber;
        }
        else
        {
            g_MainScreenFeatureInfo[featureCount].m_Location = -1;
        }
    }

    myErr = gx_window_event_process(window, event_ptr);

	return GX_SUCCESS;
}









