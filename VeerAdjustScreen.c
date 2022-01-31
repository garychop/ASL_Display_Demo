//*****************************************************************************
// Filename: VeerAdjustScreen.cpp
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

UINT g_NeutralDAC_RangeValue = 410;
UINT g_NeutralDAC_Constant = 2048;
UINT g_NeutralDAC_Value = 2020;

char g_SliderValue[20];

//*************************************************************************************
// Function Name: VeerAdjust_Screen_event_handler
//
// Description: These functions support the Veer Adjustment feature.
//
//*************************************************************************************

int g_MyValues[20];

VOID VeerAdjust_Screen_draw_function (GX_WINDOW *window)
{
	gx_window_draw(window);
}

UINT VeerSlider_event_function(GX_PIXELMAP_SLIDER *widget, GX_EVENT *event_ptr)
{
	int myNewVal, myOffset;
	int totalSteps;
	int increment;

    gx_pixelmap_slider_event_process(widget, event_ptr);

	switch (event_ptr->gx_event_type)
	{
	case GX_EVENT_SHOW:
		break;
	case GX_EVENT_PEN_DOWN:
	case GX_EVENT_PEN_DRAG:
	case GX_EVENT_PEN_UP:
		myNewVal = widget->gx_slider_info.gx_slider_info_current_val;
		totalSteps = widget->gx_slider_info.gx_slider_info_max_val - widget->gx_slider_info.gx_slider_info_min_val;
		myNewVal = myNewVal - (totalSteps / 2);

		increment = g_NeutralDAC_RangeValue / totalSteps / 2;	// This is how many going Plus and Minus.
		myOffset = myNewVal * increment;
		myNewVal = g_NeutralDAC_Constant + myOffset;
		g_NeutralDAC_Value = myNewVal;
		break;
	default:
		break;
	} // end swtich

	return GX_SUCCESS;
}

VOID Slider_Draw_Function (GX_PIXELMAP_SLIDER *slider)
{
	int myVal, totalSteps;
	int increment;

	totalSteps = slider->gx_slider_info.gx_slider_info_max_val - slider->gx_slider_info.gx_slider_info_min_val;

	increment = g_NeutralDAC_RangeValue / totalSteps / 2;	// This is how many going Plus and Minus.
	myVal = (int)(g_NeutralDAC_Value - g_NeutralDAC_Constant) / increment;

	slider->gx_slider_info.gx_slider_info_current_val = myVal + (totalSteps / 2);
	gx_pixelmap_slider_draw (slider);
	
	myVal = slider->gx_slider_info.gx_slider_info_current_val - (slider->gx_slider_info.gx_slider_info_max_val/2);
// For some reason, the following statement causes a program crash so I went back to the simple sprintf function.
//	sprintf_s (g_SliderValue, sizeof (g_SliderValue), "%2d%", myVal);
	sprintf (g_SliderValue, "%2d%", myVal);

	gx_text_button_text_set (&VeerAdjustScreen.VeerAdjustScreen_SliderValue_Button, g_SliderValue);
}

UINT VeerAdjust_Screen_event_handler (GX_WINDOW *window, GX_EVENT *event_ptr)
{
	switch (event_ptr->gx_event_type)
	{
	case GX_SIGNAL(OK_BTN_ID, GX_EVENT_CLICKED):
        screen_toggle((GX_WINDOW *)&PerformanceSelectionScreen, window);
		break;

	case GX_EVENT_PEN_DOWN:
		break;

	case GX_EVENT_PEN_UP:
		break;
	}

    gx_window_event_process(window, event_ptr);

	return GX_SUCCESS;
}







