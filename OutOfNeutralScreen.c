//*****************************************************************************
// Filename: OutOfNeutralScreen.cpp
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
// Function Name: OON_Window_event_function
//
// Description: This handles the Out of nuetral screen messages
//
//*************************************************************************************

UINT OON_Window_event_function (GX_WINDOW *window, GX_EVENT *event_ptr)
{
	gx_window_event_process(window, event_ptr);

	return GX_SUCCESS;
}




