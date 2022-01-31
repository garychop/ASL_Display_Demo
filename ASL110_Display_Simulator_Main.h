//*****************************************************************************
// Filename: ASL110_Display_Simulator_Main.h
// Date: Unknown
// Author: Unknow
// 
// 8/28/20 GChop, added good-practic comments.
//
//*****************************************************************************

#ifndef ASL110_DISPLAY_SIMULATOR_MAIN_H
#define ASL110_DISPLAY_SIMULATOR_MAIN_H

#include <stdio.h>
#include "gx_api.h"

#include "ASL110_Display_demo_resources.h"
#include "ASL110_Display_demo_specifications.h"

//extern DIAGNOSTICSCREEN_CONTROL_BLOCK DiagnosticScreen;
//
extern UINT win32_graphics_driver_setup_24xrgb(GX_DISPLAY *display);
VOID *memory_allocate(ULONG size);
void memory_free(VOID *mem);

GX_WINDOW_ROOT           *root;

#endif // ASL110_DISPLAY_SIMULATOR_MAIN_H