//*****************************************************************************
// Filename: PadDirectionScreen.cpp
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

GX_RECTANGLE g_PadDirectionLocation[] = {
	{28, 55, 28+88, 55+70},
	{205, 55, 205+88, 55+70},
	{116, 150, 116+88, 150+70},
	{0,0,0,0}};

//*************************************************************************************
// Function Name: SetPadDirectionScreen_event_process
//
// Description: This functions process the event of the Set Pad Direction screen.
//
//*************************************************************************************

UINT SetPadDirectionScreen_event_process (GX_WINDOW *window, GX_EVENT *event_ptr)
{
	UINT myErr;
	UINT pads, icons;
	switch (event_ptr->gx_event_type)
	{
	case GX_EVENT_SHOW:
		// Show correct settings for LEFT pad. Off, Right, Forward or Left.
		// First let's hide all choices for all pads.
		for (pads = 0; pads < 3; ++pads)
		{
			for (icons = 0; icons < 4; ++icons)
			{
				myErr = gx_widget_resize ((GX_WIDGET*) g_PadSettings[pads].m_DirectionIcons[icons], &g_HiddenRectangle);
			}
			myErr = gx_widget_resize ((GX_WIDGET*) g_PadSettings[pads].m_DirectionIcons[g_PadSettings[pads].m_PadDirection], &g_PadDirectionLocation[pads]);
		}
		break;

	case GX_SIGNAL(OK_BTN_ID, GX_EVENT_CLICKED):
        screen_toggle((GX_WINDOW *)&PadOptionsSettingsScreen, window);
		break;
	// Process LEFT button pushes
	case GX_SIGNAL(LEFT_PAD_OFF_BTN_ID, GX_EVENT_CLICKED):
		myErr = gx_widget_resize ((GX_WIDGET*) g_PadSettings[LEFT_PAD].m_DirectionIcons[OFF_DIRECTION], &g_HiddenRectangle);
		myErr = gx_widget_resize ((GX_WIDGET*) g_PadSettings[LEFT_PAD].m_DirectionIcons[LEFT_DIRECTION], &g_PadDirectionLocation[LEFT_PAD]);
		g_PadSettings[LEFT_PAD].m_PadDirection = LEFT_DIRECTION;
		break;
	case GX_SIGNAL(LEFT_PAD_LEFT_ARROW_BTN_ID, GX_EVENT_CLICKED):
		myErr = gx_widget_resize ((GX_WIDGET*) g_PadSettings[LEFT_PAD].m_DirectionIcons[LEFT_DIRECTION], &g_HiddenRectangle);
		myErr = gx_widget_resize ((GX_WIDGET*) g_PadSettings[LEFT_PAD].m_DirectionIcons[FORWARD_DIRECTION], &g_PadDirectionLocation[LEFT_PAD]);
		g_PadSettings[LEFT_PAD].m_PadDirection = FORWARD_DIRECTION;
		break;
	case GX_SIGNAL(LEFT_PAD_FORWARD_ARROW_BTN_ID, GX_EVENT_CLICKED):
		myErr = gx_widget_resize ((GX_WIDGET*) g_PadSettings[LEFT_PAD].m_DirectionIcons[FORWARD_DIRECTION], &g_HiddenRectangle);
		myErr = gx_widget_resize ((GX_WIDGET*) g_PadSettings[LEFT_PAD].m_DirectionIcons[RIGHT_DIRECTION], &g_PadDirectionLocation[LEFT_PAD]);
		g_PadSettings[LEFT_PAD].m_PadDirection = RIGHT_DIRECTION;
		break;
	case GX_SIGNAL(LEFT_PAD_RIGHT_ARROW_BTN_ID, GX_EVENT_CLICKED):
		myErr = gx_widget_resize ((GX_WIDGET*) g_PadSettings[LEFT_PAD].m_DirectionIcons[RIGHT_DIRECTION], &g_HiddenRectangle);
		myErr = gx_widget_resize ((GX_WIDGET*) g_PadSettings[LEFT_PAD].m_DirectionIcons[OFF_DIRECTION], &g_PadDirectionLocation[LEFT_PAD]);
		g_PadSettings[LEFT_PAD].m_PadDirection = OFF_DIRECTION;
		break;
	// Process RIGHT button pushes
	case GX_SIGNAL(RIGHT_PAD_OFF_BTN_ID, GX_EVENT_CLICKED):
		myErr = gx_widget_resize ((GX_WIDGET*) g_PadSettings[RIGHT_PAD].m_DirectionIcons[OFF_DIRECTION], &g_HiddenRectangle);
		myErr = gx_widget_resize ((GX_WIDGET*) g_PadSettings[RIGHT_PAD].m_DirectionIcons[LEFT_DIRECTION], &g_PadDirectionLocation[RIGHT_PAD]);
		g_PadSettings[RIGHT_PAD].m_PadDirection = LEFT_DIRECTION;
		break;
	case GX_SIGNAL(RIGHT_PAD_LEFT_ARROW_BTN_ID, GX_EVENT_CLICKED):
		myErr = gx_widget_resize ((GX_WIDGET*) g_PadSettings[RIGHT_PAD].m_DirectionIcons[LEFT_DIRECTION], &g_HiddenRectangle);
		myErr = gx_widget_resize ((GX_WIDGET*) g_PadSettings[RIGHT_PAD].m_DirectionIcons[FORWARD_DIRECTION], &g_PadDirectionLocation[RIGHT_PAD]);
		g_PadSettings[RIGHT_PAD].m_PadDirection = FORWARD_DIRECTION;
		break;
	case GX_SIGNAL(RIGHT_PAD_FORWARD_ARROW_BTN_ID, GX_EVENT_CLICKED):
		myErr = gx_widget_resize ((GX_WIDGET*) g_PadSettings[RIGHT_PAD].m_DirectionIcons[FORWARD_DIRECTION], &g_HiddenRectangle);
		myErr = gx_widget_resize ((GX_WIDGET*) g_PadSettings[RIGHT_PAD].m_DirectionIcons[RIGHT_DIRECTION], &g_PadDirectionLocation[RIGHT_PAD]);
		g_PadSettings[RIGHT_PAD].m_PadDirection = RIGHT_DIRECTION;
		break;
	case GX_SIGNAL(RIGHT_PAD_RIGHT_ARROW_BTN_ID, GX_EVENT_CLICKED):
		myErr = gx_widget_resize ((GX_WIDGET*) g_PadSettings[RIGHT_PAD].m_DirectionIcons[RIGHT_DIRECTION], &g_HiddenRectangle);
		myErr = gx_widget_resize ((GX_WIDGET*) g_PadSettings[RIGHT_PAD].m_DirectionIcons[OFF_DIRECTION], &g_PadDirectionLocation[RIGHT_PAD]);
		g_PadSettings[RIGHT_PAD].m_PadDirection = OFF_DIRECTION;
		break;
	// Process CENTER PAD button pushes
	case GX_SIGNAL(CENTER_PAD_OFF_BTN_ID, GX_EVENT_CLICKED):
		myErr = gx_widget_resize ((GX_WIDGET*) g_PadSettings[CENTER_PAD].m_DirectionIcons[OFF_DIRECTION], &g_HiddenRectangle);
		myErr = gx_widget_resize ((GX_WIDGET*) g_PadSettings[CENTER_PAD].m_DirectionIcons[LEFT_DIRECTION], &g_PadDirectionLocation[CENTER_PAD]);
		g_PadSettings[CENTER_PAD].m_PadDirection = LEFT_DIRECTION;
		break;
	case GX_SIGNAL(CENTER_PAD_LEFT_ARROW_BTN_ID, GX_EVENT_CLICKED):
		myErr = gx_widget_resize ((GX_WIDGET*) g_PadSettings[CENTER_PAD].m_DirectionIcons[LEFT_DIRECTION], &g_HiddenRectangle);
		myErr = gx_widget_resize ((GX_WIDGET*) g_PadSettings[CENTER_PAD].m_DirectionIcons[FORWARD_DIRECTION], &g_PadDirectionLocation[CENTER_PAD]);
		g_PadSettings[CENTER_PAD].m_PadDirection = FORWARD_DIRECTION;
		break;
	case GX_SIGNAL(CENTER_PAD_FORWARD_ARROW_BTN_ID, GX_EVENT_CLICKED):
		myErr = gx_widget_resize ((GX_WIDGET*) g_PadSettings[CENTER_PAD].m_DirectionIcons[FORWARD_DIRECTION], &g_HiddenRectangle);
		myErr = gx_widget_resize ((GX_WIDGET*) g_PadSettings[CENTER_PAD].m_DirectionIcons[RIGHT_DIRECTION], &g_PadDirectionLocation[CENTER_PAD]);
		g_PadSettings[CENTER_PAD].m_PadDirection = RIGHT_DIRECTION;
		break;
	case GX_SIGNAL(CENTER_PAD_RIGHT_ARROW_BTN_ID, GX_EVENT_CLICKED):
		myErr = gx_widget_resize ((GX_WIDGET*) g_PadSettings[CENTER_PAD].m_DirectionIcons[RIGHT_DIRECTION], &g_HiddenRectangle);
		myErr = gx_widget_resize ((GX_WIDGET*) g_PadSettings[CENTER_PAD].m_DirectionIcons[OFF_DIRECTION], &g_PadDirectionLocation[CENTER_PAD]);
		g_PadSettings[CENTER_PAD].m_PadDirection = OFF_DIRECTION;
		break;

	}

	myErr = gx_window_event_process(window, event_ptr);

	return GX_SUCCESS;
}













