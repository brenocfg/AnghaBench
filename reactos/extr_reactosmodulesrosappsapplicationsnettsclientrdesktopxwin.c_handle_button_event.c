#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16 ;
struct TYPE_11__ {int y; int x; int x_root; int y_root; int /*<<< orphan*/  button; int /*<<< orphan*/  time; } ;
struct TYPE_10__ {scalar_t__ window; } ;
struct TYPE_12__ {scalar_t__ type; TYPE_3__ xbutton; TYPE_2__ xmotion; } ;
typedef  TYPE_4__ XEvent ;
struct TYPE_9__ {int move_x_offset; int move_y_offset; scalar_t__ moving_wnd; int /*<<< orphan*/  using_full_workarea; } ;
struct TYPE_13__ {int win_button_size; int width; scalar_t__ wnd; TYPE_1__ xwin; scalar_t__ hide_decorations; int /*<<< orphan*/  fullscreen; int /*<<< orphan*/  display; int /*<<< orphan*/  last_gesturetime; } ;
typedef  TYPE_5__ RDPCLIENT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ButtonPress ; 
 scalar_t__ ButtonRelease ; 
 int /*<<< orphan*/  DefaultScreen (int /*<<< orphan*/ ) ; 
 scalar_t__ False ; 
 int MOUSE_FLAG_DOWN ; 
 int /*<<< orphan*/  RDP_INPUT_MOUSE ; 
 scalar_t__ True ; 
 int /*<<< orphan*/  XIconifyWindow (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdp_send_input (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int xkeymap_translate_button (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
handle_button_event(RDPCLIENT * This, XEvent xevent, BOOL down)
{
	uint16 button, flags = 0;
	This->last_gesturetime = xevent.xbutton.time;
	button = xkeymap_translate_button(xevent.xbutton.button);
	if (button == 0)
		return;

	if (down)
		flags = MOUSE_FLAG_DOWN;

	/* Stop moving window when button is released, regardless of cursor position */
	if (This->xwin.moving_wnd && (xevent.type == ButtonRelease))
		This->xwin.moving_wnd = False;

	/* If win_button_sizee is nonzero, enable single app mode */
	if (xevent.xbutton.y < This->win_button_size)
	{
		/*  Check from right to left: */
		if (xevent.xbutton.x >= This->width - This->win_button_size)
		{
			/* The close button, continue */
			;
		}
		else if (xevent.xbutton.x >= This->width - This->win_button_size * 2)
		{
			/* The maximize/restore button. Do not send to
			   server.  It might be a good idea to change the
			   cursor or give some other visible indication
			   that rdesktop inhibited this click */
			if (xevent.type == ButtonPress)
				return;
		}
		else if (xevent.xbutton.x >= This->width - This->win_button_size * 3)
		{
			/* The minimize button. Iconify window. */
			if (xevent.type == ButtonRelease)
			{
				/* Release the mouse button outside the minimize button, to prevent the
				   actual minimazation to happen */
				rdp_send_input(This, time(NULL), RDP_INPUT_MOUSE, button, 1, 1);
				XIconifyWindow(This->display, This->wnd, DefaultScreen(This->display));
				return;
			}
		}
		else if (xevent.xbutton.x <= This->win_button_size)
		{
			/* The system menu. Ignore. */
			if (xevent.type == ButtonPress)
				return;
		}
		else
		{
			/* The title bar. */
			if (xevent.type == ButtonPress)
			{
				if (!This->fullscreen && This->hide_decorations && !This->xwin.using_full_workarea)
				{
					This->xwin.moving_wnd = True;
					This->xwin.move_x_offset = xevent.xbutton.x;
					This->xwin.move_y_offset = xevent.xbutton.y;
				}
				return;
			}
		}
	}

	if (xevent.xmotion.window == This->wnd)
	{
		rdp_send_input(This, time(NULL), RDP_INPUT_MOUSE,
			       flags | button, xevent.xbutton.x, xevent.xbutton.y);
	}
	else
	{
		/* SeamlessRDP */
		rdp_send_input(This, time(NULL), RDP_INPUT_MOUSE,
			       flags | button, xevent.xbutton.x_root, xevent.xbutton.y_root);
	}
}