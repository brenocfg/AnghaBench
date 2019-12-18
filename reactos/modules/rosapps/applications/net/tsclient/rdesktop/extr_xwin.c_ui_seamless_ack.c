#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int outpos_serial; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  yoffset; int /*<<< orphan*/  xoffset; int /*<<< orphan*/  wnd; scalar_t__ outstanding_position; int /*<<< orphan*/  outpos_height; int /*<<< orphan*/  outpos_width; int /*<<< orphan*/  outpos_yoffset; int /*<<< orphan*/  outpos_xoffset; struct TYPE_6__* next; } ;
typedef  TYPE_2__ seamless_window ;
struct TYPE_5__ {int /*<<< orphan*/  gc; int /*<<< orphan*/  backstore; TYPE_2__* seamless_windows; } ;
struct TYPE_7__ {TYPE_1__ xwin; int /*<<< orphan*/  display; } ;
typedef  TYPE_3__ RDPCLIENT ;

/* Variables and functions */
 scalar_t__ False ; 
 int /*<<< orphan*/  XCopyArea (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ui_seamless_ack(RDPCLIENT * This, unsigned int serial)
{
	seamless_window *sw;
	for (sw = This->xwin.seamless_windows; sw; sw = sw->next)
	{
		if (sw->outstanding_position && (sw->outpos_serial == serial))
		{
			sw->xoffset = sw->outpos_xoffset;
			sw->yoffset = sw->outpos_yoffset;
			sw->width = sw->outpos_width;
			sw->height = sw->outpos_height;
			sw->outstanding_position = False;

			/* Do a complete redraw of the window as part of the
			   completion of the move. This is to remove any
			   artifacts caused by our lack of synchronization. */
			XCopyArea(This->display, This->xwin.backstore,
				  sw->wnd, This->xwin.gc,
				  sw->xoffset, sw->yoffset, sw->width, sw->height, 0, 0);

			break;
		}
	}
}