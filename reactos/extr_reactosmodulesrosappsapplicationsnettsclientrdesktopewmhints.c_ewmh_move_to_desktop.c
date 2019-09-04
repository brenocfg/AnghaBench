#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int* l; } ;
struct TYPE_8__ {int format; TYPE_1__ data; int /*<<< orphan*/  message_type; int /*<<< orphan*/  window; } ;
struct TYPE_9__ {TYPE_2__ xclient; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ XEvent ;
typedef  int /*<<< orphan*/  Window ;
struct TYPE_10__ {int /*<<< orphan*/  display; int /*<<< orphan*/  net_wm_desktop_atom; } ;
typedef  int /*<<< orphan*/  Status ;
typedef  TYPE_4__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  ClientMessage ; 
 int /*<<< orphan*/  DefaultRootWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  False ; 
 int SubstructureNotifyMask ; 
 int SubstructureRedirectMask ; 
 int /*<<< orphan*/  XSendEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_3__*) ; 

int
ewmh_move_to_desktop(RDPCLIENT * This, Window wnd, unsigned int desktop)
{
	Status status;
	XEvent xevent;

	xevent.type = ClientMessage;
	xevent.xclient.window = wnd;
	xevent.xclient.message_type = This->net_wm_desktop_atom;
	xevent.xclient.format = 32;
	xevent.xclient.data.l[0] = desktop;
	xevent.xclient.data.l[1] = 0;
	xevent.xclient.data.l[2] = 0;
	xevent.xclient.data.l[3] = 0;
	xevent.xclient.data.l[4] = 0;
	status = XSendEvent(This->display, DefaultRootWindow(This->display), False,
			    SubstructureNotifyMask | SubstructureRedirectMask, &xevent);
	if (!status)
		return -1;

	return 0;
}