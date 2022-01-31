//*****************************************************************************
// Filename: PadOptionsSettingScreen.cpp
//
// Date: Aug 28, 2020
//
// Author: G. Chopcinski, Kg Solutions, LLC
// 
//*****************************************************************************

#include "ASL165_System.h"
#include "PadInfo.h"

PAD_INFO_STRUCT g_PadSettings[3];

GX_RECTANGLE g_DiagnosticWidgetLocations[] = {
	{35, 32, 35+62, 32+90},
	{183, 32, 183+62, 32+90},
	{66, 140, 66+145, 140+42}};

//*************************************************************************************
// InitializePadInformation
//*************************************************************************************

VOID InitializePadInformation()
{
	// Populate the default Pad settings.
	g_PadSettings[LEFT_PAD].m_PadDirection = LEFT_DIRECTION;
	g_PadSettings[LEFT_PAD].m_PadType = PROPORTIONAL_PADTYPE;
	g_PadSettings[LEFT_PAD].m_MinimumDriveValue = 20;
	strcpy_s (g_PadSettings[LEFT_PAD].m_MinimuDriveString, sizeof (g_PadSettings[LEFT_PAD].m_MinimuDriveString), "20%");
	g_PadSettings[LEFT_PAD].m_DirectionIcons[OFF_DIRECTION] = &SetPadDirectionScreen.SetPadDirectionScreen_LeftPad_Off_Button;
	g_PadSettings[LEFT_PAD].m_DirectionIcons[RIGHT_DIRECTION] = &SetPadDirectionScreen.SetPadDirectionScreen_LeftPad_RightArrow_Button;
	g_PadSettings[LEFT_PAD].m_DirectionIcons[LEFT_DIRECTION] = &SetPadDirectionScreen.SetPadDirectionScreen_LeftPad_LeftArrow_Button;
	g_PadSettings[LEFT_PAD].m_DirectionIcons[FORWARD_DIRECTION] = &SetPadDirectionScreen.SetPadDirectionScreen_LeftPad_ForwardArrow_Button;
	g_PadSettings[LEFT_PAD].m_PadMinimumCalibrationValue = 2;
	g_PadSettings[LEFT_PAD].m_PadMaximumCalibrationValue = 30;
	g_PadSettings[LEFT_PAD].m_DiagnosticWidigetLocation = g_DiagnosticWidgetLocations[LEFT_PAD];
	g_PadSettings[LEFT_PAD].m_DiagnosticOff_ID = LEFT_PAD_OFF_BTN_ID;
	g_PadSettings[LEFT_PAD].m_DiagnosticDigital_ID = LEFT_PAD_DIGITAL_BTN_ID;
	g_PadSettings[LEFT_PAD].m_DiagnosticProportional_ID = LEFT_PAD_PROP_BTN_ID;
	g_PadSettings[LEFT_PAD].m_DiagnosticOff_Widget = &DiagnosticScreen.DiagnosticScreen_LeftPadOff_Button;
	g_PadSettings[LEFT_PAD].m_DiagnosticProportional_Widget = &DiagnosticScreen.DiagnosticScreen_LeftPadProp_Button;
	g_PadSettings[LEFT_PAD].m_DiagnosticDigital_Widget = &DiagnosticScreen.DiagnosticScreen_LeftPadDigital_Button;

	g_PadSettings[RIGHT_PAD].m_PadDirection = RIGHT_DIRECTION;
	g_PadSettings[RIGHT_PAD].m_PadType = PROPORTIONAL_PADTYPE;
	g_PadSettings[RIGHT_PAD].m_MinimumDriveValue = 20;
	strcpy_s (g_PadSettings[RIGHT_PAD].m_MinimuDriveString, sizeof (g_PadSettings[RIGHT_PAD].m_MinimuDriveString), "20%");
	g_PadSettings[RIGHT_PAD].m_DirectionIcons[OFF_DIRECTION] = &SetPadDirectionScreen.SetPadDirectionScreen_RightPad_Off_Button;
	g_PadSettings[RIGHT_PAD].m_DirectionIcons[RIGHT_DIRECTION] = &SetPadDirectionScreen.SetPadDirectionScreen_RightPad_RightArrow_Button;
	g_PadSettings[RIGHT_PAD].m_DirectionIcons[LEFT_DIRECTION] = &SetPadDirectionScreen.SetPadDirectionScreen_RightPad_LeftArrow_Button;
	g_PadSettings[RIGHT_PAD].m_DirectionIcons[FORWARD_DIRECTION] = &SetPadDirectionScreen.SetPadDirectionScreen_RightPad_ForwardArrow_Button;
	g_PadSettings[RIGHT_PAD].m_PadMinimumCalibrationValue = 2;
	g_PadSettings[RIGHT_PAD].m_PadMaximumCalibrationValue = 30;
	g_PadSettings[RIGHT_PAD].m_DiagnosticWidigetLocation = g_DiagnosticWidgetLocations[RIGHT_PAD];
	g_PadSettings[RIGHT_PAD].m_DiagnosticOff_ID = RIGHT_PAD_OFF_BTN_ID;
	g_PadSettings[RIGHT_PAD].m_DiagnosticDigital_ID = RIGHT_PAD_DIGITAL_BTN_ID;
	g_PadSettings[RIGHT_PAD].m_DiagnosticProportional_ID = RIGHT_PAD_PROP_BTN_ID;
	g_PadSettings[RIGHT_PAD].m_DiagnosticOff_Widget = &DiagnosticScreen.DiagnosticScreen_RightPadOff_Button;
	g_PadSettings[RIGHT_PAD].m_DiagnosticProportional_Widget = &DiagnosticScreen.DiagnosticScreen_RightPadProp_Button;
	g_PadSettings[RIGHT_PAD].m_DiagnosticDigital_Widget = &DiagnosticScreen.DiagnosticScreen_RightPadDigital_Button;

	g_PadSettings[CENTER_PAD].m_PadDirection = FORWARD_DIRECTION;
	g_PadSettings[CENTER_PAD].m_PadType = PROPORTIONAL_PADTYPE;
	g_PadSettings[CENTER_PAD].m_MinimumDriveValue = 20;
	strcpy_s (g_PadSettings[CENTER_PAD].m_MinimuDriveString, sizeof (g_PadSettings[CENTER_PAD].m_MinimuDriveString), "20%");
	g_PadSettings[CENTER_PAD].m_DirectionIcons[OFF_DIRECTION] = &SetPadDirectionScreen.SetPadDirectionScreen_CenterPad_Off_Button;
	g_PadSettings[CENTER_PAD].m_DirectionIcons[RIGHT_DIRECTION] = &SetPadDirectionScreen.SetPadDirectionScreen_CenterPad_RightArrow_Button;
	g_PadSettings[CENTER_PAD].m_DirectionIcons[LEFT_DIRECTION] = &SetPadDirectionScreen.SetPadDirectionScreen_CenterPad_LeftArrow_Button;
	g_PadSettings[CENTER_PAD].m_DirectionIcons[FORWARD_DIRECTION] = &SetPadDirectionScreen.SetPadDirectionScreen_CenterPad_ForwardArrow_Button;
	g_PadSettings[CENTER_PAD].m_PadMinimumCalibrationValue = 2;
	g_PadSettings[CENTER_PAD].m_PadMaximumCalibrationValue = 30;
	g_PadSettings[CENTER_PAD].m_DiagnosticWidigetLocation = g_DiagnosticWidgetLocations[CENTER_PAD];
	g_PadSettings[CENTER_PAD].m_DiagnosticOff_ID = CENTER_PAD_OFF_BTN_ID;
	g_PadSettings[CENTER_PAD].m_DiagnosticDigital_ID = CENTER_PAD_DIGITAL_BTN_ID;
	g_PadSettings[CENTER_PAD].m_DiagnosticProportional_ID = CENTER_PAD_PROP_BTN_ID;
	g_PadSettings[CENTER_PAD].m_DiagnosticOff_Widget = &DiagnosticScreen.DiagnosticScreen_CenterPadOff_Button;
	g_PadSettings[CENTER_PAD].m_DiagnosticProportional_Widget = &DiagnosticScreen.DiagnosticScreen_CenterPadProp_Button;
	g_PadSettings[CENTER_PAD].m_DiagnosticDigital_Widget = &DiagnosticScreen.DiagnosticScreen_CenterPadDigital_Button;
}

