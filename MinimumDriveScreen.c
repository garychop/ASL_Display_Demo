//*****************************************************************************
// Filename: MinimumDriveScreen.cpp
//
// Date: Aug 28, 2020
//
// Author: G. Chopcinski, Kg Solutions, LLC
// 
//*****************************************************************************

#include "ASL165_System.h"
#include "PadInfo.h"

//*************************************************************************************
// Function Name: MinimumDriveScreen_event_process
//
// Description: This dispatches the Pad Option Settings Screen messages
//
//*************************************************************************************

UINT MinimumDriveScreen_event_process (GX_WINDOW *window, GX_EVENT *event_ptr)
{
	UINT myErr;

	switch (event_ptr->gx_event_type)
	{
	case GX_EVENT_SHOW:
		if (g_HA_EEPROM_Version >= 5)		// Firmware version 5 uses 3 drive offset values.
		{
		}
		else	// Old school, Only one value is shown since the ASL110 firmware supports only one Minimum Drive value.
		{
			gx_widget_hide (&MinimumDriveScreen.MinimumDriveScreen_RightPadPercentage_Button);	// Hide the right pad button
			gx_widget_hide (&MinimumDriveScreen.MinimumDriveScreen_LeftPadPercentage_Button);	// Hide the Left pad button
			gx_widget_hide (&MinimumDriveScreen.MinimumDriveScreen_Prompt_ForEachPad);			// Hide the "FOR EACH PAD" prompt
			// Move the "SET MINIMUM DRIVE SPEED" prompt down for better appearance.
			MinimumDriveScreen.MinimumDriveScreen_Prompt_SetMinimumSpeed.gx_widget_size.gx_rectangle_top += 10;
			MinimumDriveScreen.MinimumDriveScreen_Prompt_SetMinimumSpeed.gx_widget_size.gx_rectangle_bottom += 10;
			// Move the Center Pad button to the middle, upper part of the screen.
			MinimumDriveScreen.MinimumDriveScreen_CenterPadPercentage_Button.gx_widget_size.gx_rectangle_left = 116;
			MinimumDriveScreen.MinimumDriveScreen_CenterPadPercentage_Button.gx_widget_size.gx_rectangle_right = 116 + 80; // left + width
			MinimumDriveScreen.MinimumDriveScreen_CenterPadPercentage_Button.gx_widget_size.gx_rectangle_top = 55;
			MinimumDriveScreen.MinimumDriveScreen_CenterPadPercentage_Button.gx_widget_size.gx_rectangle_bottom = 55 + 64; // top + height
		}
		break;

	case GX_SIGNAL(OK_BTN_ID, GX_EVENT_CLICKED):
        screen_toggle((GX_WINDOW *)&PadOptionsSettingsScreen, window);
		break;

	case GX_SIGNAL (CENTER_PAD_PERCENTAGE_BTN_ID, GX_EVENT_CLICKED):
		if (g_PadSettings[CENTER_PAD].m_MinimumDriveValue >= MAXIMUM_DRIVE_SPEED)
		{
			g_PadSettings[CENTER_PAD].m_MinimumDriveValue = 0;
			strcpy_s (g_PadSettings[CENTER_PAD].m_MinimuDriveString, sizeof (g_PadSettings[CENTER_PAD].m_MinimuDriveString), "OFF");
		}
		else
		{
			g_PadSettings[CENTER_PAD].m_MinimumDriveValue += 5;
			sprintf_s (g_PadSettings[CENTER_PAD].m_MinimuDriveString, sizeof (g_PadSettings[CENTER_PAD].m_MinimuDriveString), "%d%%", g_PadSettings[CENTER_PAD].m_MinimumDriveValue);
		}
		gx_text_button_text_set (&MinimumDriveScreen.MinimumDriveScreen_CenterPadPercentage_Button, g_PadSettings[CENTER_PAD].m_MinimuDriveString);
		break;

	case GX_SIGNAL (LEFT_PAD_PERCENTAGE_BTN_ID, GX_EVENT_CLICKED):
		if (g_PadSettings[LEFT_PAD].m_MinimumDriveValue >= MAXIMUM_DRIVE_SPEED)
		{
			g_PadSettings[LEFT_PAD].m_MinimumDriveValue = 0;
			strcpy_s (g_PadSettings[LEFT_PAD].m_MinimuDriveString, sizeof (g_PadSettings[CENTER_PAD].m_MinimuDriveString), "OFF");
		}
		else
		{
			g_PadSettings[LEFT_PAD].m_MinimumDriveValue += 5;
			sprintf_s (g_PadSettings[LEFT_PAD].m_MinimuDriveString, sizeof (g_PadSettings[LEFT_PAD].m_MinimuDriveString), "%d%%", g_PadSettings[LEFT_PAD].m_MinimumDriveValue);
		}
		gx_text_button_text_set (&MinimumDriveScreen.MinimumDriveScreen_LeftPadPercentage_Button, g_PadSettings[LEFT_PAD].m_MinimuDriveString);
		break;

	case GX_SIGNAL (RIGHT_PAD_PERCENTAGE_BTN_ID, GX_EVENT_CLICKED):
		if (g_PadSettings[RIGHT_PAD].m_MinimumDriveValue >= MAXIMUM_DRIVE_SPEED)
		{
			g_PadSettings[RIGHT_PAD].m_MinimumDriveValue = 0;
			strcpy_s (g_PadSettings[RIGHT_PAD].m_MinimuDriveString, sizeof (g_PadSettings[RIGHT_PAD].m_MinimuDriveString),  "OFF");
		}
		else
		{
			g_PadSettings[RIGHT_PAD].m_MinimumDriveValue += 5;
			sprintf_s (g_PadSettings[RIGHT_PAD].m_MinimuDriveString, sizeof (g_PadSettings[RIGHT_PAD].m_MinimuDriveString), "%d%%", g_PadSettings[RIGHT_PAD].m_MinimumDriveValue);
		}
		gx_text_button_text_set (&MinimumDriveScreen.MinimumDriveScreen_RightPadPercentage_Button, g_PadSettings[RIGHT_PAD].m_MinimuDriveString);
		break;

	} // end switch

    myErr = gx_window_event_process(window, event_ptr);

	return GX_SUCCESS;
}







