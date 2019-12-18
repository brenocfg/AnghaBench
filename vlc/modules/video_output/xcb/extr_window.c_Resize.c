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
typedef  int /*<<< orphan*/  xcb_connection_t ;
struct TYPE_5__ {int /*<<< orphan*/  xid; } ;
struct TYPE_6__ {TYPE_1__ handle; TYPE_3__* sys; } ;
typedef  TYPE_2__ vout_window_t ;
struct TYPE_7__ {int /*<<< orphan*/ * conn; } ;
typedef  TYPE_3__ vout_window_sys_t ;
typedef  unsigned int uint32_t ;

/* Variables and functions */
 int XCB_CONFIG_WINDOW_HEIGHT ; 
 int XCB_CONFIG_WINDOW_WIDTH ; 
 int /*<<< orphan*/  xcb_configure_window (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,unsigned int const*) ; 
 int /*<<< orphan*/  xcb_flush (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Resize(vout_window_t *wnd, unsigned width, unsigned height)
{
    vout_window_sys_t *sys = wnd->sys;
    xcb_connection_t *conn = sys->conn;
    const uint32_t values[] = { width, height, };

    xcb_configure_window(conn, wnd->handle.xid,
                         XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT,
                         values);
    xcb_flush(conn);
}