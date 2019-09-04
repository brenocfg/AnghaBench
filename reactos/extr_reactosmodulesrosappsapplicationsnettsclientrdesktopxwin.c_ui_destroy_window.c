#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * IC; } ;
struct TYPE_5__ {int /*<<< orphan*/  wnd; int /*<<< orphan*/  display; TYPE_1__ xwin; } ;
typedef  TYPE_2__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  XDestroyIC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XDestroyWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ui_destroy_window(RDPCLIENT * This)
{
	if (This->xwin.IC != NULL)
		XDestroyIC(This->xwin.IC);

	XDestroyWindow(This->display, This->wnd);
}