//***********************************************************************************
// Project: ASL110 Display Demo package
//
// Filename: ASL110_Display_Simulator_Main.c
//
// Description: This project is a Windows based project that is used to convey the
//		ASL110 Display Unit.
//
// Author: G. Chopcinski
//
// Creation Date: 7/18/19
//
//***********************************************************************************

#define GX_ARC_DRAWING_SUPPORT

#include "time.h"			// Windows supported timed functions.
#include "ASL110_Display_Simulator_Main.h"
#include "ASL165_System.h"
#include "UserMainScreen.h"
#include "PadInfo.h"

#define SCREEN_STACK_SIZE  5
#define SCRATCHPAD_PIXELS  (PRIMARYDISPLAY_X_RESOLUTION * PRIMARYDISPLAY_Y_RESOLUTION * 2)

//--------------------------------------------------------------------
// Define prototypes.
VOID start_guix(VOID);

extern void CreateFeatureWidgets (GX_VERTICAL_LIST *list);

//--------------------------------------------------------------------
// Global Variables
TX_BYTE_POOL       memory_pool;
GX_COLOR           scratchpad[SCRATCHPAD_PIXELS];

GX_RECTANGLE g_HiddenRectangle = {0,0,0,0};

//GX_RECTANGLE g_FeatureLocation[] = {
//	{10, 16, 300, 86},
//	{30, 94, 290, 130},
//	{30, 130, 290, 162},
//	{30, 166, 290, 198},
//	{0,0,0,0}};

int g_ChangeScreen_WIP;

GX_WINDOW *g_CalibrationScreen = GX_NULL;
//extern GX_RECTANGLE g_CalibrationPadLocations[];
extern GX_RECTANGLE g_CalibrationPromptLocations[];

int g_CalibrationPadNumber;
int g_CalibrationStepNumber;
int g_PadValue = 35;
int g_DeltaValue;

int g_ClicksActive = FALSE;
int g_PowerUpInIdle = FALSE;
int g_TimeoutValue = 20;
int g_RNet_Active = TRUE;
int g_AttendantActive = FALSE;
MODE_SWITCH_SCHEMA_ENUM g_Mode_Switch_Schema = MODE_SWITCH_PIN5;

//*************************************************************************************
// GLOBAL VARIABLES
//*************************************************************************************

int g_MinimumDriveValue = 20;		// Percentage, Minimum Drive value
char g_MinimuDriveString[8] = "20%";
unsigned char g_HA_Version_Major, g_HA_Version_Minor, g_HA_Version_Build, g_HA_EEPROM_Version = 5;

MAIN_SCREEN_FEATURE g_MainScreenFeatureInfo[NUM_FEATURES];

//*************************************************************************************
// Provided by GUIX to support Windows environment.
//*************************************************************************************

VOID *memory_allocate(ULONG size)
{
    VOID *memptr;

    if (tx_byte_allocate(&memory_pool, &memptr, size, TX_NO_WAIT) == TX_SUCCESS)
    {
        return memptr;
    }
    return NULL;
}

//*************************************************************************************
// Provided by GUIX to support Windows environment.
//*************************************************************************************
void memory_free(VOID *mem)
{
    tx_byte_release(mem);
}

//*************************************************************************************
// Provided by GUIX to support Windows environment.
//*************************************************************************************
int main(int argc, char ** argv)
{
    tx_kernel_enter();
    return(0);
}

//*************************************************************************************
// Provided by GUIX to support Windows environment.
//*************************************************************************************
VOID tx_application_define(void *first_unused_memory)
{
    /* create byte pool*/
    tx_byte_pool_create(&memory_pool, "scratchpad", scratchpad,
        SCRATCHPAD_PIXELS * sizeof(GX_COLOR));

    start_guix();
}

