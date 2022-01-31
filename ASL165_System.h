//*****************************************************************************
// Filename: ASL165_System.h
// Description: This file declares function, typedefs and macros to the 
//		system wide usage.
//
// Author: G. Chopcinski, Kg Solutions, LLC
// 
//*****************************************************************************

#ifndef ASL165_SYSTEM_H
#define ASL165_SYSTEM_H

#include <stdio.h>

#include "asl110_display_demo_resources.h"
#include "asl110_display_demo_specifications.h"
#include "custom_checkbox.h"

#define MAXIMUM_DRIVE_SPEED (40)
#define FEATURE_TOGGLE_BUTTON_ID 1000	// this is used as the dynamically created buttons in the feature list.

// The following hold the Digital (non0) vs Proportional (0) setting for each pad.
typedef enum FEATURE_ID {POWER_ONOFF_ID, BLUETOOTH_ID, NEXT_FUNCTION_OR_TOGGLE_ID, NEXT_PROFILE_OR_USER_MENU_ID, RNET_SEATING_ID, RNET_SLEEP_FEATURE_ID, NUM_FEATURES} FEATURE_ID_ENUM; // "invalid" must be last enum
typedef enum ENUM_TIMER_IDS {ARROW_PUSHED_TIMER_ID = 1, CALIBRATION_TIMER_ID, PAD_ACTIVE_TIMER_ID} ENUM_TIMER_IDS_ENUM;
typedef enum ENUM_MODE_SWITCH_SCHEMA {MODE_SWITCH_PIN5, MODE_SWITCH_REVERSE} MODE_SWITCH_SCHEMA_ENUM;

typedef struct MAIN_SCREEN_FEATURE_STRUCT
{
    int m_Location;     // This indicates the Main Screen location, 0=Top most, 3=bottom most
	int m_Available;	// This is true if this feature should be displayed for Enabling/Disabling. Typically based upon RNet setting.
    int m_Enabled;      // Indicates if this feature is active.
    GX_RESOURCE_ID m_SmallIcon;
    GX_RESOURCE_ID m_LargeIcon;
    GX_RESOURCE_ID m_SmallDescriptionID;
    GX_RESOURCE_ID m_LargeDescriptionID;
	GX_WIDGET m_ItemWidget;
	GX_PROMPT m_PromptWidget;
	GX_CHECKBOX m_ButtonWidget;
    CUSTOM_CHECKBOX m_Checkbox;
} MAIN_SCREEN_FEATURE;

//*****************************************************************************
// GLOBAL VARIABLES
//*****************************************************************************

extern int g_ChangeScreen_WIP;
extern unsigned char g_HA_Version_Major, g_HA_Version_Minor, g_HA_Version_Build, g_HA_EEPROM_Version;
extern int g_CalibrationPadNumber;
extern int g_ClicksActive;
extern int g_PowerUpInIdle;
extern int g_TimeoutValue;
extern int g_RNet_Active;
extern int g_AttendantActive;
extern MODE_SWITCH_SCHEMA_ENUM g_Mode_Switch_Schema;

extern MAIN_SCREEN_FEATURE g_MainScreenFeatureInfo[];

//*****************************************************************************
// EXTERNAL, GLOBALLY available functions
//*****************************************************************************

VOID screen_toggle(GX_WINDOW *new_win, GX_WINDOW *old_win);
VOID screen_switch(GX_WIDGET *parent, GX_WIDGET *new_screen);


#endif // ASL165_SYSTEM_H