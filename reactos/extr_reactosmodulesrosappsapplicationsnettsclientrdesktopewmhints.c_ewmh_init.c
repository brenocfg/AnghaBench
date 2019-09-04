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
struct TYPE_4__ {void* utf8_string_atom; void* name_atom; void* state_modal_atom; void* state_skip_pager_atom; void* state_skip_taskbar_atom; void* state_hidden_atom; void* state_maximized_horz_atom; void* state_maximized_vert_atom; } ;
struct TYPE_5__ {int /*<<< orphan*/  display; TYPE_1__ ewmhints; void* net_wm_desktop_atom; void* net_wm_state_atom; } ;
typedef  TYPE_2__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 void* XInternAtom (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void
ewmh_init(RDPCLIENT * This)
{
	/* FIXME: Use XInternAtoms */
	This->ewmhints.state_maximized_vert_atom =
		XInternAtom(This->display, "_NET_WM_STATE_MAXIMIZED_VERT", False);
	This->ewmhints.state_maximized_horz_atom =
		XInternAtom(This->display, "_NET_WM_STATE_MAXIMIZED_HORZ", False);
	This->ewmhints.state_hidden_atom = XInternAtom(This->display, "_NET_WM_STATE_HIDDEN", False);
	This->ewmhints.state_skip_taskbar_atom =
		XInternAtom(This->display, "_NET_WM_STATE_SKIP_TASKBAR", False);
	This->ewmhints.state_skip_pager_atom = XInternAtom(This->display, "_NET_WM_STATE_SKIP_PAGER", False);
	This->ewmhints.state_modal_atom = XInternAtom(This->display, "_NET_WM_STATE_MODAL", False);
	This->net_wm_state_atom = XInternAtom(This->display, "_NET_WM_STATE", False);
	This->net_wm_desktop_atom = XInternAtom(This->display, "_NET_WM_DESKTOP", False);
	This->ewmhints.name_atom = XInternAtom(This->display, "_NET_WM_NAME", False);
	This->ewmhints.utf8_string_atom = XInternAtom(This->display, "UTF8_STRING", False);
}