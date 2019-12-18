#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_window_t ;
struct TYPE_6__ {int /*<<< orphan*/  xid; } ;
struct TYPE_7__ {TYPE_1__ handle; } ;
typedef  TYPE_2__ vout_window_t ;

/* Variables and functions */
 int /*<<< orphan*/  Close (TYPE_2__*) ; 
 int /*<<< orphan*/  ReleaseDrawable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_2__*) ; 

__attribute__((used)) static void EmClose (vout_window_t *wnd)
{
    xcb_window_t window = wnd->handle.xid;

    Close (wnd);
    ReleaseDrawable (VLC_OBJECT(wnd), window);
}