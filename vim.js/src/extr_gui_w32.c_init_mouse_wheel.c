#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* UINT ;
struct TYPE_2__ {scalar_t__ dwPlatformId; int dwMajorVersion; int dwMinorVersion; } ;
typedef  scalar_t__ HWND ;

/* Variables and functions */
 scalar_t__ FindWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* RegisterWindowMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_GETWHEELSCROLLLINES ; 
 scalar_t__ SendMessage (scalar_t__,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SystemParametersInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ VER_PLATFORM_WIN32_NT ; 
 scalar_t__ VER_PLATFORM_WIN32_WINDOWS ; 
 int /*<<< orphan*/  VMOUSEZ_CLASSNAME ; 
 int /*<<< orphan*/  VMOUSEZ_TITLE ; 
 int /*<<< orphan*/  VMSH_MOUSEWHEEL ; 
 int /*<<< orphan*/  VMSH_SCROLL_LINES ; 
 int mouse_scroll_lines ; 
 void* msh_msgmousewheel ; 
 TYPE_1__ os_version ; 

__attribute__((used)) static void
init_mouse_wheel(void)
{

#ifndef SPI_GETWHEELSCROLLLINES
# define SPI_GETWHEELSCROLLLINES    104
#endif
#ifndef SPI_SETWHEELSCROLLLINES
# define SPI_SETWHEELSCROLLLINES    105
#endif

#define VMOUSEZ_CLASSNAME  "MouseZ"		/* hidden wheel window class */
#define VMOUSEZ_TITLE      "Magellan MSWHEEL"	/* hidden wheel window title */
#define VMSH_MOUSEWHEEL    "MSWHEEL_ROLLMSG"
#define VMSH_SCROLL_LINES  "MSH_SCROLL_LINES_MSG"

    HWND hdl_mswheel;
    UINT msh_msgscrolllines;

    msh_msgmousewheel = 0;
    mouse_scroll_lines = 3;	/* reasonable default */

    if ((os_version.dwPlatformId == VER_PLATFORM_WIN32_NT
		&& os_version.dwMajorVersion >= 4)
	    || (os_version.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS
		&& ((os_version.dwMajorVersion == 4
			&& os_version.dwMinorVersion >= 10)
		    || os_version.dwMajorVersion >= 5)))
    {
	/* if NT 4.0+ (or Win98) get scroll lines directly from system */
	SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0,
		&mouse_scroll_lines, 0);
    }
    else if (os_version.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS
	    || (os_version.dwPlatformId == VER_PLATFORM_WIN32_NT
		&& os_version.dwMajorVersion < 4))
    {	/*
	 * If Win95 or NT 3.51,
	 * try to find the hidden point32 window.
	 */
	hdl_mswheel = FindWindow(VMOUSEZ_CLASSNAME, VMOUSEZ_TITLE);
	if (hdl_mswheel)
	{
	    msh_msgscrolllines = RegisterWindowMessage(VMSH_SCROLL_LINES);
	    if (msh_msgscrolllines)
	    {
		mouse_scroll_lines = (int)SendMessage(hdl_mswheel,
			msh_msgscrolllines, 0, 0);
		msh_msgmousewheel  = RegisterWindowMessage(VMSH_MOUSEWHEEL);
	    }
	}
    }
}