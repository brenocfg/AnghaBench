#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ decoder_t ;
struct TYPE_19__ {int i_quirks; scalar_t__ b_started; } ;
struct TYPE_21__ {int (* pf_on_new_block ) (TYPE_2__*,TYPE_4__**) ;int i_decode_flags; int /*<<< orphan*/  lock; scalar_t__ b_has_format; scalar_t__ b_aborted; TYPE_1__ api; scalar_t__ b_output_ready; } ;
typedef  TYPE_3__ decoder_sys_t ;
struct TYPE_22__ {int i_flags; } ;
typedef  TYPE_4__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  AbortDecoderLocked (TYPE_2__*) ; 
 int BLOCK_FLAG_CORRUPTED ; 
 int BLOCK_FLAG_DISCONTINUITY ; 
 int BLOCK_FLAG_INTERLACED_MASK ; 
 int DECODE_FLAG_DRAIN ; 
 int DECODE_FLAG_RESTART ; 
 int /*<<< orphan*/  DecodeFlushLocked (TYPE_2__*) ; 
 int MC_API_VIDEO_QUIRKS_SUPPORT_INTERLACED ; 
 int /*<<< orphan*/  QueueBlockLocked (TYPE_2__*,TYPE_4__*,int) ; 
 int StartMediaCodec (TYPE_2__*) ; 
 int /*<<< orphan*/  StopMediaCodec (TYPE_2__*) ; 
 int VLCDEC_ECRITICAL ; 
 int VLCDEC_RELOAD ; 
 int VLCDEC_SUCCESS ; 
#define  VLC_ENOOBJ 129 
#define  VLC_SUCCESS 128 
 int /*<<< orphan*/  VLC_VAR_VOID ; 
 int /*<<< orphan*/  block_Release (TYPE_4__*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_2__*,char*) ; 
 int stub1 (TYPE_2__*,TYPE_4__**) ; 
 int /*<<< orphan*/  var_Create (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int DecodeBlock(decoder_t *p_dec, block_t *p_in_block)
{
    decoder_sys_t *p_sys = p_dec->p_sys;
    int i_ret;

    vlc_mutex_lock(&p_sys->lock);

    if (p_sys->b_aborted)
    {
        if (p_sys->b_has_format)
            goto end;
        else
            goto reload;
    }

    if (p_in_block == NULL)
    {
        /* No input block, decoder is draining */
        msg_Err(p_dec, "Decoder is draining");

        if (p_sys->b_output_ready)
            QueueBlockLocked(p_dec, NULL, true);
        goto end;
    }

    if (p_in_block->i_flags & (BLOCK_FLAG_DISCONTINUITY|BLOCK_FLAG_CORRUPTED))
    {
        if (p_sys->b_output_ready)
            QueueBlockLocked(p_dec, NULL, true);
        DecodeFlushLocked(p_dec);
        if (p_sys->b_aborted)
            goto end;
        if (p_in_block->i_flags & BLOCK_FLAG_CORRUPTED)
            goto end;
    }

    if (p_in_block->i_flags & BLOCK_FLAG_INTERLACED_MASK
     && !(p_sys->api.i_quirks & MC_API_VIDEO_QUIRKS_SUPPORT_INTERLACED))
    {
        /* Before Android 21 and depending on the vendor, MediaCodec can
         * crash or be in an inconsistent state when decoding interlaced
         * videos. See OMXCodec_GetQuirks() for a white list of decoders
         * that supported interlaced videos before Android 21. */
        msg_Warn(p_dec, "codec doesn't support interlaced videos");
        goto reload;
    }

    /* Parse input block */
    if ((i_ret = p_sys->pf_on_new_block(p_dec, &p_in_block)) != 1)
    {
        if (i_ret != 0)
        {
            AbortDecoderLocked(p_dec);
            msg_Err(p_dec, "pf_on_new_block failed");
        }
        goto end;
    }
    if (p_sys->i_decode_flags & (DECODE_FLAG_DRAIN|DECODE_FLAG_RESTART))
    {
        msg_Warn(p_dec, "Draining from DecodeBlock");
        const bool b_restart = p_sys->i_decode_flags & DECODE_FLAG_RESTART;
        p_sys->i_decode_flags = 0;

        /* Drain and flush before restart to unblock OutThread */
        if (p_sys->b_output_ready)
            QueueBlockLocked(p_dec, NULL, true);
        DecodeFlushLocked(p_dec);
        if (p_sys->b_aborted)
            goto end;

        if (b_restart)
        {
            StopMediaCodec(p_dec);

            int i_ret = StartMediaCodec(p_dec);
            switch (i_ret)
            {
            case VLC_SUCCESS:
                msg_Warn(p_dec, "Restarted from DecodeBlock");
                break;
            case VLC_ENOOBJ:
                break;
            default:
                msg_Err(p_dec, "StartMediaCodec failed");
                AbortDecoderLocked(p_dec);
                goto end;
            }
        }
    }

    /* Abort if MediaCodec is not yet started */
    if (p_sys->api.b_started)
        QueueBlockLocked(p_dec, p_in_block, false);

end:
    if (p_in_block)
        block_Release(p_in_block);
    /* Too late to reload here, we already modified/released the input block,
     * do it next time. */
    int ret = p_sys->b_aborted && p_sys->b_has_format ? VLCDEC_ECRITICAL
                                                      : VLCDEC_SUCCESS;
    vlc_mutex_unlock(&p_sys->lock);
    return ret;

reload:
    vlc_mutex_unlock(&p_sys->lock);
    /* Add an empty variable so that mediacodec won't be loaded again
     * for this ES */
    var_Create(p_dec, "mediacodec-failed", VLC_VAR_VOID);
    return VLCDEC_RELOAD;
}