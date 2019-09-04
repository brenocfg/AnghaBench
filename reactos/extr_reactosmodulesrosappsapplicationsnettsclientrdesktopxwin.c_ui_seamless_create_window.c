#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_10__ ;

/* Type definitions */
struct timeval {int dummy; } ;
struct TYPE_27__ {unsigned long id; int /*<<< orphan*/  wnd; TYPE_10__* group; struct TYPE_27__* next; scalar_t__ outpos_height; scalar_t__ outpos_width; scalar_t__ outpos_yoffset; scalar_t__ outpos_xoffset; scalar_t__ outpos_serial; int /*<<< orphan*/  outstanding_position; void* position_timer; scalar_t__ desktop; int /*<<< orphan*/  state; scalar_t__ height; scalar_t__ width; scalar_t__ yoffset; scalar_t__ xoffset; scalar_t__ behind; } ;
typedef  TYPE_2__ seamless_window ;
struct TYPE_28__ {char* res_name; char* res_class; int /*<<< orphan*/  window_group; int /*<<< orphan*/  flags; } ;
typedef  TYPE_3__ XWMHints ;
typedef  TYPE_3__ XSizeHints ;
typedef  int /*<<< orphan*/  XSetWindowAttributes ;
typedef  TYPE_3__ XClassHint ;
typedef  int /*<<< orphan*/  Window ;
struct TYPE_26__ {TYPE_2__* seamless_windows; int /*<<< orphan*/  kill_atom; int /*<<< orphan*/  screen; int /*<<< orphan*/  visual; int /*<<< orphan*/  depth; int /*<<< orphan*/  seamless_active; } ;
struct TYPE_29__ {int /*<<< orphan*/  display; TYPE_1__ xwin; } ;
struct TYPE_25__ {int /*<<< orphan*/  wnd; int /*<<< orphan*/  refcnt; } ;
typedef  TYPE_6__ RDPCLIENT ;

