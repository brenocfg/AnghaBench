#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32 ;
struct TYPE_8__ {scalar_t__* l; } ;
struct TYPE_9__ {int format; TYPE_1__ data; int /*<<< orphan*/  message_type; int /*<<< orphan*/  window; } ;
struct TYPE_10__ {TYPE_2__ xclient; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ XEvent ;
typedef  int /*<<< orphan*/  Window ;
struct TYPE_11__ {int /*<<< orphan*/  display; int /*<<< orphan*/  net_wm_state_atom; } ;
typedef  int /*<<< orphan*/  Status ;
typedef  TYPE_4__ RDPCLIENT ;
typedef  scalar_t__ Atom ;

/* Variables and functions */
 int /*<<< orphan*/  ClientMessage ; 
 int /*<<< orphan*/  DefaultRootWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  PropModeAppend ; 
 int /*<<< orphan*/  PropModeReplace ; 
 int SubstructureNotifyMask ; 
 int SubstructureRedirectMask ; 
 scalar_t__ WithdrawnState ; 
 int /*<<< orphan*/  XA_ATOM ; 
 int /*<<< orphan*/  XChangeProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned char*,unsigned long) ; 
 int /*<<< orphan*/  XFree (unsigned char*) ; 
 int /*<<< orphan*/  XSendEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_3__*) ; 
 scalar_t__ _NET_WM_STATE_ADD ; 
 scalar_t__ _NET_WM_STATE_REMOVE ; 
 scalar_t__ get_property_value (TYPE_4__*,int /*<<< orphan*/ ,char*,int,unsigned long*,unsigned char**,int) ; 
 int /*<<< orphan*/  memmove (scalar_t__*,scalar_t__*,int) ; 

__attribute__((used)) static int
ewmh_modify_state(RDPCLIENT * This, Window wnd, int add, Atom atom1, Atom atom2)
{
	Status status;
	XEvent xevent;

	int result;
	unsigned long nitems;
	unsigned char *props;
	uint32 state = WithdrawnState;

	/* The spec states that the window manager must respect any
	   _NET_WM_STATE attributes on a withdrawn window. In order words, we
	   modify the attributes directly for withdrawn windows and ask the WM
	   to do it for active windows. */
	result = get_property_value(This, wnd, "WM_STATE", 64, &nitems, &props, 1);
	if ((result >= 0) && nitems)
	{
		state = *(uint32 *) props;
		XFree(props);
	}

	if (state == WithdrawnState)
	{
		if (add)
		{
			Atom atoms[2];

			atoms[0] = atom1;
			nitems = 1;
			if (atom2)
			{
				atoms[1] = atom2;
				nitems = 2;
			}

			XChangeProperty(This->display, wnd, This->net_wm_state_atom, XA_ATOM,
					32, PropModeAppend, (unsigned char *) atoms, nitems);
		}
		else
		{
			Atom *atoms;
			int i;

			if (get_property_value(This, wnd, "_NET_WM_STATE", 64, &nitems, &props, 1) < 0)
				return 0;

			atoms = (Atom *) props;

			for (i = 0; i < nitems; i++)
			{
				if ((atoms[i] == atom1) || (atom2 && (atoms[i] == atom2)))
				{
					if (i != (nitems - 1))
						memmove(&atoms[i], &atoms[i + 1],
							sizeof(Atom) * (nitems - i - 1));
					nitems--;
					i--;
				}
			}

			XChangeProperty(This->display, wnd, This->net_wm_state_atom, XA_ATOM,
					32, PropModeReplace, (unsigned char *) atoms, nitems);

			XFree(props);
		}

		return 0;
	}

	xevent.type = ClientMessage;
	xevent.xclient.window = wnd;
	xevent.xclient.message_type = This->net_wm_state_atom;
	xevent.xclient.format = 32;
	if (add)
		xevent.xclient.data.l[0] = _NET_WM_STATE_ADD;
	else
		xevent.xclient.data.l[0] = _NET_WM_STATE_REMOVE;
	xevent.xclient.data.l[1] = atom1;
	xevent.xclient.data.l[2] = atom2;
	xevent.xclient.data.l[3] = 0;
	xevent.xclient.data.l[4] = 0;
	status = XSendEvent(This->display, DefaultRootWindow(This->display), False,
			    SubstructureNotifyMask | SubstructureRedirectMask, &xevent);
	if (!status)
		return -1;

	return 0;
}