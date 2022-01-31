//*****************************************************************************
// Filename: StartupScreen.cpp
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
// Function Name: StartupScreen_event_handler
// 
//*************************************************************************************

VOID StartScreen_draw_function (GX_WINDOW *window)
{
//	UINT myErr;
//	char *myString;

//	myErr = gx_prompt_text_get ((GX_PROMPT*)&StartupScreen.StartupScreen_StatusPrompt, &myString);
//	myString = "Starting...";
//	myErr = gx_prompt_text_set (&StartupScreen.StartupScreen_StatusPrompt, myString);
//	myErr = gx_prompt_text_color_set ((GX_PROMPT*) &StartupScreen.StartupScreen_StatusPrompt, GX_COLOR_ID_MAROON, GX_COLOR_ID_MAROON, GX_COLOR_ID_MAROON);

	gx_window_draw(window);
}

UINT StartupScreen_event_handler (GX_WINDOW *widget, GX_EVENT *event_ptr)
{
	UINT myErr;

    myErr = gx_window_event_process(widget, event_ptr);
	
	return GX_SUCCESS;
}