/* Variables and functions */
 int CWBackPixel ; 
 int CWBackingStore ; 
 int CWBorderPixel ; 
 int CWColormap ; 
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  InputOutput ; 
 long PropertyChangeMask ; 
 int /*<<< orphan*/  RootWindowOfScreen (int /*<<< orphan*/ ) ; 
 unsigned long SEAMLESSRDP_CREATE_MODAL ; 
 int /*<<< orphan*/  SEAMLESSRDP_NOTYETMAPPED ; 
 int /*<<< orphan*/  USPosition ; 
 int /*<<< orphan*/  WindowGroupHint ; 
 TYPE_3__* XAllocClassHint () ; 
 TYPE_3__* XAllocSizeHints () ; 
 TYPE_3__* XAllocWMHints () ; 
 int /*<<< orphan*/  XCreateWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XFree (TYPE_3__*) ; 
 int /*<<< orphan*/  XSelectInput (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  XSetClassHint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  XSetTransientForHint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSetWMHints (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  XSetWMNormalHints (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  XSetWMProtocols (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  XStoreName (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ewmh_set_window_modal (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ewmh_set_window_popup (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ewmh_set_wm_name (TYPE_6__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_input_mask (TYPE_6__*,long*) ; 
 int /*<<< orphan*/  get_window_attribs (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mwm_hide_decorations (TYPE_6__*,int /*<<< orphan*/ ) ; 
 TYPE_10__* sw_find_group (TYPE_6__*,unsigned long,int /*<<< orphan*/ ) ; 
 TYPE_2__* sw_get_window_by_id (TYPE_6__*,unsigned long) ; 
 int /*<<< orphan*/  timerclear (void*) ; 
 int /*<<< orphan*/  warning (char*,unsigned long) ; 
 void* xmalloc (int) ; 

void
ui_seamless_create_window(RDPCLIENT * This, unsigned long id, unsigned long group, unsigned long parent,
			  unsigned long flags)
{
	Window wnd;
	XSetWindowAttributes attribs;
	XClassHint *classhints;
	XSizeHints *sizehints;
	XWMHints *wmhints;
	long input_mask;
	seamless_window *sw, *sw_parent;

	if (!This->xwin.seamless_active)
		return;

	/* Ignore CREATEs for existing windows */
	sw = sw_get_window_by_id(This, id);
	if (sw)
		return;

	get_window_attribs(This, &attribs);
	wnd = XCreateWindow(This->display, RootWindowOfScreen(This->xwin.screen), -1, -1, 1, 1, 0, This->xwin.depth,
			    InputOutput, This->xwin.visual,
			    CWBackPixel | CWBackingStore | CWColormap | CWBorderPixel, &attribs);

	XStoreName(This->display, wnd, "SeamlessRDP");
	ewmh_set_wm_name(This, wnd, "SeamlessRDP");

	mwm_hide_decorations(This, wnd);

	classhints = XAllocClassHint();
	if (classhints != NULL)
	{
		classhints->res_name = "rdesktop";
		classhints->res_class = "SeamlessRDP";
		XSetClassHint(This->display, wnd, classhints);
		XFree(classhints);
	}

	/* WM_NORMAL_HINTS */
	sizehints = XAllocSizeHints();
	if (sizehints != NULL)
	{
		sizehints->flags = USPosition;
		XSetWMNormalHints(This->display, wnd, sizehints);
		XFree(sizehints);
	}

	/* Parent-less transient windows */
	if (parent == 0xFFFFFFFF)
	{
		XSetTransientForHint(This->display, wnd, RootWindowOfScreen(This->xwin.screen));
		/* Some buggy wm:s (kwin) do not handle the above, so fake it
		   using some other hints. */
		ewmh_set_window_popup(This, wnd);
	}
	/* Normal transient windows */
	else if (parent != 0x00000000)
	{
		sw_parent = sw_get_window_by_id(This, parent);
		if (sw_parent)
			XSetTransientForHint(This->display, wnd, sw_parent->wnd);
		else
			warning("ui_seamless_create_window: No parent window 0x%lx\n", parent);
	}

	if (flags & SEAMLESSRDP_CREATE_MODAL)
	{
		/* We do this to support buggy wm:s (*cough* metacity *cough*)
		   somewhat at least */
		if (parent == 0x00000000)
			XSetTransientForHint(This->display, wnd, RootWindowOfScreen(This->xwin.screen));
		ewmh_set_window_modal(This, wnd);
	}

	/* FIXME: Support for Input Context:s */

	get_input_mask(This, &input_mask);
	input_mask |= PropertyChangeMask;

	XSelectInput(This->display, wnd, input_mask);

	/* handle the WM_DELETE_WINDOW protocol. FIXME: When killing a
	   seamless window, we could try to close the window on the
	   serverside, instead of terminating rdesktop */
	XSetWMProtocols(This->display, wnd, &This->xwin.kill_atom, 1);

	sw = xmalloc(sizeof(seamless_window));
	sw->wnd = wnd;
	sw->id = id;
	sw->behind = 0;
	sw->group = sw_find_group(This, group, False);
	sw->group->refcnt++;
	sw->xoffset = 0;
	sw->yoffset = 0;
	sw->width = 0;
	sw->height = 0;
	sw->state = SEAMLESSRDP_NOTYETMAPPED;
	sw->desktop = 0;
	sw->position_timer = xmalloc(sizeof(struct timeval));
	timerclear(sw->position_timer);

	sw->outstanding_position = False;
	sw->outpos_serial = 0;
	sw->outpos_xoffset = sw->outpos_yoffset = 0;
	sw->outpos_width = sw->outpos_height = 0;

	sw->next = This->xwin.seamless_windows;
	This->xwin.seamless_windows = sw;

	/* WM_HINTS */
	wmhints = XAllocWMHints();
	if (wmhints)
	{
		wmhints->flags = WindowGroupHint;
		wmhints->window_group = sw->group->wnd;
		XSetWMHints(This->display, sw->wnd, wmhints);
		XFree(wmhints);
	}
}