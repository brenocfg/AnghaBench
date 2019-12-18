#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ wnd; struct TYPE_7__* next; } ;
typedef  TYPE_2__ seamless_window ;
typedef  scalar_t__ Window ;
struct TYPE_6__ {TYPE_2__* seamless_windows; } ;
struct TYPE_8__ {TYPE_1__ xwin; } ;
typedef  TYPE_3__ RDPCLIENT ;

/* Variables and functions */

__attribute__((used)) static seamless_window *
sw_get_window_by_wnd(RDPCLIENT * This, Window wnd)
{
	seamless_window *sw;
	for (sw = This->xwin.seamless_windows; sw; sw = sw->next)
	{
		if (sw->wnd == wnd)
			return sw;
	}
	return NULL;
}