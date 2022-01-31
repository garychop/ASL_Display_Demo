//*****************************************************************************
// Filename: HHP_StartScreen.cpp
// Description: This file supports the Programming Main Screen.
//
// Date: Aug 28, 2020
//
// Author: G. Chopcinski, Kg Solutions, LLC
// 
//*****************************************************************************

#include "ASL165_System.h"

//*************************************************************************************

//*************************************************************************************
// Function Name: HHP_Start_Screen_event_process
//
// Description: This handles the Startup Screen messages
//
//*************************************************************************************

UINT HHP_Start_Screen_event_process (GX_WINDOW *window, GX_EVENT *event_ptr)
{
	UINT myErr = -1;

    myErr = gx_window_event_process(window, event_ptr);

	switch (event_ptr->gx_event_type)
	{
	case GX_SIGNAL(PAD_SETTINGS_BTN_ID, GX_EVENT_CLICKED):		// When selected, goto Main Pad Setting scree.
        screen_toggle((GX_WINDOW *)&PadOptionsSettingsScreen, window);
		break;
	case GX_SIGNAL(SETTINGS_BTN_ID, GX_EVENT_CLICKED):
        screen_toggle((GX_WINDOW *)&UserSelectionScreen, window);
		break;
	case GX_SIGNAL(MORE_BTN_ID, GX_EVENT_CLICKED):
        screen_toggle((GX_WINDOW *)&MoreSelectionScreen, window);
		break;
	case GX_SIGNAL(OK_BTN_ID, GX_EVENT_CLICKED):
        screen_toggle((GX_WINDOW *)&MainUserScreen, window);
		break;
	}
	return myErr;
}

