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
typedef  int /*<<< orphan*/  MMMouseButton ;

/* Variables and functions */
 int /*<<< orphan*/  clickMouse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  microsleep (int) ; 

void doubleClick(MMMouseButton button)
{

#if defined(IS_MACOSX)

	/* Double click for Mac. */
	const CGPoint currentPos = CGPointFromMMPoint(getMousePos());
	const CGEventType mouseTypeDown = MMMouseToCGEventType(true, button);
	const CGEventType mouseTypeUP = MMMouseToCGEventType(false, button);

	CGEventRef event = CGEventCreateMouseEvent(NULL, mouseTypeDown, currentPos, kCGMouseButtonLeft);

	/* Set event to double click. */
	CGEventSetIntegerValueField(event, kCGMouseEventClickState, 2);

	CGEventPost(kCGHIDEventTap, event);

	CGEventSetType(event, mouseTypeUP);
	CGEventPost(kCGHIDEventTap, event);

	CFRelease(event);

#else

	/* Double click for everything else. */
	clickMouse(button);
	microsleep(200);
	clickMouse(button);

#endif
}