//*************************************************************************************
// Provided by GUIX to support Windows environment.
//*************************************************************************************
VOID  start_guix(VOID)
{
	UINT myError;

    /* Initialize GUIX. */
    gx_system_initialize();

    /* Assign memory alloc/free functions. */
    gx_system_memory_allocator_set(memory_allocate, memory_free);

	myError = -1;
    myError = gx_studio_display_configure(PRIMARYDISPLAY, win32_graphics_driver_setup_24xrgb, 
        LANGUAGE_ENGLISH, PRIMARYDISPLAY_THEME_1, &root);

	Initialize_MainScreenInfo();

	InitializePadInformation();

//    myError = gx_studio_named_widget_create("PrimaryTemplate", (GX_WIDGET *)root, GX_NULL);
	myError = gx_studio_named_widget_create("AttendantScreen", GX_NULL, GX_NULL);
	myError = gx_studio_named_widget_create("AttendantSettingsScreen", GX_NULL, GX_NULL);
	myError = gx_studio_named_widget_create("DiagnosticScreen", GX_NULL, GX_NULL);
	myError = gx_studio_named_widget_create("FeatureSettingsScreen", GX_NULL, GX_NULL);
	//CreateFeatureWidgets (&FeatureSettingsScreen.FeatureSettingsScreen_FeatureListBox);
	myError = gx_studio_named_widget_create("HHP_Start_Screen", GX_NULL, GX_NULL);
	myError = gx_studio_named_widget_create("MainUserScreen", (GX_WIDGET *)root, GX_NULL);
	myError = gx_studio_named_widget_create("MinimumDriveScreen", GX_NULL, GX_NULL);
	myError = gx_studio_named_widget_create("MoreSelectionScreen", GX_NULL, GX_NULL);
	myError = gx_studio_named_widget_create("PerformanceSelectionScreen", GX_NULL, GX_NULL);
	myError = gx_studio_named_widget_create("OON_Screen", GX_NULL, GX_NULL);
	myError = gx_studio_named_widget_create("PadCalibrationScreen", GX_NULL, GX_NULL);
	myError = gx_studio_named_widget_create("PadOptionsSettingsScreen", GX_NULL, GX_NULL);
	myError = gx_studio_named_widget_create("ResetScreen", GX_NULL, GX_NULL);
	myError = gx_studio_named_widget_create("ResetFinishScreen", GX_NULL, GX_NULL);
	myError = gx_studio_named_widget_create("StartupScreen", GX_NULL, GX_NULL);
	myError = gx_studio_named_widget_create("SetPadDirectionScreen", GX_NULL, GX_NULL);
	myError = gx_studio_named_widget_create("SetPadTypeScreen", GX_NULL, GX_NULL);
	myError = gx_studio_named_widget_create("UserSettingsScreen", GX_NULL, GX_NULL);
	myError = gx_studio_named_widget_create("UserSelectionScreen", GX_NULL, GX_NULL);
	myError = gx_studio_named_widget_create("VeerAdjustScreen", GX_NULL, GX_NULL);

	/* Show the root window.  */
    gx_widget_show(root);

    /* start GUIX thread */
    gx_system_start();
}

//******************************************************************************************
// Detach one window and attach anothe window to root.
//******************************************************************************************

VOID screen_toggle(GX_WINDOW *new_win, GX_WINDOW *old_win)
{
	int status;
    if (!new_win->gx_widget_parent)
    {
        status = gx_widget_attach(root, (GX_WIDGET *)new_win);
    }
    else
    {
        status = gx_widget_show((GX_WIDGET *)new_win);
    }
    status = gx_widget_detach((GX_WIDGET *)old_win);
}

////******************************************************************************************
//VOID screen_switch(GX_WIDGET *parent, GX_WIDGET *new_screen)
//{
//    gx_widget_detach(current_screen);
//    gx_widget_attach(parent, new_screen);
//    current_screen = new_screen;
//}
//*************************************************************************************
// Function Name: Template_event_function
//
// Description: This handles any messages sent to the template window
//
//*************************************************************************************

