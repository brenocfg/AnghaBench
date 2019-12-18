#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_6__ {TYPE_4__** p_overlays; } ;
struct TYPE_8__ {TYPE_1__ bdj; } ;
typedef  TYPE_3__ demux_sys_t ;
struct TYPE_9__ {scalar_t__ status; int /*<<< orphan*/  lock; scalar_t__ b_on_vout; } ;
typedef  TYPE_4__ bluray_overlay_t ;

/* Variables and functions */
 scalar_t__ Displayed ; 
 scalar_t__ Outdated ; 
 scalar_t__ ToDisplay ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void blurayActivateOverlay(demux_t *p_demux, int plane)
{
    demux_sys_t *p_sys = p_demux->p_sys;
    bluray_overlay_t *ov = p_sys->bdj.p_overlays[plane];

    /*
     * If the overlay is already displayed, mark the picture as outdated.
     * We must NOT use vout_PutSubpicture if a picture is already displayed.
     */
    vlc_mutex_lock(&ov->lock);
    if (ov->status >= Displayed && ov->b_on_vout) {
        ov->status = Outdated;
        vlc_mutex_unlock(&ov->lock);
        return;
    }

    /*
     * Mark the overlay as available, but don't display it right now.
     * the blurayDemuxMenu will send it to vout, as it may be unavailable when
     * the overlay is computed
     */
    ov->status = ToDisplay;
    vlc_mutex_unlock(&ov->lock);
}