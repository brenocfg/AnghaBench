#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_53__   TYPE_9__ ;
typedef  struct TYPE_52__   TYPE_8__ ;
typedef  struct TYPE_51__   TYPE_7__ ;
typedef  struct TYPE_50__   TYPE_6__ ;
typedef  struct TYPE_49__   TYPE_5__ ;
typedef  struct TYPE_48__   TYPE_4__ ;
typedef  struct TYPE_47__   TYPE_3__ ;
typedef  struct TYPE_46__   TYPE_36__ ;
typedef  struct TYPE_45__   TYPE_35__ ;
typedef  struct TYPE_44__   TYPE_32__ ;
typedef  struct TYPE_43__   TYPE_2__ ;
typedef  struct TYPE_42__   TYPE_1__ ;
typedef  struct TYPE_41__   TYPE_18__ ;
typedef  struct TYPE_40__   TYPE_11__ ;
typedef  struct TYPE_39__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  str ;
struct TYPE_53__ {TYPE_32__* position_timer; int /*<<< orphan*/  desktop; int /*<<< orphan*/  wnd; int /*<<< orphan*/  state; int /*<<< orphan*/  id; scalar_t__ yoffset; scalar_t__ xoffset; } ;
typedef  TYPE_9__ seamless_window ;
typedef  int /*<<< orphan*/  XKeyEvent ;
struct TYPE_50__ {int /*<<< orphan*/  window; } ;
struct TYPE_41__ {int /*<<< orphan*/  state; int /*<<< orphan*/  atom; int /*<<< orphan*/  window; } ;
struct TYPE_46__ {int /*<<< orphan*/  request; } ;
struct TYPE_49__ {scalar_t__ y; scalar_t__ x; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  window; } ;
struct TYPE_48__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  window; } ;
struct TYPE_47__ {scalar_t__ y_root; scalar_t__ x_root; scalar_t__ y; scalar_t__ x; int /*<<< orphan*/  window; } ;
struct TYPE_45__ {int /*<<< orphan*/  state; int /*<<< orphan*/  keycode; int /*<<< orphan*/  time; } ;
struct TYPE_42__ {int /*<<< orphan*/ * l; } ;
struct TYPE_43__ {TYPE_1__ data; int /*<<< orphan*/  message_type; } ;
struct TYPE_52__ {int /*<<< orphan*/  state; int /*<<< orphan*/  window; } ;
struct TYPE_39__ {int type; TYPE_6__ xconfigure; TYPE_18__ xproperty; int /*<<< orphan*/  xselectionrequest; int /*<<< orphan*/  xselection; TYPE_36__ xmapping; TYPE_5__ xexpose; TYPE_4__ xfocus; TYPE_3__ xmotion; TYPE_35__ xkey; TYPE_2__ xclient; TYPE_8__ xvisibility; } ;
typedef  TYPE_10__ XEvent ;
struct TYPE_51__ {int /*<<< orphan*/  seamless_active; int /*<<< orphan*/  mod_map; int /*<<< orphan*/  gc; int /*<<< orphan*/  backstore; scalar_t__ mouse_in_wnd; scalar_t__ focused; int /*<<< orphan*/  seamless_focused; scalar_t__ move_y_offset; scalar_t__ move_x_offset; int /*<<< orphan*/  moving_wnd; int /*<<< orphan*/ * IC; int /*<<< orphan*/  kill_atom; int /*<<< orphan*/  protocol_atom; } ;
struct TYPE_44__ {int tv_usec; int tv_sec; } ;
struct TYPE_40__ {int Unobscured; TYPE_7__ xwin; int /*<<< orphan*/  net_wm_desktop_atom; int /*<<< orphan*/  net_wm_state_atom; int /*<<< orphan*/  display; int /*<<< orphan*/  wnd; int /*<<< orphan*/  fullscreen; int /*<<< orphan*/  grab_keyboard; int /*<<< orphan*/  last_gesturetime; } ;
typedef  int /*<<< orphan*/  Status ;
typedef  TYPE_11__ RDPCLIENT ;
typedef  int /*<<< orphan*/  KeySym ;
typedef  int /*<<< orphan*/  Atom ;

