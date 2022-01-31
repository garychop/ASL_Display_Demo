//*****************************************************************************
// Filename: DiagnosticScreen.cpp
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

extern GX_RECTANGLE g_HiddenRectangle;

//*************************************************************************************
// Local/Global variables
//*************************************************************************************

//*************************************************************************************
// Forward Declarations
//*************************************************************************************

UINT ShowHidePad (GX_EVENT *event_ptr);

//*************************************************************************************
// Function Name: DiagnosticScreen_event_handler
//
// Description: This handles the Diagnostic Screen messages
//
//*************************************************************************************

UINT DiagnosticScreen_event_handler(GX_WINDOW *window, GX_EVENT *event_ptr)
{
	UINT myError;
	int pads;

    switch (event_ptr->gx_event_type)
    {
	case GX_EVENT_SHOW:
		for (pads = 0; pads < 3; ++pads)
		{
			myError = gx_widget_resize ((GX_WIDGET*) g_PadSettings[pads].m_DiagnosticDigital_Widget, &g_HiddenRectangle);
			myError = gx_widget_resize ((GX_WIDGET*) g_PadSettings[pads].m_DiagnosticProportional_Widget, &g_HiddenRectangle);
			if (g_PadSettings[pads].m_PadDirection == OFF_DIRECTION)
				myError = gx_widget_resize ((GX_WIDGET*)g_PadSettings[pads].m_DiagnosticOff_Widget, &g_PadSettings[pads].m_DiagnosticWidigetLocation);
			else
				myError = gx_widget_resize ((GX_WIDGET*)g_PadSettings[pads].m_DiagnosticOff_Widget, &g_HiddenRectangle);
		}
		break;

	case GX_SIGNAL(OK_BTN_ID, GX_EVENT_CLICKED):
        screen_toggle((GX_WINDOW *)&MoreSelectionScreen, window);
		break;

	case GX_EVENT_PEN_DOWN:
	case GX_EVENT_PEN_UP:
		ShowHidePad (event_ptr);
		break;
    } // end switch
    return gx_window_event_process(window, event_ptr);
}

//*************************************************************************************
// Function Name: ShowHidePad
//
// Description: This functions displays an green-illuminated pad simulating an active pad.
//
//*************************************************************************************

int gFound = 0;

UINT ShowHidePad (GX_EVENT *event_ptr)
{
	UINT myError = GX_SUCCESS;
	int pad;
//	GX_WIDGET *myWidget;
	GX_VALUE xPos, yPos;

	// We can only look at the PEN UP and PEN DOWN events and it only provides 
	if (event_ptr->gx_event_target->gx_widget_first_child == NULL)
		return GX_FAILURE;
	// We are going to identify the "press" pad by its location.
	xPos = event_ptr->gx_event_payload.gx_event_pointdata.gx_point_x;
	yPos = event_ptr->gx_event_payload.gx_event_pointdata.gx_point_y;

	// Now traverse the entire set of widgets for this window looking for the the "Pressed" icon.
	for (pad = 0; pad <= 2; ++pad)
	{
		if ((yPos >= g_PadSettings[pad].m_DiagnosticWidigetLocation.gx_rectangle_top)
			&& (yPos <= g_PadSettings[pad].m_DiagnosticWidigetLocation.gx_rectangle_bottom)
			&& (xPos >= g_PadSettings[pad].m_DiagnosticWidigetLocation.gx_rectangle_left)
			&& (xPos <= g_PadSettings[pad].m_DiagnosticWidigetLocation.gx_rectangle_right))
		{
			// If we got the right pad, then do something.
			if (g_PadSettings[pad].m_PadDirection != OFF_DIRECTION)
			{
				// Determine if we are going to show it or hide it.
				//if (event_ptr->gx_event_type == GX_EVENT_PEN_DOWN)
				{
					// Determine if we show the Proportional (Orange) or Digital (Green)
					if (g_PadSettings[pad].m_PadType == PROPORTIONAL_PADTYPE)
						myError = gx_widget_resize ((GX_WIDGET*)g_PadSettings[pad].m_DiagnosticProportional_Widget , &g_PadSettings[pad].m_DiagnosticWidigetLocation);
					else
						myError = gx_widget_resize ((GX_WIDGET*)g_PadSettings[pad].m_DiagnosticDigital_Widget , &g_PadSettings[pad].m_DiagnosticWidigetLocation);
				}
				//else // PEN UP
				//{
				//	// Now we are going to hide it.
				//	if (g_PadSettings[pad].m_PadType == PROPORTIONAL_PADTYPE)
				//		myError = gx_widget_resize ((GX_WIDGET*)g_PadSettings[pad].m_DiagnosticProportional_Widget , &g_HiddenRectangle);
				//	else
				//		myError = gx_widget_resize ((GX_WIDGET*)g_PadSettings[pad].m_DiagnosticDigital_Widget , &g_HiddenRectangle);
				//}
				++gFound;
			} // endif !OFF
		}
	} // end while
	
	if ((gFound & 1) == 1)
	{
		gx_icon_button_pixelmap_set (&DiagnosticScreen.DiagnosticScreen_UserPort_IconButton, GX_PIXELMAP_ID_RADIOBUTTON_ON);
		gx_icon_button_pixelmap_set (&DiagnosticScreen.DiagnosticScreen_ModePort_IconButton, GX_PIXELMAP_ID_RADIOBUTTON_OFF);
	}
	else
	{
		gx_icon_button_pixelmap_set (&DiagnosticScreen.DiagnosticScreen_UserPort_IconButton, GX_PIXELMAP_ID_RADIOBUTTON_OFF);
		gx_icon_button_pixelmap_set (&DiagnosticScreen.DiagnosticScreen_ModePort_IconButton, GX_PIXELMAP_ID_RADIOBUTTON_ON);
	}
	return (myError);
}














