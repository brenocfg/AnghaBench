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
typedef  int /*<<< orphan*/  pa_stream ;
struct TYPE_10__ {size_t i_buffer; size_t p_buffer; } ;
typedef  TYPE_1__ block_t ;
struct TYPE_11__ {TYPE_3__* sys; } ;
typedef  TYPE_2__ audio_output_t ;
struct TYPE_12__ {int /*<<< orphan*/  mainloop; int /*<<< orphan*/  context; int /*<<< orphan*/  last_date; int /*<<< orphan*/ * stream; } ;
typedef  TYPE_3__ aout_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  PA_SEEK_RELATIVE ; 
 int /*<<< orphan*/  block_Release (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (void*,size_t,size_t) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  pa_operation_unref (int /*<<< orphan*/ ) ; 
 scalar_t__ pa_stream_begin_write (int /*<<< orphan*/ *,void**,size_t*) ; 
 int /*<<< orphan*/  pa_stream_flush (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pa_stream_is_corked (int /*<<< orphan*/ *) ; 
 scalar_t__ pa_stream_write (int /*<<< orphan*/ *,void*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stream_start (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_pa_error (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Play(audio_output_t *aout, block_t *block, vlc_tick_t date)
{
    aout_sys_t *sys = aout->sys;
    pa_stream *s = sys->stream;


    /* Note: The core already holds the output FIFO lock at this point.
     * Therefore we must not under any circumstances (try to) acquire the
     * output FIFO lock while the PulseAudio threaded main loop lock is held
     * (including from PulseAudio stream callbacks). Otherwise lock inversion
     * will take place, and sooner or later a deadlock. */
    pa_threaded_mainloop_lock(sys->mainloop);

    sys->last_date = date;

    if (pa_stream_is_corked(s) > 0)
        stream_start(s, aout, date);

#if 0 /* Fault injector to test underrun recovery */
    static volatile unsigned u = 0;
    if ((++u % 1000) == 0) {
        msg_Err(aout, "fault injection");
        pa_operation_unref(pa_stream_flush(s, NULL, NULL));
    }
#endif
    while (block->i_buffer > 0)
    {
        void *ptr;
        size_t len = block->i_buffer;

        if (pa_stream_begin_write(s, &ptr, &len))
            vlc_pa_error(aout, "cannot begin write", sys->context);

        memcpy(ptr, block->p_buffer, len);
        block->p_buffer += len;
        block->i_buffer -= len;

        if (pa_stream_write(s, ptr, len, NULL, 0, PA_SEEK_RELATIVE) < 0)
            vlc_pa_error(aout, "cannot write", sys->context);
    }

    block_Release(block);

    pa_threaded_mainloop_unlock(sys->mainloop);
}