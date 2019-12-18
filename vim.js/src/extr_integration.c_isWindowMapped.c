#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ map_state; } ;
typedef  TYPE_1__ XWindowAttributes ;
typedef  int /*<<< orphan*/  Window ;
typedef  int /*<<< orphan*/  Display ;
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 scalar_t__ IsViewable ; 
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  XGetWindowAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static Boolean
isWindowMapped(Display *display, Window win)
{
	XWindowAttributes winAttrs;
	XGetWindowAttributes(display,
			     win,
			     &winAttrs);
	if (winAttrs.map_state == IsViewable) {
		return(True);
	} else {
		return(False);
	}
}