UINT Template_event_function (GX_WINDOW *window, GX_EVENT *event_ptr)
{
	UINT myErr = -1;

	switch (event_ptr->gx_event_type)
	{
	case GX_SIGNAL(DOWN_ARROW_BTN_ID, GX_EVENT_CLICKED):
		if (window->gx_widget_name == "PadCalibrationScreen")
		{
			if (g_CalibrationStepNumber == 0)		// We are doing minimum
			{
				if (g_PadSettings[g_CalibrationPadNumber].m_PadMinimumCalibrationValue > 4)
					g_PadSettings[g_CalibrationPadNumber].m_PadMinimumCalibrationValue -= 5;
				myErr = gx_numeric_prompt_value_set (&PadCalibrationScreen.PadCalibrationScreen_Value_Prompt, g_PadSettings[g_CalibrationPadNumber].m_PadMinimumCalibrationValue);
			}
			else if (g_CalibrationStepNumber == 1)	// Doing maximum
			{
				if (g_PadSettings[g_CalibrationPadNumber].m_PadMaximumCalibrationValue > 4)
					g_PadSettings[g_CalibrationPadNumber].m_PadMaximumCalibrationValue -= 5;
				myErr = gx_numeric_prompt_value_set (&PadCalibrationScreen.PadCalibrationScreen_Value_Prompt, g_PadSettings[g_CalibrationPadNumber].m_PadMaximumCalibrationValue);
			}
			gx_system_dirty_mark(g_CalibrationScreen);		// This forces the gauge to be updated and redrawn
		}
		break;
	case GX_SIGNAL(UP_ARROW_BTN_ID, GX_EVENT_CLICKED):
		if (window->gx_widget_name == "PadCalibrationScreen")
		{
			if (g_CalibrationStepNumber == 0)		// We are doing minimum
			{
				if (g_PadSettings[g_CalibrationPadNumber].m_PadMinimumCalibrationValue < 100)
					g_PadSettings[g_CalibrationPadNumber].m_PadMinimumCalibrationValue += 5;
				myErr = gx_numeric_prompt_value_set (&PadCalibrationScreen.PadCalibrationScreen_Value_Prompt, g_PadSettings[g_CalibrationPadNumber].m_PadMinimumCalibrationValue);
			}
			else if (g_CalibrationStepNumber == 1)	// Doing maximum
			{
				if (g_PadSettings[g_CalibrationPadNumber].m_PadMaximumCalibrationValue < 100)
					g_PadSettings[g_CalibrationPadNumber].m_PadMaximumCalibrationValue += 5;
				myErr = gx_numeric_prompt_value_set (&PadCalibrationScreen.PadCalibrationScreen_Value_Prompt, g_PadSettings[g_CalibrationPadNumber].m_PadMaximumCalibrationValue);
			}
			gx_system_dirty_mark(g_CalibrationScreen);		// This forces the gauge to be updated and redrawn
		}
//		else if (window->gx_widget_name == "StartupScreen")
//		{
//	        screen_toggle((GX_WINDOW *)&Main_User_Screen, window);
//		}
		break;
	case GX_EVENT_PEN_DOWN:	// We are going to determine if the PAD button is pressed and start a timer to increment the 
							// ... long time (2 seconds) and goto Programming if so.
		if (event_ptr->gx_event_target->gx_widget_name == "PadActiveButton")
		{
			g_DeltaValue = +5;
			gx_system_timer_start(window, PAD_ACTIVE_TIMER_ID, 8, 8);
			//myErr = gx_slider_value_set((GX_SLIDER*)&PadCalibrationScreen.PadCalibrationScreen_PadValue_Slider, &PadCalibrationScreen.PadCalibrationScreen_PadValue_Slider.gx_slider_info, g_PadValue);
		}
		break;
    case GX_EVENT_TIMER:
        if (event_ptr->gx_event_payload.gx_event_timer_id == PAD_ACTIVE_TIMER_ID)
		{
			g_PadValue += g_DeltaValue;
			if (g_PadValue > 100)
				g_PadValue = 100;
			if (g_PadValue <= 0)
				gx_system_timer_stop(window, PAD_ACTIVE_TIMER_ID);
			if (g_PadValue > 0)
			{
				myErr = gx_widget_resize ((GX_WIDGET*) &PadCalibrationScreen.PadCalibrationScreen_PadValue_Prompt, &g_CalibrationPromptLocations[1]);
				myErr = gx_numeric_prompt_value_set (&PadCalibrationScreen.PadCalibrationScreen_PadValue_Prompt, g_PadValue);
			}
			else
			{
				myErr = gx_widget_resize ((GX_WIDGET*) &PadCalibrationScreen.PadCalibrationScreen_PadValue_Prompt, &g_HiddenRectangle);
				myErr = gx_numeric_prompt_value_set (&PadCalibrationScreen.PadCalibrationScreen_PadValue_Prompt, g_PadValue);
			}
			gx_system_dirty_mark(g_CalibrationScreen);		// This forces the gauge to be updated and redrawn
		}
		break;
	case GX_EVENT_PEN_UP:
		{
			g_DeltaValue = -5;
		}
		break;
	} // end switch

    myErr = gx_window_event_process(window, event_ptr);

	return myErr;
}

