#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct mc_api_out {scalar_t__ b_eos; } ;
typedef  int /*<<< orphan*/  picture_t ;
struct TYPE_11__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_13__ {int (* dequeue_out ) (TYPE_4__*,int) ;int (* get_out ) (TYPE_4__*,int,struct mc_api_out*) ;int /*<<< orphan*/  (* release_out ) (TYPE_4__*,int,int) ;} ;
struct TYPE_12__ {int b_flush_out; int (* pf_process_output ) (TYPE_1__*,struct mc_api_out*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ;int b_drained; int b_aborted; int /*<<< orphan*/  lock; int /*<<< orphan*/  dec_cond; TYPE_4__ api; int /*<<< orphan*/  cond; int /*<<< orphan*/  b_output_ready; } ;
typedef  TYPE_2__ decoder_sys_t ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int MC_API_INFO_OUTPUT_BUFFERS_CHANGED ; 
 int MC_API_INFO_OUTPUT_FORMAT_CHANGED ; 
 int /*<<< orphan*/  decoder_QueueAudio (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decoder_QueueVideo (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  mutex_cleanup_push (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_4__*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,int,int) ; 
 int stub3 (TYPE_4__*,int,struct mc_api_out*) ; 
 int stub4 (TYPE_1__*,struct mc_api_out*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  vlc_cleanup_pop () ; 
 int /*<<< orphan*/  vlc_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 

__attribute__((used)) static void *OutThread(void *data)
{
    decoder_t *p_dec = data;
    decoder_sys_t *p_sys = p_dec->p_sys;

    vlc_mutex_lock(&p_sys->lock);
    mutex_cleanup_push(&p_sys->lock);
    for (;;)
    {
        int i_index;

        /* Wait for output ready */
        while (!p_sys->b_flush_out && !p_sys->b_output_ready)
            vlc_cond_wait(&p_sys->cond, &p_sys->lock);

        if (p_sys->b_flush_out)
        {
            /* Acknowledge flushed state */
            p_sys->b_flush_out = false;
            vlc_cond_broadcast(&p_sys->dec_cond);
            continue;
        }

        int canc = vlc_savecancel();

        vlc_mutex_unlock(&p_sys->lock);

        /* Wait for an output buffer. This function returns when a new output
         * is available or if output is flushed. */
        i_index = p_sys->api.dequeue_out(&p_sys->api, -1);

        vlc_mutex_lock(&p_sys->lock);

        /* Ignore dequeue_out errors caused by flush */
        if (p_sys->b_flush_out)
        {
            /* If i_index >= 0, Release it. There is no way to know if i_index
             * is owned by us, so don't check the error. */
            if (i_index >= 0)
                p_sys->api.release_out(&p_sys->api, i_index, false);

            /* Parse output format/buffers even when we are flushing */
            if (i_index != MC_API_INFO_OUTPUT_FORMAT_CHANGED
             && i_index != MC_API_INFO_OUTPUT_BUFFERS_CHANGED)
            {
                vlc_restorecancel(canc);
                continue;
            }
        }

        /* Process output returned by dequeue_out */
        if (i_index >= 0 || i_index == MC_API_INFO_OUTPUT_FORMAT_CHANGED
         || i_index == MC_API_INFO_OUTPUT_BUFFERS_CHANGED)
        {
            struct mc_api_out out;
            int i_ret = p_sys->api.get_out(&p_sys->api, i_index, &out);

            if (i_ret == 1)
            {
                picture_t *p_pic = NULL;
                block_t *p_block = NULL;

                if (p_sys->pf_process_output(p_dec, &out, &p_pic,
                                             &p_block) == -1 && !out.b_eos)
                {
                    msg_Err(p_dec, "pf_process_output failed");
                    vlc_restorecancel(canc);
                    break;
                }
                if (p_pic)
                    decoder_QueueVideo(p_dec, p_pic);
                else if (p_block)
                    decoder_QueueAudio(p_dec, p_block);

                if (out.b_eos)
                {
                    msg_Warn(p_dec, "EOS received");
                    p_sys->b_drained = true;
                    vlc_cond_signal(&p_sys->dec_cond);
                }
            } else if (i_ret != 0)
            {
                msg_Err(p_dec, "get_out failed");
                vlc_restorecancel(canc);
                break;
            }
        }
        else
        {
            vlc_restorecancel(canc);
            break;
        }
        vlc_restorecancel(canc);
    }
    msg_Warn(p_dec, "OutThread stopped");

    /* Signal DecoderFlush that the output thread aborted */
    p_sys->b_aborted = true;
    vlc_cond_signal(&p_sys->dec_cond);

    vlc_cleanup_pop();
    vlc_mutex_unlock(&p_sys->lock);

    return NULL;
}