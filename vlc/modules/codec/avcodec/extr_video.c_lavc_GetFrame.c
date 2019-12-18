#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct AVCodecContext {int /*<<< orphan*/  pix_fmt; TYPE_1__* opaque; } ;
struct TYPE_10__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_11__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * p_va; int /*<<< orphan*/  b_direct_rendering; } ;
typedef  TYPE_2__ decoder_sys_t ;
struct TYPE_12__ {int /*<<< orphan*/ * opaque; int /*<<< orphan*/ ** buf; scalar_t__* linesize; int /*<<< orphan*/ ** data; } ;
typedef  TYPE_3__ AVFrame ;

/* Variables and functions */
 unsigned int AV_NUM_DATA_POINTERS ; 
 int avcodec_default_get_buffer2 (struct AVCodecContext*,TYPE_3__*,int) ; 
 scalar_t__ decoder_UpdateVideoOutput (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ lavc_UpdateVideoFormat (TYPE_1__*,struct AVCodecContext*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int lavc_dr_GetFrame (struct AVCodecContext*,TYPE_3__*) ; 
 int lavc_va_GetFrame (struct AVCodecContext*,TYPE_3__*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lavc_GetFrame(struct AVCodecContext *ctx, AVFrame *frame, int flags)
{
    decoder_t *dec = ctx->opaque;
    decoder_sys_t *sys = dec->p_sys;

    for (unsigned i = 0; i < AV_NUM_DATA_POINTERS; i++)
    {
        frame->data[i] = NULL;
        frame->linesize[i] = 0;
        frame->buf[i] = NULL;
    }
    frame->opaque = NULL;

    vlc_mutex_lock(&sys->lock);
    if (sys->p_va == NULL)
    {
        if (!sys->b_direct_rendering)
        {
            vlc_mutex_unlock(&sys->lock);
            return avcodec_default_get_buffer2(ctx, frame, flags);
        }

        /* Most unaccelerated decoders do not call get_format(), so we need to
         * update the output video format here. The MT semaphore must be held
         * to protect p_dec->fmt_out. */
        if (lavc_UpdateVideoFormat(dec, ctx, ctx->pix_fmt, ctx->pix_fmt, NULL) ||
            decoder_UpdateVideoOutput(dec, NULL))
        {
            vlc_mutex_unlock(&sys->lock);
            return -1;
        }
    }

    if (sys->p_va != NULL)
    {
        int ret = lavc_va_GetFrame(ctx, frame);
        vlc_mutex_unlock(&sys->lock);
        return ret;
    }

    /* Some codecs set pix_fmt only after the 1st frame has been decoded,
     * so we need to check for direct rendering again. */
    int ret = lavc_dr_GetFrame(ctx, frame);
    vlc_mutex_unlock(&sys->lock);
    if (ret)
        ret = avcodec_default_get_buffer2(ctx, frame, flags);
    return ret;
}