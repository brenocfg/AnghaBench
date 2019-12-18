#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int dmSize; int dmPelsWidth; int dmPelsHeight; int dmFields; int /*<<< orphan*/  dmDisplayFixedOutput; } ;
typedef  int /*<<< orphan*/  PGUI_CONSOLE_DATA ;
typedef  int /*<<< orphan*/  DevMode ;
typedef  TYPE_1__ DEVMODEW ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CDS_FULLSCREEN ; 
 scalar_t__ ChangeDisplaySettingsW (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ DISP_CHANGE_SUCCESSFUL ; 
 int /*<<< orphan*/  DMDFO_CENTER ; 
 int DM_DISPLAYFIXEDOUTPUT ; 
 int DM_PELSHEIGHT ; 
 int DM_PELSWIDTH ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 

BOOL
EnterFullScreen(PGUI_CONSOLE_DATA GuiData)
{
    DEVMODEW DevMode;

    ZeroMemory(&DevMode, sizeof(DevMode));
    DevMode.dmSize = sizeof(DevMode);

    DevMode.dmDisplayFixedOutput = DMDFO_CENTER; // DMDFO_STRETCH // DMDFO_DEFAULT
    // DevMode.dmDisplayFlags = DMDISPLAYFLAGS_TEXTMODE;
    DevMode.dmPelsWidth  = 640; // GuiData->ActiveBuffer->ViewSize.X * GuiData->CharWidth;
    DevMode.dmPelsHeight = 480; // GuiData->ActiveBuffer->ViewSize.Y * GuiData->CharHeight;
    // DevMode.dmBitsPerPel = 32;
    DevMode.dmFields     = DM_DISPLAYFIXEDOUTPUT | /* DM_DISPLAYFLAGS | DM_BITSPERPEL | */ DM_PELSWIDTH | DM_PELSHEIGHT;

    return (ChangeDisplaySettingsW(&DevMode, CDS_FULLSCREEN) == DISP_CHANGE_SUCCESSFUL);
}