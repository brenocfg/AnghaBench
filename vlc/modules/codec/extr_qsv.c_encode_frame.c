#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_20__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_18__ ;
typedef  struct TYPE_22__   TYPE_13__ ;

/* Type definitions */
struct TYPE_26__ {scalar_t__ date; } ;
typedef  TYPE_2__ picture_t ;
typedef  scalar_t__ mfxStatus ;
typedef  int /*<<< orphan*/  mfxFrameSurface1 ;
struct TYPE_27__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ encoder_t ;
struct TYPE_24__ {int BufferSizeInKB; } ;
struct TYPE_25__ {TYPE_1__ mfx; } ;
struct TYPE_28__ {TYPE_20__ params; int /*<<< orphan*/  session; int /*<<< orphan*/  busy_warn_counter; scalar_t__ offset_pts; } ;
typedef  TYPE_4__ encoder_sys_t ;
struct TYPE_22__ {int /*<<< orphan*/  Data; int /*<<< orphan*/  MaxLength; } ;
struct TYPE_29__ {TYPE_18__* block; void* syncp; TYPE_13__ bs; } ;
typedef  TYPE_5__ async_task_t ;
struct TYPE_30__ {int /*<<< orphan*/  surface; } ;
struct TYPE_23__ {int /*<<< orphan*/  p_buffer; int /*<<< orphan*/  i_buffer; } ;
typedef  TYPE_6__ QSVFrame ;

/* Variables and functions */
 scalar_t__ MFXVideoENCODE_EncodeFrameAsync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_13__*,void*) ; 
 int /*<<< orphan*/  MFXVideoENCODE_Reset (int /*<<< orphan*/ ,TYPE_20__*) ; 
 scalar_t__ MFX_ERR_MEMORY_ALLOC ; 
 scalar_t__ MFX_ERR_MORE_DATA ; 
 scalar_t__ MFX_ERR_NONE ; 
 scalar_t__ MFX_WRN_DEVICE_BUSY ; 
 scalar_t__ MFX_WRN_IN_EXECUTION ; 
 int /*<<< orphan*/  QSV_BUSYWAIT_TIME ; 
 scalar_t__ VLC_SUCCESS ; 
 TYPE_18__* block_Alloc (int) ; 
 int /*<<< orphan*/  block_Release (TYPE_18__*) ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_5__*) ; 
 int /*<<< orphan*/  memset (TYPE_13__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  msg_Err (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_3__*,char*) ; 
 scalar_t__ submit_frame (TYPE_3__*,TYPE_2__*,TYPE_6__**) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_tick_sleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static async_task_t *encode_frame(encoder_t *enc, picture_t *pic)
{
    encoder_sys_t *sys = enc->p_sys;
    mfxStatus sts = MFX_ERR_MEMORY_ALLOC;
    QSVFrame *qsv_frame = NULL;
    mfxFrameSurface1 *surf = NULL;
    async_task_t *task = calloc(1, sizeof(*task));
    if (unlikely(task == NULL))
        goto done;

    if (pic) {
        /* To avoid qsv -> vlc timestamp conversion overflow, we use timestamp relative
           to the first picture received. That way, vlc will overflow before us.
           (Thanks to funman for the idea) */
        if (!sys->offset_pts) // First frame
            sys->offset_pts = pic->date;

        if (submit_frame(enc, pic, &qsv_frame) != VLC_SUCCESS)
        {
            msg_Warn(enc, "Unable to find an unlocked surface in the pool");
            goto done;
        }
    }

    if (!(task->syncp = calloc(1, sizeof(*task->syncp)))) {
        msg_Err(enc, "Unable to allocate syncpoint for encoder output");
        goto done;
    }

    /* Allocate block_t and prepare mfxBitstream for encoder */
    if (!(task->block = block_Alloc(sys->params.mfx.BufferSizeInKB * 1000))) {
        msg_Err(enc, "Unable to allocate block for encoder output");
        goto done;
    }
    memset(&task->bs, 0, sizeof(task->bs));
    task->bs.MaxLength = task->block->i_buffer;
    task->bs.Data = task->block->p_buffer;

    if (qsv_frame) {
        surf = &qsv_frame->surface;
    }

    for (;;) {
        sts = MFXVideoENCODE_EncodeFrameAsync(sys->session, 0, surf, &task->bs, task->syncp);
        if (sts != MFX_WRN_DEVICE_BUSY && sts != MFX_WRN_IN_EXECUTION)
            break;
        if (sys->busy_warn_counter++ % 16 == 0)
            msg_Dbg(enc, "Device is busy, let's wait and retry %d", sts);
        if (sts == MFX_WRN_DEVICE_BUSY)
            vlc_tick_sleep(QSV_BUSYWAIT_TIME);
    }

    // msg_Dbg(enc, "Encode async status: %d, Syncpoint = %tx", sts, (ptrdiff_t)task->syncp);

    if (sts == MFX_ERR_MORE_DATA)
        if (pic)
            msg_Dbg(enc, "Encoder feeding phase, more data is needed.");
        else
            msg_Dbg(enc, "Encoder is empty");
    else if (sts < MFX_ERR_NONE) {
        msg_Err(enc, "Encoder not ready or error (%d), trying a reset...", sts);
        MFXVideoENCODE_Reset(sys->session, &sys->params);
    }

done:
    if (sts < MFX_ERR_NONE || (task != NULL && !task->syncp)) {
        if (task->block != NULL)
            block_Release(task->block);
        free(task);
        task = NULL;
    }
    return task;
}