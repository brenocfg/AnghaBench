#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_generic_event_t ;
struct TYPE_11__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ vout_display_t ;
struct TYPE_12__ {int /*<<< orphan*/  conn; TYPE_4__* current; int /*<<< orphan*/  vdp; int /*<<< orphan*/  queue; } ;
typedef  TYPE_2__ vout_display_sys_t ;
struct TYPE_13__ {int /*<<< orphan*/  surface; } ;
typedef  TYPE_3__ vlc_vdp_output_surface_t ;
struct TYPE_14__ {TYPE_3__* p_sys; } ;
typedef  TYPE_4__ picture_t ;
typedef  int /*<<< orphan*/  VdpTime ;
typedef  scalar_t__ VdpStatus ;

/* Variables and functions */
 scalar_t__ VDP_STATUS_OK ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 TYPE_4__* picture_Hold (TYPE_4__*) ; 
 int /*<<< orphan*/  picture_Release (TYPE_4__*) ; 
 int /*<<< orphan*/  vdp_get_error_string (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ vdp_presentation_queue_block_until_surface_idle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xcb_poll_for_event (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Wait(vout_display_t *vd, picture_t *pic)
{
    vout_display_sys_t *sys = vd->sys;
    xcb_generic_event_t *ev;

    picture_t *current = sys->current;
    if (current != NULL)
    {
        vlc_vdp_output_surface_t *psys = current->p_sys;
        VdpTime pts;
        VdpStatus err;

        err = vdp_presentation_queue_block_until_surface_idle(sys->vdp,
                                              sys->queue, psys->surface, &pts);
        if (err != VDP_STATUS_OK)
        {
            msg_Err(vd, "presentation queue blocking error: %s",
                    vdp_get_error_string(sys->vdp, err));
            goto out;
        }
        picture_Release(current);
    }

    sys->current = picture_Hold(pic);
out:
    /* Drain the event queue. TODO: remove sys->conn completely */

    while ((ev = xcb_poll_for_event(sys->conn)) != NULL)
        free(ev);
}