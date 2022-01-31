//*****************************************************************************
// Filename: SetPadTypeScreen.cpp
//
// Date: Aug 28, 2020
//
// Author: G. Chopcinski, Kg Solutions, LLC
// 
//*****************************************************************************

#include "ASL165_System.h"
#include "PadInfo.h"

//*************************************************************************************
// Local/Global variables
//*************************************************************************************


//*************************************************************************************
// Function Name: SetPadTypeScreen_event_process
//
// Description: This handles the Set Pad Screen messages
//
//*************************************************************************************

UINT SetPadTypeScreen_event_process (GX_WINDOW *window, GX_EVENT *event_ptr)
{
	UINT myErr = -1;

	switch (event_ptr->gx_event_type)
	{
	case GX_EVENT_SHOW:
		g_ChangeScreen_WIP = FALSE;
		if (g_PadSettings[LEFT_PAD].m_PadType)	// Digital?
		{
			gx_widget_hide ((GX_WIDGET*) &SetPadTypeScreen.SetPadTypeScreen_LeftPadProportional_Button);
			gx_widget_show ((GX_WIDGET*) &SetPadTypeScreen.SetPadTypeScreen_LeftPadDigital_Button);
		}
		else
		{
			gx_widget_show ((GX_WIDGET*) &SetPadTypeScreen.SetPadTypeScreen_LeftPadProportional_Button);
			gx_widget_hide ((GX_WIDGET*) &SetPadTypeScreen.SetPadTypeScreen_LeftPadDigital_Button);
		}
		if (g_PadSettings[RIGHT_PAD].m_PadType)	// Digital?
		{
			gx_widget_hide ((GX_WIDGET*) &SetPadTypeScreen.SetPadTypeScreen_RightPadProportional_Button);
			gx_widget_show ((GX_WIDGET*) &SetPadTypeScreen.SetPadTypeScreen_RightPadDigital_Button);
		}
		else
		{
			gx_widget_show ((GX_WIDGET*) &SetPadTypeScreen.SetPadTypeScreen_RightPadProportional_Button);
			gx_widget_hide ((GX_WIDGET*) &SetPadTypeScreen.SetPadTypeScreen_RightPadDigital_Button);
		}
		if (g_PadSettings[CENTER_PAD].m_PadType)	// Digital?
		{
			gx_widget_hide ((GX_WIDGET*) &SetPadTypeScreen.SetPadTypeScreen_CenterPadProportional_Button);
			gx_widget_show ((GX_WIDGET*) &SetPadTypeScreen.SetPadTypeScreen_CenterPadDigital_Button);
		}
		else
		{
			gx_widget_show ((GX_WIDGET*) &SetPadTypeScreen.SetPadTypeScreen_CenterPadProportional_Button);
			gx_widget_hide ((GX_WIDGET*) &SetPadTypeScreen.SetPadTypeScreen_CenterPadDigital_Button);
		}
		break;

	case GX_SIGNAL(OK_BTN_ID, GX_EVENT_CLICKED):
        screen_toggle((GX_WINDOW *)&PadOptionsSettingsScreen, window);
		break;

	case GX_SIGNAL(RIGHT_PAD_DIGITAL_BTN_ID, GX_EVENT_CLICKED):
		if (!g_ChangeScreen_WIP)
		{
			myErr = gx_widget_hide ((GX_WIDGET*) &SetPadTypeScreen.SetPadTypeScreen_RightPadDigital_Button);
			myErr = gx_widget_show ((GX_WIDGET*) &SetPadTypeScreen.SetPadTypeScreen_RightPadProportional_Button);
			g_PadSettings[RIGHT_PAD].m_PadType = PROPORTIONAL_PADTYPE;
		}
		break;
	case GX_SIGNAL(RIGHT_PAD_PROPORTIONAL_BTN_ID, GX_EVENT_CLICKED):
		if (!g_ChangeScreen_WIP)
		{
			myErr = gx_widget_hide ((GX_WIDGET*) &SetPadTypeScreen.SetPadTypeScreen_RightPadProportional_Button);
			myErr = gx_widget_show ((GX_WIDGET*) &SetPadTypeScreen.SetPadTypeScreen_RightPadDigital_Button);
			g_PadSettings[RIGHT_PAD].m_PadType = DIGITAL_PADTYPE;
		}
		break;
	case GX_SIGNAL(LEFT_PAD_DIGITAL_BTN_ID, GX_EVENT_CLICKED):
		if (!g_ChangeScreen_WIP)
		{
			myErr = gx_widget_hide ((GX_WIDGET*) &SetPadTypeScreen.SetPadTypeScreen_LeftPadDigital_Button);
			myErr = gx_widget_show ((GX_WIDGET*) &SetPadTypeScreen.SetPadTypeScreen_LeftPadProportional_Button);
			g_PadSettings[LEFT_PAD].m_PadType = PROPORTIONAL_PADTYPE;
		}
		break;
	case GX_SIGNAL(LEFT_PAD_PROPORTIONAL_BTN_ID, GX_EVENT_CLICKED):
		if (!g_ChangeScreen_WIP)
		{
			myErr = gx_widget_hide ((GX_WIDGET*) &SetPadTypeScreen.SetPadTypeScreen_LeftPadProportional_Button);
			myErr = gx_widget_show ((GX_WIDGET*) &SetPadTypeScreen.SetPadTypeScreen_LeftPadDigital_Button);
			g_PadSettings[LEFT_PAD].m_PadType = DIGITAL_PADTYPE;
		}
		break;
	case GX_SIGNAL(CENTER_PAD_DIGITAL_BTN_ID, GX_EVENT_CLICKED):
		if (!g_ChangeScreen_WIP)
		{
			myErr = gx_widget_hide ((GX_WIDGET*) &SetPadTypeScreen.SetPadTypeScreen_CenterPadDigital_Button);
			myErr = gx_widget_show ((GX_WIDGET*) &SetPadTypeScreen.SetPadTypeScreen_CenterPadProportional_Button);
			g_PadSettings[CENTER_PAD].m_PadType = PROPORTIONAL_PADTYPE;
		}
		break;
	case GX_SIGNAL(CENTER_PAD_PROPORTIONAL_BTN_ID, GX_EVENT_CLICKED):
		if (!g_ChangeScreen_WIP)
		{
			myErr = gx_widget_hide ((GX_WIDGET*) &SetPadTypeScreen.SetPadTypeScreen_CenterPadProportional_Button);
			myErr = gx_widget_show ((GX_WIDGET*) &SetPadTypeScreen.SetPadTypeScreen_CenterPadDigital_Button);
			g_PadSettings[CENTER_PAD].m_PadType = DIGITAL_PADTYPE;
		}
		break;

	case GX_EVENT_TIMER:
        if (event_ptr->gx_event_payload.gx_event_timer_id == CALIBRATION_TIMER_ID)
		{
			gx_system_timer_stop(window, CALIBRATION_TIMER_ID);
	        screen_toggle((GX_WINDOW *)&PadCalibrationScreen, window);
			g_ChangeScreen_WIP = TRUE;
		}
		break;
	case GX_EVENT_PEN_DOWN:	// We are going to determine if the Up or Down arrow buttons have been held for a
							// ... long time (2 seconds) and goto calibration if so.

		if (event_ptr->gx_event_target->gx_widget_name == "CenterPadProportional_Button")
		{
			g_CalibrationPadNumber = CENTER_PAD; 
			gx_system_timer_start(window, CALIBRATION_TIMER_ID, 100, 0);
		}
		else if (event_ptr->gx_event_target->gx_widget_name == "LeftPadProportional_Button")
		{
			g_CalibrationPadNumber = LEFT_PAD; 
			gx_system_timer_start(window, CALIBRATION_TIMER_ID, 100, 0);
		}
		else if (event_ptr->gx_event_target->gx_widget_name == "RightPadProportional_Button")
		{
			g_CalibrationPadNumber = RIGHT_PAD; 
			gx_system_timer_start(window, CALIBRATION_TIMER_ID, 100, 0);
		}
		break;
	case GX_EVENT_PEN_UP:
			gx_system_timer_stop(window, CALIBRATION_TIMER_ID);
		break;

	}

    myErr = gx_window_event_process(window, event_ptr);

	return myErr;
}












