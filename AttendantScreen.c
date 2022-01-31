//*****************************************************************************
// Filename: AttendantScreen.cpp
//
// Date: April 28, 2021
//
// Author: G. Chopcinski, Kg Solutions, LLC
// 
//*****************************************************************************

#include "math.h"

#include "ASL165_System.h"
#include "PadInfo.h"

//*************************************************************************************
// Local Macros
//*************************************************************************************

//*************************************************************************************
// External References
//*************************************************************************************

#define INNER_CIRCLE_DIAMETER (30)
#define INNER_CIRCLE_DIAMETER_FLOAT (30.0f)

//*************************************************************************************
// Local/Global variables
//*************************************************************************************

int g_StopActive = 0;

//*************************************************************************************
// Function Name: AttendantScreen_event_process
//
// Description: This functions handles the Attendant screen and dispatches
//		to the Diagnostic Screen or the Reset System screen.
//
//*************************************************************************************

char gPositionString[16];
char gDriveDemandString[16];
char gOutputDemandString[16];

UINT AttendantScreen_event_process (GX_WINDOW *window, GX_EVENT *event_ptr)
{
	double myDistance;
	double diffX, diffY;
	int speedDemand = 0, directionDemand = 0;
	int outputSpeed = 0, outputDirection = 0;
	float speed, direction;
	GX_BOOL calculateDistance = FALSE;

	switch (event_ptr->gx_event_type)
	{
	case GX_EVENT_SHOW:
		gx_icon_button_pixelmap_set (&AttendantScreen.AttendantScreen_StopButton, GX_PIXELMAP_ID_HEADARRAY_88X70);
		//gx_canvas_pixelmap_rotate (232, 9, 
		//	gx_canvas_pixelmap_get
		//	gx_context_pixelmap_get
		g_StopActive = FALSE;
		break;

	case GX_SIGNAL (OK_BTN_ID, GX_EVENT_CLICKED):
        screen_toggle((GX_WINDOW *)&MainUserScreen, window);
		break;

	case GX_EVENT_PEN_DOWN:
		if (event_ptr->gx_event_target->gx_widget_id == ATTENDANT_DRIVER_ID)
		{
			calculateDistance = TRUE;
		}

		if (event_ptr->gx_event_target->gx_widget_id == STOP_BUTTON_ID)
		{
			if (g_StopActive == 0)
			{
				g_StopActive = 1;
				gx_icon_button_pixelmap_set (&AttendantScreen.AttendantScreen_StopButton, GX_PIXELMAP_ID_HEADARRAY_DISABLED_88X70);
			}
			else if (g_StopActive == 1)
			{
				g_StopActive = 2;
				gx_icon_button_pixelmap_set (&AttendantScreen.AttendantScreen_StopButton, GX_PIXELMAP_ID_HEADARRAY_POWEROFF_88X70);
			}
			else 
			{
				g_StopActive = 0;
				gx_icon_button_pixelmap_set (&AttendantScreen.AttendantScreen_StopButton, GX_PIXELMAP_ID_HEADARRAY_88X70);
			}
		}


		break;

	case GX_EVENT_PEN_DRAG:
		if (event_ptr->gx_event_target->gx_widget_id == ATTENDANT_DRIVER_ID)
		{
			calculateDistance = TRUE;
		}
		break;
	} // end switch

	if (calculateDistance)
	{
		// distance = square root of the sum of the squares
		// Calculate the distance for the center of the Circle.
		diffX = (double) (event_ptr->gx_event_payload.gx_event_pointdata.gx_point_x) - 120.0f;
		diffY = (double) (event_ptr->gx_event_payload.gx_event_pointdata.gx_point_y) - 120.0f;
		diffX *= diffX;
		diffY *= diffY;
		myDistance = sqrt (diffX + diffY);

		// Check to see if the position is within the valid area.
		if ((myDistance > INNER_CIRCLE_DIAMETER_FLOAT) && (myDistance < 100.0f))
		{
			// touch is within valid zone
			gx_numeric_prompt_value_set (&AttendantScreen.AttendantScreen_Distance_Prompt, (int) myDistance);
			// Calculate speed demand
			// First determine if it's in the "dead zone" which is within the inner circle.
			if ((event_ptr->gx_event_payload.gx_event_pointdata.gx_point_x < (120-INNER_CIRCLE_DIAMETER)) || (event_ptr->gx_event_payload.gx_event_pointdata.gx_point_x > (120+INNER_CIRCLE_DIAMETER)))
			{
				speed = (float) event_ptr->gx_event_payload.gx_event_pointdata.gx_point_x - 120;	// 120 = screen center of circle
				if (speed > 0)	// Forward direction?
				{
					speed -= INNER_CIRCLE_DIAMETER_FLOAT;	// eliminate inner circle offset
					speed *= (100.0f / (100.0f - INNER_CIRCLE_DIAMETER_FLOAT));						// convert to 0-100
					if (speed > 75)
						speed = 100;
				}
				else					// Must be reverse
				{
					speed += INNER_CIRCLE_DIAMETER;	// adjust for inner circle offset
					speed *= (100.0f / (100.0f - INNER_CIRCLE_DIAMETER_FLOAT));						// convert to 0-100
					if (speed < -65)
						speed = -100;
				}
				speedDemand = (int) speed;
			}

			// Calculate direction demand
			// First determine if it's in the "dead zone" which is within the circle.
			if ((event_ptr->gx_event_payload.gx_event_pointdata.gx_point_y < (120-INNER_CIRCLE_DIAMETER)) || (event_ptr->gx_event_payload.gx_event_pointdata.gx_point_y > (120+INNER_CIRCLE_DIAMETER)))
			{
				direction = (float) event_ptr->gx_event_payload.gx_event_pointdata.gx_point_y - 120;
				if (direction > 0)	// Right
				{
					direction -= INNER_CIRCLE_DIAMETER_FLOAT;	// eliminate inner circle offset
					direction *= (100.0f / (100.0f - INNER_CIRCLE_DIAMETER_FLOAT));						// convert to 0-100
					if (direction > 40)
						direction = 100;
				}
				else					// Must be left
				{
					direction += INNER_CIRCLE_DIAMETER;	// adjust for inner circle offset
					direction *= (100.0f / (100.0f - INNER_CIRCLE_DIAMETER_FLOAT));						// convert to 0-100
					if (direction < -40)
						direction = -100;
				}
				directionDemand = (int) direction;
			}
			outputSpeed = 2048+212;
			outputSpeed += (speedDemand * 410) / 100;
			outputDirection = 2048+212;
			outputDirection += (directionDemand * 410 ) / 100;
		}
	}

    gx_window_event_process(window, event_ptr);

	return (GX_SUCCESS);
}


