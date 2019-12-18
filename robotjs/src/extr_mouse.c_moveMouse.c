#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mouseInput ;
struct TYPE_8__ {int dwFlags; scalar_t__ mouseData; scalar_t__ dwExtraInfo; scalar_t__ time; void* dy; void* dx; } ;
struct TYPE_10__ {TYPE_1__ mi; int /*<<< orphan*/  type; } ;
struct TYPE_9__ {void* y; void* x; } ;
typedef  TYPE_2__ MMPoint ;
typedef  TYPE_3__ INPUT ;
typedef  int /*<<< orphan*/  Display ;
typedef  int /*<<< orphan*/  CGEventRef ;

/* Variables and functions */
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CGEventCreateMouseEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CGEventPost (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CGPointFromMMPoint (TYPE_2__) ; 
 int /*<<< orphan*/  DefaultRootWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INPUT_MOUSE ; 
 int MOUSEEVENTF_ABSOLUTE ; 
 int MOUSEEVENTF_MOVE ; 
 void* MOUSE_COORD_TO_ABS (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  None ; 
 int /*<<< orphan*/  SM_CXSCREEN ; 
 int /*<<< orphan*/  SM_CYSCREEN ; 
 int /*<<< orphan*/  SendInput (int,TYPE_3__*,int) ; 
 int /*<<< orphan*/ * XGetMainDisplay () ; 
 int /*<<< orphan*/  XSync (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  XWarpPointer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*) ; 
 int /*<<< orphan*/  calculateDeltas (int /*<<< orphan*/ *,TYPE_2__) ; 
 int /*<<< orphan*/  kCGEventMouseMoved ; 
 int /*<<< orphan*/  kCGMouseButtonLeft ; 
 int /*<<< orphan*/  kCGSessionEventTap ; 

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