/* Variables and functions */
#define  ButtonPress 147 
#define  ButtonRelease 146 
#define  ClientMessage 145 
#define  ConfigureNotify 144 
 int /*<<< orphan*/  CurrentTime ; 
 int /*<<< orphan*/  DEBUG_KBD (char*) ; 
 int /*<<< orphan*/  DefaultRootWindow (int /*<<< orphan*/ ) ; 
#define  EnterNotify 143 
#define  Expose 142 
 scalar_t__ False ; 
#define  FocusIn 141 
#define  FocusOut 140 
 int /*<<< orphan*/  GrabModeAsync ; 
#define  KeyPress 139 
#define  KeyRelease 138 
#define  LeaveNotify 137 
 int /*<<< orphan*/  MOUSE_FLAG_MOVE ; 
#define  MapNotify 136 
 int /*<<< orphan*/  MappingKeyboard ; 
 int /*<<< orphan*/  MappingModifier ; 
#define  MappingNotify 135 
#define  MotionNotify 134 
 int /*<<< orphan*/  None ; 
 int /*<<< orphan*/  NotifyGrab ; 
 int /*<<< orphan*/  NotifyUngrab ; 
 int /*<<< orphan*/  NotifyWhileGrabbed ; 
 int /*<<< orphan*/  PropertyNewValue ; 
#define  PropertyNotify 133 
 int /*<<< orphan*/  RDP_INPUT_MOUSE ; 
 int /*<<< orphan*/  RevertToPointerRoot ; 
 int SEAMLESSRDP_POSITION_TIMER ; 
#define  SelectionClear 132 
#define  SelectionNotify 131 
#define  SelectionRequest 130 
 scalar_t__ True ; 
