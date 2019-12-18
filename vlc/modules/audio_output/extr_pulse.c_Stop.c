#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pa_stream ;
struct TYPE_4__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ audio_output_t ;
struct TYPE_5__ {int /*<<< orphan*/  mainloop; int /*<<< orphan*/ * stream; int /*<<< orphan*/ * trigger; } ;
typedef  TYPE_2__ aout_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  pa_stream_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_stream_set_buffer_attr_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_stream_set_event_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_stream_set_latency_update_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_stream_set_moved_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_stream_set_overflow_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_stream_set_started_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_stream_set_state_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_stream_set_suspended_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_stream_set_underflow_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_stream_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_pa_rttime_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Stop(audio_output_t *aout)
{
    aout_sys_t *sys = aout->sys;
    pa_stream *s = sys->stream;

    pa_threaded_mainloop_lock(sys->mainloop);
    if (unlikely(sys->trigger != NULL))
        vlc_pa_rttime_free(sys->mainloop, sys->trigger);
    pa_stream_disconnect(s);

    /* Clear all callbacks */
    pa_stream_set_state_callback(s, NULL, NULL);
    pa_stream_set_buffer_attr_callback(s, NULL, NULL);
    pa_stream_set_event_callback(s, NULL, NULL);
    pa_stream_set_latency_update_callback(s, NULL, NULL);
    pa_stream_set_moved_callback(s, NULL, NULL);
    pa_stream_set_overflow_callback(s, NULL, NULL);
    pa_stream_set_started_callback(s, NULL, NULL);
    pa_stream_set_suspended_callback(s, NULL, NULL);
    pa_stream_set_underflow_callback(s, NULL, NULL);

    pa_stream_unref(s);
    sys->stream = NULL;
    pa_threaded_mainloop_unlock(sys->mainloop);
}