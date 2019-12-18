#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  opaque; int /*<<< orphan*/  (* setResizeCb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vout_window_t*) ;} ;
typedef  TYPE_1__ wextern_t ;
typedef  int /*<<< orphan*/  vout_window_cfg_t ;
struct vout_window_t {TYPE_1__* sys; } ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  WindowResize ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vout_window_t*) ; 

__attribute__((used)) static int Enable(struct vout_window_t *wnd, const vout_window_cfg_t *wcfg)
{
    wextern_t *sys = wnd->sys;

    if ( sys->setResizeCb != NULL )
        /* bypass the size handling as the window doesn't handle the size */
        sys->setResizeCb( sys->opaque, WindowResize, wnd );

    (void) wcfg;
    return VLC_SUCCESS;
}