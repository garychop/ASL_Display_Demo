//*****************************************************************************
// Filename: AttendantSettingsScreen.cpp
//
// Date: May 16, 2021
//
// Author: G. Chopcinski, Kg Solutions, LLC
// 
//*****************************************************************************

#include "ASL165_System.h"

//*************************************************************************************
// Local/Global variables
//*************************************************************************************

int g_SettingsChanged;

//*************************************************************************************
// Forward Declarations
//*************************************************************************************


//*************************************************************************************
// Function Name: FeatureSettingsScreen_event_process
//
// Description: This handles the Feature Settings Screen messages
//
//*************************************************************************************

UINT AttendantSettingsScreen_event_process (GX_WINDOW *window, GX_EVENT *event_ptr)
{
	UINT myErr = -1;

	switch (event_ptr->gx_event_type)
	{
		case GX_EVENT_SHOW:
			// Active
			if (g_AttendantActive)
				gx_button_select ((GX_BUTTON*) &AttendantSettingsScreen.AttendantSettingsScreen_ActiveToggleBtn);
			else
				gx_button_deselect ((GX_BUTTON*) &AttendantSettingsScreen.AttendantSettingsScreen_ActiveToggleBtn, TRUE);

			if (0)
			{
				gx_button_select ((GX_BUTTON*) &AttendantSettingsScreen.AttendantSettingsScreen_ActiveToggleBtn);
			}

			// Proportional
			if (0)
			{
				gx_button_select ((GX_BUTTON*) &AttendantSettingsScreen.AttendantSettingsScreen_ProportionalToggleBtn);
			}

			// Override
			if (0)
			{
				gx_button_select ((GX_BUTTON*) &AttendantSettingsScreen.AttendantSettingsScreen_OverrideToggleBtn);
			}

			break;

		// Active toggle button processing
		case GX_SIGNAL(ACTIVE_TOGGLE_BTN_ID, GX_EVENT_TOGGLE_ON):
			g_AttendantActive = TRUE;
			break;
		case GX_SIGNAL(ACTIVE_TOGGLE_BTN_ID, GX_EVENT_TOGGLE_OFF):
			g_AttendantActive = FALSE;
			break;

		// Proportional toggle button processing
		case GX_SIGNAL(PROPORTIONAL_TOGGLE_BTN_ID, GX_EVENT_TOGGLE_ON):
			//g_MainScreenFeatureInfo[0].m_Enabled = TRUE;
			//g_SettingsChanged = TRUE;
			break;
		case GX_SIGNAL(PROPORTIONAL_TOGGLE_BTN_ID, GX_EVENT_TOGGLE_OFF):
			//g_MainScreenFeatureInfo[0].m_Enabled = FALSE;
			//g_SettingsChanged = TRUE;
			break;

		// Override toggle button processing
		case GX_SIGNAL(OVERRIDE_TOGGLE_BTN_ID, GX_EVENT_TOGGLE_ON):
			//g_MainScreenFeatureInfo[0].m_Enabled = TRUE;
			//g_SettingsChanged = TRUE;
			break;

		case GX_SIGNAL(OVERRIDE_TOGGLE_BTN_ID, GX_EVENT_TOGGLE_OFF):
			//g_MainScreenFeatureInfo[0].m_Enabled = FALSE;
			//g_SettingsChanged = TRUE;
			break;

		case GX_SIGNAL(OK_BTN_ID, GX_EVENT_CLICKED):
	        screen_toggle((GX_WINDOW *)&PerformanceSelectionScreen, window);
			break;

	} // end switch

    myErr = gx_window_event_process(window, event_ptr);

	return 0;
}











