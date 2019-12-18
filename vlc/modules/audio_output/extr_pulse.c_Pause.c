#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  int /*<<< orphan*/  pa_stream ;
struct TYPE_7__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ audio_output_t ;
struct TYPE_8__ {scalar_t__ last_date; int /*<<< orphan*/  mainloop; int /*<<< orphan*/ * stream; } ;
typedef  TYPE_2__ aout_sys_t ;

/* Variables and functions */
 scalar_t__ VLC_TICK_INVALID ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  pa_stream_set_latency_update_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stream_latency_cb ; 
 int /*<<< orphan*/  stream_start_now (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  stream_stop (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void Pause(audio_output_t *aout, bool paused, vlc_tick_t date)
{
    aout_sys_t *sys = aout->sys;
    pa_stream *s = sys->stream;

    pa_threaded_mainloop_lock(sys->mainloop);

    if (paused) {
        pa_stream_set_latency_update_callback(s, NULL, NULL);
        stream_stop(s, aout);
    } else {
        pa_stream_set_latency_update_callback(s, stream_latency_cb, aout);
        if (likely(sys->last_date != VLC_TICK_INVALID))
            stream_start_now(s, aout);
    }

    pa_threaded_mainloop_unlock(sys->mainloop);
    (void) date;
}