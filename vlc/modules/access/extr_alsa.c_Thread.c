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
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  int /*<<< orphan*/  snd_pcm_t ;
typedef  int snd_pcm_state_t ;
typedef  int snd_pcm_sframes_t ;
struct TYPE_10__ {int /*<<< orphan*/  out; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_11__ {int period_size; int /*<<< orphan*/  es; int /*<<< orphan*/  rate; int /*<<< orphan*/ * pcm; } ;
typedef  TYPE_2__ demux_sys_t ;
struct TYPE_12__ {int i_nb_samples; int /*<<< orphan*/  i_pts; scalar_t__ i_length; void* i_buffer; int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  DumpDeviceStatus (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int EAGAIN ; 
 int /*<<< orphan*/  Poll (int /*<<< orphan*/ *,int) ; 
#define  SND_PCM_STATE_PREPARED 129 
#define  SND_PCM_STATE_RUNNING 128 
 TYPE_3__* block_Alloc (size_t) ; 
 int /*<<< orphan*/  block_Release (TYPE_3__*) ; 
 int /*<<< orphan*/  es_out_Send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  es_out_SetPCR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_pcm_delay (int /*<<< orphan*/ *,int*) ; 
 void* snd_pcm_frames_to_bytes (int /*<<< orphan*/ *,int) ; 
 int snd_pcm_readi (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int snd_pcm_recover (int /*<<< orphan*/ *,int,int) ; 
 int snd_pcm_start (int /*<<< orphan*/ *) ; 
 int snd_pcm_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_strerror (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int vlc_savecancel () ; 
 scalar_t__ vlc_tick_from_samples (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_tick_now () ; 

__attribute__((used)) static void *Thread (void *data)
{
    demux_t *demux = data;
    demux_sys_t *sys = demux->p_sys;
    snd_pcm_t *pcm = sys->pcm;
    size_t bytes;
    int canc, val;

    canc = vlc_savecancel ();
    bytes = snd_pcm_frames_to_bytes (pcm, sys->period_size);
    val = snd_pcm_start (pcm);
    if (val)
    {
        msg_Err (demux, "cannot prepare device: %s", snd_strerror (val));
        return NULL;
    }

    for (;;)
    {
        block_t *block = block_Alloc (bytes);
        if (unlikely(block == NULL))
            break;

        /* Wait for data */
        Poll (pcm, canc);

        /* Read data */
        snd_pcm_sframes_t frames, delay;
        vlc_tick_t pts;

        frames = snd_pcm_readi (pcm, block->p_buffer, sys->period_size);
        pts = vlc_tick_now ();
        if (frames < 0)
        {
            block_Release (block);
            if (frames == -EAGAIN)
                continue;

            val = snd_pcm_recover (pcm, frames, 1);
            if (val == 0)
            {
                msg_Warn (demux, "cannot read samples: %s",
                          snd_strerror (frames));
                snd_pcm_state_t state = snd_pcm_state (pcm);
                switch (state)
                {
                case SND_PCM_STATE_PREPARED:
                    val = snd_pcm_start (pcm);
                    if (val < 0)
                    {
                        msg_Err (demux, "cannot prepare device: %s",
                                 snd_strerror (val));
                        return NULL;
                    }
                    continue;
                case SND_PCM_STATE_RUNNING:
                    continue;
                default:
                    break;
                }
            }
            msg_Err (demux, "cannot recover record stream: %s",
                     snd_strerror (val));
            DumpDeviceStatus (demux, pcm);
            break;
        }

        /* Compute time stamp */
        if (snd_pcm_delay (pcm, &delay))
            delay = 0;
        delay += frames;
        pts -= vlc_tick_from_samples(delay,  sys->rate);

        block->i_buffer = snd_pcm_frames_to_bytes (pcm, frames);
        block->i_nb_samples = frames;
        block->i_pts = pts;
        block->i_length = vlc_tick_from_samples(frames, sys->rate);

        es_out_SetPCR(demux->out, block->i_pts);
        es_out_Send (demux->out, sys->es, block);
    }
    return NULL;
}