//*************************************************************************************
// Function Name: PadOptionsSettingsScreen_event_process
//
// Description: This dispatches the Pad Option Settings Screen messages
//
//*************************************************************************************

UINT PadOptionsSettingsScreen_event_process (GX_WINDOW *window, GX_EVENT *event_ptr)
{
	UINT myErr;

	switch (event_ptr->gx_event_type)
	{
	case GX_SIGNAL(OK_BTN_ID, GX_EVENT_CLICKED):
        screen_toggle((GX_WINDOW *)&HHP_Start_Screen, window);
		break;

	case GX_SIGNAL(PAD_TYPE_BTN_ID, GX_EVENT_CLICKED):
        screen_toggle((GX_WINDOW *)&SetPadTypeScreen, window);
		break;

	case GX_SIGNAL(PAD_DIRECTIONS_BTN_ID, GX_EVENT_CLICKED):
        screen_toggle((GX_WINDOW *)&SetPadDirectionScreen, window);
		break;

	case GX_SIGNAL(MINIMUM_DRIVE_BTN_ID, GX_EVENT_CLICKED):
        screen_toggle((GX_WINDOW *)&MinimumDriveScreen, window);
		break;
	}

    myErr = gx_window_event_process(window, event_ptr);

	return GX_SUCCESS;
}





