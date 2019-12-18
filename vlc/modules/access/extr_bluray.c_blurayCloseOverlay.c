#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_7__ {TYPE_4__** p_overlays; } ;
struct TYPE_9__ {TYPE_1__ bdj; int /*<<< orphan*/  p_out; } ;
typedef  TYPE_3__ demux_sys_t ;
struct TYPE_10__ {int /*<<< orphan*/  p_regions; int /*<<< orphan*/  lock; scalar_t__ p_updater; } ;
typedef  TYPE_4__ bluray_overlay_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLURAY_ES_OUT_CONTROL_DELETE_OVERLAY ; 
 int /*<<< orphan*/  es_out_Control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 int /*<<< orphan*/  subpicture_region_ChainDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unref_subpicture_updater (scalar_t__) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void blurayCloseOverlay(demux_t *p_demux, int plane)
{
    demux_sys_t *p_sys = p_demux->p_sys;
    bluray_overlay_t *ov = p_sys->bdj.p_overlays[plane];

    if (ov != NULL) {

        /* drop overlay from vout */
        if (ov->p_updater) {
            unref_subpicture_updater(ov->p_updater);
        }

        /* no references to this overlay exist in vo anymore */
        es_out_Control(p_sys->p_out, BLURAY_ES_OUT_CONTROL_DELETE_OVERLAY, plane);

        vlc_mutex_destroy(&ov->lock);
        subpicture_region_ChainDelete(ov->p_regions);
        free(ov);

        p_sys->bdj.p_overlays[plane] = NULL;
    }
}