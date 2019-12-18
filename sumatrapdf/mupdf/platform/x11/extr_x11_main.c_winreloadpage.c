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
typedef  int /*<<< orphan*/  pdfapp_t ;
struct TYPE_5__ {scalar_t__* l; } ;
struct TYPE_6__ {int format; TYPE_1__ data; int /*<<< orphan*/  message_type; int /*<<< orphan*/  window; int /*<<< orphan*/  send_event; scalar_t__ serial; int /*<<< orphan*/  type; } ;
struct TYPE_7__ {TYPE_2__ xclient; } ;
typedef  TYPE_3__ XEvent ;
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 int /*<<< orphan*/  ClientMessage ; 
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  WM_RELOAD_PAGE ; 
 int /*<<< orphan*/  XCloseDisplay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * XOpenDisplay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XSendEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  xwin ; 

void winreloadpage(pdfapp_t *app)
{
	XEvent xev;
	Display *dpy = XOpenDisplay(NULL);

	xev.xclient.type = ClientMessage;
	xev.xclient.serial = 0;
	xev.xclient.send_event = True;
	xev.xclient.window = xwin;
	xev.xclient.message_type = WM_RELOAD_PAGE;
	xev.xclient.format = 32;
	xev.xclient.data.l[0] = 0;
	xev.xclient.data.l[1] = 0;
	xev.xclient.data.l[2] = 0;
	XSendEvent(dpy, xwin, 0, 0, &xev);
	XCloseDisplay(dpy);
}