#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  subpicture_t ;
struct TYPE_8__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_9__ {int /*<<< orphan*/  p_out; } ;
typedef  TYPE_2__ demux_sys_t ;
struct TYPE_10__ {int b_on_vout; int /*<<< orphan*/  status; int /*<<< orphan*/ * p_updater; } ;
typedef  TYPE_3__ bluray_overlay_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLURAY_ES_OUT_CONTROL_CREATE_OVERLAY ; 
 int /*<<< orphan*/  Outdated ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * bluraySubpictureCreate (TYPE_3__*) ; 
 int es_out_Control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  subpicture_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unref_subpicture_updater (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bluraySendOverlayToVout(demux_t *p_demux, int plane, bluray_overlay_t *p_ov)
{
    demux_sys_t *p_sys = p_demux->p_sys;

    assert(p_ov != NULL);
    assert(!p_ov->b_on_vout);

    if (p_ov->p_updater) {
        unref_subpicture_updater(p_ov->p_updater);
        p_ov->p_updater = NULL;
    }

    subpicture_t *p_pic = bluraySubpictureCreate(p_ov);
    if (!p_pic) {
        msg_Err(p_demux, "bluraySubpictureCreate() failed");
        return;
    }

    /*
     * After this point, the picture should not be accessed from the demux thread,
     * as it is held by the vout thread.
     * This must be done only once per subpicture, ie. only once between each
     * blurayInitOverlay & blurayCloseOverlay call.
     */
    int ret = es_out_Control(p_sys->p_out, BLURAY_ES_OUT_CONTROL_CREATE_OVERLAY,
                             plane, p_pic);
    if (ret != VLC_SUCCESS)
    {
        unref_subpicture_updater(p_ov->p_updater);
        p_ov->p_updater = NULL;
        p_ov->b_on_vout = false;
        subpicture_Delete(p_pic);
        return;
    }
    p_ov->b_on_vout = true;

    /*
     * Mark the picture as Outdated, as it contains no region for now.
     * This will make the subpicture_updater_t call pf_update
     */
    p_ov->status = Outdated;
}