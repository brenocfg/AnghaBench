#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  MMSize ;
typedef  int /*<<< orphan*/  Display ;
typedef  int /*<<< orphan*/  CGDirectDisplayID ;

/* Variables and functions */
 size_t CGDisplayPixelsHigh (int /*<<< orphan*/ ) ; 
 size_t CGDisplayPixelsWide (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CGMainDisplayID () ; 
 int DefaultScreen (int /*<<< orphan*/ *) ; 
 scalar_t__ DisplayHeight (int /*<<< orphan*/ *,int const) ; 
 scalar_t__ DisplayWidth (int /*<<< orphan*/ *,int const) ; 
 scalar_t__ GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMSizeMake (size_t,size_t) ; 
 int /*<<< orphan*/  SM_CXSCREEN ; 
 int /*<<< orphan*/  SM_CYSCREEN ; 
 int /*<<< orphan*/ * XGetMainDisplay () ; 

MMSize getMainDisplaySize(void)
{
#if defined(IS_MACOSX)
	CGDirectDisplayID displayID = CGMainDisplayID();
	return MMSizeMake(CGDisplayPixelsWide(displayID),
	                  CGDisplayPixelsHigh(displayID));
#elif defined(USE_X11)
	Display *display = XGetMainDisplay();
	const int screen = DefaultScreen(display);

	return MMSizeMake((size_t)DisplayWidth(display, screen),
	                  (size_t)DisplayHeight(display, screen));
#elif defined(IS_WINDOWS)
	return MMSizeMake((size_t)GetSystemMetrics(SM_CXSCREEN),
	                  (size_t)GetSystemMetrics(SM_CYSCREEN));
#endif
}