#define  UnmapNotify 129 
#define  VisibilityNotify 128 
 int /*<<< orphan*/  VisibilityUnobscured ; 
 int /*<<< orphan*/  XCopyArea (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ XFilterEvent (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFreeModifiermap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGetModifierMapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGrabKeyboard (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLookupBoth ; 
 int /*<<< orphan*/  XLookupKeySym ; 
 int /*<<< orphan*/  XLookupString (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XMoveWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XNextEvent (int /*<<< orphan*/ ,TYPE_10__*) ; 
 scalar_t__ XPending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XRefreshKeyboardMapping (TYPE_36__*) ; 
 int /*<<< orphan*/  XSetInputFocus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XUngrabKeyboard (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XmbLookupString (int /*<<< orphan*/ *,TYPE_35__*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ewmh_get_window_desktop (TYPE_11__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ewmh_get_window_state (TYPE_11__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ksname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gettimeofday (TYPE_32__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_button_event (TYPE_11__*,TYPE_10__,scalar_t__) ; 
 int /*<<< orphan*/  handle_special_keys (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  rdp_send_client_window_status (TYPE_11__*,int) ; 
 int /*<<< orphan*/  rdp_send_input (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  reset_modifier_keys (TYPE_11__*) ; 
 int /*<<< orphan*/  seamless_send_focus (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seamless_send_state (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sw_all_to_desktop (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_9__* sw_get_window_by_wnd (TYPE_11__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sw_handle_restack (TYPE_11__*,TYPE_9__*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xclip_handle_PropertyNotify (TYPE_11__*,TYPE_18__*) ; 
 int /*<<< orphan*/  xclip_handle_SelectionClear (TYPE_11__*) ; 
 int /*<<< orphan*/  xclip_handle_SelectionNotify (TYPE_11__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xclip_handle_SelectionRequest (TYPE_11__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xkeymap_send_keys (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xwin_process_events(RDPCLIENT * This)
{
	XEvent xevent;
	KeySym keysym;
	uint32 ev_time;
	char str[256];
	Status status;
	int events = 0;
	seamless_window *sw;

	while ((XPending(This->display) > 0) && events++ < 20)
	{
		XNextEvent(This->display, &xevent);

		if ((This->xwin.IC != NULL) && (XFilterEvent(&xevent, None) == True))
		{
			DEBUG_KBD(("Filtering event\n"));
			continue;
		}

		switch (xevent.type)
		{
			case VisibilityNotify:
				if (xevent.xvisibility.window == This->wnd)
					This->Unobscured =
						xevent.xvisibility.state == VisibilityUnobscured;

				break;
			case ClientMessage:
				/* the window manager told us to quit */
				if ((xevent.xclient.message_type == This->xwin.protocol_atom)
				    && ((Atom) xevent.xclient.data.l[0] == This->xwin.kill_atom))
					/* Quit */
					return 0;
				break;

			case KeyPress:
				This->last_gesturetime = xevent.xkey.time;
				if (This->xwin.IC != NULL)
					/* Multi_key compatible version */
				{
					XmbLookupString(This->xwin.IC,
							&xevent.xkey, str, sizeof(str), &keysym,
							&status);
					if (!((status == XLookupKeySym) || (status == XLookupBoth)))
					{
						error("XmbLookupString failed with status 0x%x\n",
						      status);
						break;
					}
				}
				else
				{
					/* Plain old XLookupString */
					DEBUG_KBD(("\nNo input context, using XLookupString\n"));
					XLookupString((XKeyEvent *) & xevent,
						      str, sizeof(str), &keysym, NULL);
				}

				DEBUG_KBD(("KeyPress for keysym (0x%lx, %s)\n", keysym,
					   get_ksname(keysym)));

				ev_time = time(NULL);
				if (handle_special_keys(This, keysym, xevent.xkey.state, ev_time, True))
					break;

				xkeymap_send_keys(This, keysym, xevent.xkey.keycode, xevent.xkey.state,
						  ev_time, True, 0);
				break;

			case KeyRelease:
				This->last_gesturetime = xevent.xkey.time;
				XLookupString((XKeyEvent *) & xevent, str,
					      sizeof(str), &keysym, NULL);

				DEBUG_KBD(("\nKeyRelease for keysym (0x%lx, %s)\n", keysym,
					   get_ksname(keysym)));

				ev_time = time(NULL);
				if (handle_special_keys(This, keysym, xevent.xkey.state, ev_time, False))
					break;

				xkeymap_send_keys(This, keysym, xevent.xkey.keycode, xevent.xkey.state,
						  ev_time, False, 0);
				break;

			case ButtonPress:
				handle_button_event(This, xevent, True);
				break;

			case ButtonRelease:
				handle_button_event(This, xevent, False);
				break;

			case MotionNotify:
				if (This->xwin.moving_wnd)
				{
					XMoveWindow(This->display, This->wnd,
						    xevent.xmotion.x_root - This->xwin.move_x_offset,
						    xevent.xmotion.y_root - This->xwin.move_y_offset);
					break;
				}

				if (This->fullscreen && !This->xwin.focused)
					XSetInputFocus(This->display, This->wnd, RevertToPointerRoot,
						       CurrentTime);

				if (xevent.xmotion.window == This->wnd)
				{
					rdp_send_input(This, time(NULL), RDP_INPUT_MOUSE, MOUSE_FLAG_MOVE,
						       xevent.xmotion.x, xevent.xmotion.y);
				}
				else
				{
					/* SeamlessRDP */
					rdp_send_input(This, time(NULL), RDP_INPUT_MOUSE, MOUSE_FLAG_MOVE,
						       xevent.xmotion.x_root,
						       xevent.xmotion.y_root);
				}
				break;

			case FocusIn:
				if (xevent.xfocus.mode == NotifyGrab)
					break;
				This->xwin.focused = True;
				reset_modifier_keys(This);
				if (This->grab_keyboard && This->xwin.mouse_in_wnd)
					XGrabKeyboard(This->display, This->wnd, True,
						      GrabModeAsync, GrabModeAsync, CurrentTime);

				sw = sw_get_window_by_wnd(This, xevent.xfocus.window);
				if (!sw)
					break;

				if (sw->id != This->xwin.seamless_focused)
				{
					seamless_send_focus(This, sw->id, 0);
					This->xwin.seamless_focused = sw->id;
				}
				break;

			case FocusOut:
				if (xevent.xfocus.mode == NotifyUngrab)
					break;
				This->xwin.focused = False;
				if (xevent.xfocus.mode == NotifyWhileGrabbed)
					XUngrabKeyboard(This->display, CurrentTime);
				break;

			case EnterNotify:
				/* we only register for this event when in fullscreen mode */
				/* or grab_keyboard */
				This->xwin.mouse_in_wnd = True;
				if (This->fullscreen)
				{
					XSetInputFocus(This->display, This->wnd, RevertToPointerRoot,
						       CurrentTime);
					break;
				}
				if (This->xwin.focused)
					XGrabKeyboard(This->display, This->wnd, True,
						      GrabModeAsync, GrabModeAsync, CurrentTime);
				break;

			case LeaveNotify:
				/* we only register for this event when grab_keyboard */
				This->xwin.mouse_in_wnd = False;
				XUngrabKeyboard(This->display, CurrentTime);
				break;

			case Expose:
				if (xevent.xexpose.window == This->wnd)
				{
					XCopyArea(This->display, This->xwin.backstore, xevent.xexpose.window,
						  This->xwin.gc,
						  xevent.xexpose.x, xevent.xexpose.y,
						  xevent.xexpose.width, xevent.xexpose.height,
						  xevent.xexpose.x, xevent.xexpose.y);
				}
				else
				{
					sw = sw_get_window_by_wnd(This, xevent.xexpose.window);
					if (!sw)
						break;
					XCopyArea(This->display, This->xwin.backstore,
						  xevent.xexpose.window, This->xwin.gc,
						  xevent.xexpose.x + sw->xoffset,
						  xevent.xexpose.y + sw->yoffset,
						  xevent.xexpose.width,
						  xevent.xexpose.height, xevent.xexpose.x,
						  xevent.xexpose.y);
				}

				break;

			case MappingNotify:
				/* Refresh keyboard mapping if it has changed. This is important for
				   Xvnc, since it allocates keycodes dynamically */
				if (xevent.xmapping.request == MappingKeyboard
				    || xevent.xmapping.request == MappingModifier)
					XRefreshKeyboardMapping(&xevent.xmapping);

				if (xevent.xmapping.request == MappingModifier)
				{
					XFreeModifiermap(This->xwin.mod_map);
					This->xwin.mod_map = XGetModifierMapping(This->display);
				}
				break;

				/* clipboard stuff */
			case SelectionNotify:
				xclip_handle_SelectionNotify(This, &xevent.xselection);
				break;
			case SelectionRequest:
				xclip_handle_SelectionRequest(This, &xevent.xselectionrequest);
				break;
			case SelectionClear:
				xclip_handle_SelectionClear(This);
				break;
			case PropertyNotify:
				xclip_handle_PropertyNotify(This, &xevent.xproperty);
				if (xevent.xproperty.window == This->wnd)
					break;
				if (xevent.xproperty.window == DefaultRootWindow(This->display))
					break;

				/* seamless */
				sw = sw_get_window_by_wnd(This, xevent.xproperty.window);
				if (!sw)
					break;

				if ((xevent.xproperty.atom == This->net_wm_state_atom)
				    && (xevent.xproperty.state == PropertyNewValue))
				{
					sw->state = ewmh_get_window_state(This, sw->wnd);
					seamless_send_state(This, sw->id, sw->state, 0);
				}

				if ((xevent.xproperty.atom == This->net_wm_desktop_atom)
				    && (xevent.xproperty.state == PropertyNewValue))
				{
					sw->desktop = ewmh_get_window_desktop(This, sw->wnd);
					sw_all_to_desktop(This, sw->wnd, sw->desktop);
				}

				break;
			case MapNotify:
				if (!This->xwin.seamless_active)
					rdp_send_client_window_status(This, 1);
				break;
			case UnmapNotify:
				if (!This->xwin.seamless_active)
					rdp_send_client_window_status(This, 0);
				break;
			case ConfigureNotify:
				if (!This->xwin.seamless_active)
					break;

				sw = sw_get_window_by_wnd(This, xevent.xconfigure.window);
				if (!sw)
					break;

				gettimeofday(sw->position_timer, NULL);
				if (sw->position_timer->tv_usec + SEAMLESSRDP_POSITION_TIMER >=
				    1000000)
				{
					sw->position_timer->tv_usec +=
						SEAMLESSRDP_POSITION_TIMER - 1000000;
					sw->position_timer->tv_sec += 1;
				}
				else
				{
					sw->position_timer->tv_usec += SEAMLESSRDP_POSITION_TIMER;
				}

				sw_handle_restack(This, sw);
				break;
		}
	}
	/* Keep going */
	return 1;
}