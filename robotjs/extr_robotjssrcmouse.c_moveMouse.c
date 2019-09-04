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
typedef  int /*<<< orphan*/  MMPoint ;

/* Variables and functions */

void moveMouse(MMPoint point)
{
#if defined(IS_MACOSX)
	CGEventRef move = CGEventCreateMouseEvent(NULL, kCGEventMouseMoved,
	                                          CGPointFromMMPoint(point),
	                                          kCGMouseButtonLeft);

	calculateDeltas(&move, point);

	CGEventPost(kCGSessionEventTap, move);
	CFRelease(move);
#elif defined(USE_X11)
	Display *display = XGetMainDisplay();
	XWarpPointer(display, None, DefaultRootWindow(display),
	             0, 0, 0, 0, point.x, point.y);
	XSync(display, false);
#elif defined(IS_WINDOWS)
	//Mouse motion is now done using SendInput with MOUSEINPUT. We use Absolute mouse positioning
	#define MOUSE_COORD_TO_ABS(coord, width_or_height) (((65536 * coord) / width_or_height) + (coord < 0 ? -1 : 1))
	point.x = MOUSE_COORD_TO_ABS(point.x, GetSystemMetrics(SM_CXSCREEN));
	point.y = MOUSE_COORD_TO_ABS(point.y, GetSystemMetrics(SM_CYSCREEN));
	INPUT mouseInput;
	mouseInput.type = INPUT_MOUSE;
	mouseInput.mi.dx = point.x;
	mouseInput.mi.dy = point.y;
	mouseInput.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
	mouseInput.mi.time = 0; //System will provide the timestamp
	mouseInput.mi.dwExtraInfo = 0;
	mouseInput.mi.mouseData = 0;
	SendInput(1, &mouseInput, sizeof(mouseInput));
#endif
}