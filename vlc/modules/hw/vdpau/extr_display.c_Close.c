#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ vout_display_t ;
struct TYPE_6__ {int /*<<< orphan*/  conn; int /*<<< orphan*/  vdp; int /*<<< orphan*/ * current; int /*<<< orphan*/  target; int /*<<< orphan*/  queue; } ;
typedef  TYPE_2__ vout_display_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  picture_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdp_presentation_queue_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdp_presentation_queue_target_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdp_release_x11 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_disconnect (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Close(vout_display_t *vd)
{
    vout_display_sys_t *sys = vd->sys;

    vdp_presentation_queue_destroy(sys->vdp, sys->queue);
    vdp_presentation_queue_target_destroy(sys->vdp, sys->target);

    if (sys->current != NULL)
        picture_Release(sys->current);

    vdp_release_x11(sys->vdp);
    xcb_disconnect(sys->conn);
    free(sys);
}