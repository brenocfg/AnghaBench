#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int* data32; } ;
struct TYPE_9__ {int format; TYPE_2__ data; int /*<<< orphan*/  type; int /*<<< orphan*/  window; int /*<<< orphan*/  response_type; } ;
typedef  TYPE_3__ xcb_client_message_event_t ;
typedef  int xcb_atom_t ;
struct TYPE_7__ {int /*<<< orphan*/  xid; } ;
struct TYPE_10__ {TYPE_1__ handle; TYPE_5__* sys; } ;
typedef  TYPE_4__ vout_window_t ;
struct TYPE_11__ {int /*<<< orphan*/  root; int /*<<< orphan*/  conn; int /*<<< orphan*/  wm_state; } ;
typedef  TYPE_5__ vout_window_sys_t ;

/* Variables and functions */
 int NET_WM_STATE_ADD ; 
 int NET_WM_STATE_REMOVE ; 
 int /*<<< orphan*/  XCB_CLIENT_MESSAGE ; 
 int XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY ; 
 int XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT ; 
 int /*<<< orphan*/  xcb_send_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char const*) ; 

__attribute__((used)) static void change_wm_state (vout_window_t *wnd, bool on, xcb_atom_t state)
{
    vout_window_sys_t *sys = wnd->sys;
    /* From EWMH "_WM_STATE" */
    xcb_client_message_event_t ev = {
         .response_type = XCB_CLIENT_MESSAGE,
         .format = 32,
         .window = wnd->handle.xid,
         .type = sys->wm_state,
    };

    ev.data.data32[0] = on ? NET_WM_STATE_ADD : NET_WM_STATE_REMOVE;
    ev.data.data32[1] = state;
    ev.data.data32[2] = 0;
    ev.data.data32[3] = 1;

    /* From ICCCM "Changing Window State" */
    xcb_send_event (sys->conn, 0, sys->root,
                    XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY |
                    XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT,
                    (const char *)&ev);
}