//*****************************************************************************
// Filename: PadCalibrationScreen.cpp
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

#define GRAPH_CENTER_PT_XPOS 139	// From Left of screen
#define GRAPH_CENTER_PT_YPOS 130	// From Top of screen

//*************************************************************************************
// External References
//*************************************************************************************

extern GX_WINDOW *g_CalibrationScreen;
extern int g_PadValue;
extern GX_RECTANGLE g_HiddenRectangle;
extern int g_CalibrationStepNumber;

//*************************************************************************************
// Local/Global variables
//*************************************************************************************

GX_RECTANGLE g_CalibrationPadLocations[] = {
	{36, 32, 36+62, 32+98},			// Left Pad location
	{184, 32, 184+62, 32+98},		// Right Pad location
	{67, 140, 67+145, 140+42},		// Center Pad Location
	{0,0,0,0}};
GX_RECTANGLE g_CalibrationPromptLocations[] = {
	{20, 4, 38+239, 4+33},			// Max and Min Prompt location
	{GRAPH_CENTER_PT_XPOS-25, GRAPH_CENTER_PT_YPOS-26-60, GRAPH_CENTER_PT_XPOS-25+50, GRAPH_CENTER_PT_YPOS-26-60+26},		// Pad Value prompt location
	{0,0,0,0}};

//*************************************************************************************
// Function Name: CalibrationScreen_draw
//
// Description: This callback function is called when Drawing is required by GUIX.
//		This function draws the Guage.
//
//*************************************************************************************

VOID CalibrationScreen_draw (GX_WINDOW *window)
{
	GX_BRUSH *brush;
	GX_BRUSH originalBrush;
	UINT myErr;
	INT raw100, pieSide;

	gx_window_draw(window);

	myErr = gx_context_brush_get(&brush);
	originalBrush = *brush;

	// Draw the background
	brush->gx_brush_line_color = GX_COLOR_LIGHTGRAY;
	brush->gx_brush_width = 3;
	brush->gx_brush_fill_color = GX_COLOR_DARKGRAY;
	myErr = gx_canvas_pie_draw (GRAPH_CENTER_PT_XPOS, GRAPH_CENTER_PT_YPOS, 55, -5, 185);

	// Draw the Pad pie
	if (g_PadValue > 0)				// Anything less than 175-180 is too small of a pie to see; if it's 180 it draws a full circle.
	{
		raw100 = 100 - g_PadValue;
		raw100 *= 100;					// Integer math, yuch!
		raw100 *= 18;					// This converts the percentage to degrees which is a factor of 1.8 
		pieSide = raw100 / 1000;		// This is includes the decimal shift.
		brush->gx_brush_width = 2;
		brush->gx_brush_fill_color = GX_COLOR_GREEN;
		brush->gx_brush_line_color = GX_COLOR_GREEN;
		myErr = gx_canvas_pie_draw (GRAPH_CENTER_PT_XPOS, GRAPH_CENTER_PT_YPOS, 54, pieSide, 180);
	}

	// Draw the minimum pie
	// Calculate the position of the upper side of the pie.
	// The arc is drawn as follows:
	//		 0 degrees = 3:00 clock time
	//		90 degrees = 12:00 noon clock time
	//		180 degrees = 9:00 clock time
	//		270 degrees = 6:00 clock time.
	raw100 = 100 - g_PadSettings[g_CalibrationPadNumber].m_PadMinimumCalibrationValue;
	raw100 *= 100;					// Integer math, yuch!
	raw100 *= 18;					// This converts the percentage to degrees which is a factor of 1.8 
	pieSide = raw100 / 1000;		// This is includes the decimal shift.
	if (pieSide > 175)				// Anything less than 175-180 is too small of a pie to see.
		pieSide = 175;
	brush->gx_brush_fill_color = GX_COLOR_YELLOW;	// Draw in yellow.
	brush->gx_brush_line_color = GX_COLOR_YELLOW;
	//brush->gx_brush_style = GX_BRUSH_OUTLINE;
	brush->gx_brush_width = 1;
	myErr = gx_context_brush_set(brush);		// Not really required. It seems to change the color to yellow without this call.
	myErr = gx_canvas_pie_draw (GRAPH_CENTER_PT_XPOS, GRAPH_CENTER_PT_YPOS, 40, pieSide, 180);

	// Draw the Maximum Pie
	raw100 = 100 - g_PadSettings[g_CalibrationPadNumber].m_PadMaximumCalibrationValue;		// Integer math, yuch!
	raw100 *= 100;
	raw100 *= 18;					// This converts the percentage to degrees which is a factor of 1.8 
	pieSide = raw100 / 1000;		// This is includes the decimal shift.
	if (pieSide < 5)						// Anything less than 0-5 is too small of a sliver to see.
		pieSide = 5;
	brush->gx_brush_fill_color = 0xff6a00;	// Orange
	brush->gx_brush_line_color = 0xff6a00;
	myErr = gx_context_brush_set(brush);		// Not really required. It seems to change the color to yellow without this call.
	myErr = gx_canvas_pie_draw (GRAPH_CENTER_PT_XPOS, GRAPH_CENTER_PT_YPOS, 40, 0, pieSide);

	*brush = originalBrush;
}

