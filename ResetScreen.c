//*****************************************************************************
// Filename: ResetScreen.cpp
//
// Date: Aug 28, 2020
//
// Author: G. Chopcinski, Kg Solutions, LLC
// 
//*****************************************************************************

#include "ASL165_System.h"
#include "PadInfo.h"

//*************************************************************************************
// Local Macros
//*************************************************************************************

//*************************************************************************************
// External References
//*************************************************************************************

//*************************************************************************************
// Local/Global variables
//*************************************************************************************

//*************************************************************************************
// Forward Declarations
//*************************************************************************************


//*************************************************************************************
// Function Name: ResetScreen_event_process
//
// Description: This handles the Diagnostic Screen messages
//
//*************************************************************************************

UINT ResetScreen_event_process(GX_WINDOW *window, GX_EVENT *event_ptr)
{

    switch (event_ptr->gx_event_type)
    {
	case GX_SIGNAL(OK_BTN_ID, GX_EVENT_CLICKED):
        screen_toggle((GX_WINDOW *)&MoreSelectionScreen, window);
		break;

	case GX_SIGNAL(CONTINUE_BTN_ID, GX_EVENT_CLICKED):
        screen_toggle((GX_WINDOW *)&ResetFinishScreen, window);
		break;
    } // end switch
    return gx_window_event_process(window, event_ptr);
}

//*************************************************************************************

UINT ResetFinishScreen_event_process(GX_WINDOW *window, GX_EVENT *event_ptr)
{
	switch (event_ptr->gx_event_type)
    {
	case GX_SIGNAL(OK_BTN_ID, GX_EVENT_CLICKED):
        screen_toggle((GX_WINDOW *)&HHP_Start_Screen, window);
		break;

    } // end switch
    return gx_window_event_process(window, event_ptr);
}