//*************************************************************************************
// Function Name: CalibrationScreen_event_process
//
// Description: This handles the Set Pad Screen messages
//
//*************************************************************************************

UINT CalibrationScreen_event_process (GX_WINDOW *window, GX_EVENT *event_ptr)
{
	UINT myErr;

	switch (event_ptr->gx_event_type)
	{
	case GX_EVENT_SHOW:
		myErr = gx_widget_resize ((GX_WIDGET*) &PadCalibrationScreen.PadCalibrationScreen_MaximumInstructionsText, &g_HiddenRectangle);
		myErr = gx_widget_resize ((GX_WIDGET*) &PadCalibrationScreen.PadCalibrationScreen_MinimumInstructionsText, &g_CalibrationPromptLocations[0]);
		g_CalibrationStepNumber = 0;

		myErr = gx_numeric_prompt_value_set (&PadCalibrationScreen.PadCalibrationScreen_Value_Prompt, g_PadSettings[g_CalibrationPadNumber].m_PadMinimumCalibrationValue);

		// show the PAD under calibration and hide the other PADs.
		myErr = gx_widget_resize ((GX_WIDGET*) &PadCalibrationScreen.PadCalibrationScreen_CenterPadON_Button, &g_HiddenRectangle);
		myErr = gx_widget_resize ((GX_WIDGET*) &PadCalibrationScreen.PadCalibrationScreen_LeftPadON_Button, &g_HiddenRectangle);
		myErr = gx_widget_resize ((GX_WIDGET*) &PadCalibrationScreen.PadCalibrationScreen_RightPadON_Button, &g_HiddenRectangle);
		switch (g_CalibrationPadNumber)
		{
		case LEFT_PAD:
			myErr = gx_widget_resize ((GX_WIDGET*) &PadCalibrationScreen.PadCalibrationScreen_LeftPadON_Button, &g_CalibrationPadLocations[0]);
			break;
		case RIGHT_PAD:
			myErr = gx_widget_resize ((GX_WIDGET*) &PadCalibrationScreen.PadCalibrationScreen_RightPadON_Button, &g_CalibrationPadLocations[1]);
			break;
		case CENTER_PAD:
			myErr = gx_widget_resize ((GX_WIDGET*) &PadCalibrationScreen.PadCalibrationScreen_CenterPadON_Button, &g_CalibrationPadLocations[2]);
			break;
		} // end switch (g_CalibrationPadNumber)

		g_CalibrationScreen = window;		// Store for use by screen update process.
		break;

	case GX_SIGNAL(OK_BTN_ID, GX_EVENT_CLICKED):
		if (g_CalibrationStepNumber == 0)			// Let's do maximum calibration
		{
			myErr = gx_widget_resize ((GX_WIDGET*) &PadCalibrationScreen.PadCalibrationScreen_MaximumInstructionsText, &g_CalibrationPromptLocations[0]);
			myErr = gx_widget_resize ((GX_WIDGET*) &PadCalibrationScreen.PadCalibrationScreen_MinimumInstructionsText, &g_HiddenRectangle);
			myErr = gx_numeric_prompt_value_set (&PadCalibrationScreen.PadCalibrationScreen_Value_Prompt, g_PadSettings[g_CalibrationPadNumber].m_PadMaximumCalibrationValue);
			++g_CalibrationStepNumber;
			g_PadValue = 85;
		}
		else if (g_CalibrationStepNumber == 1)
		{
	        screen_toggle((GX_WINDOW *)&SetPadTypeScreen, window);
		}
		break;

	}
    myErr = gx_window_event_process(window, event_ptr);

	return GX_SUCCESS;
}













