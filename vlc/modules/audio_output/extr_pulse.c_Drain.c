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
typedef  scalar_t__ vlc_tick_t ;
typedef  int /*<<< orphan*/  pa_stream ;
typedef  int /*<<< orphan*/  pa_operation ;
struct TYPE_7__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ audio_output_t ;
struct TYPE_8__ {int /*<<< orphan*/  mainloop; int /*<<< orphan*/  last_date; int /*<<< orphan*/ * trigger; int /*<<< orphan*/ * stream; } ;
typedef  TYPE_2__ aout_sys_t ;

/* Variables and functions */
 scalar_t__ TimeGet (TYPE_1__*,scalar_t__*) ; 
 scalar_t__ VLC_TICK_FROM_SEC (int) ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  pa_operation_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pa_stream_drain (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pa_stream_is_corked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stream_start_now (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  stream_stop (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_pa_rttime_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_tick_sleep (scalar_t__) ; 

__attribute__((used)) static void Drain(audio_output_t *aout)
{
    aout_sys_t *sys = aout->sys;
    pa_stream *s = sys->stream;

    pa_threaded_mainloop_lock(sys->mainloop);

    if (unlikely(pa_stream_is_corked(s) > 0))
    {
        /* Drain while the stream is corked. It happens with very small input
         * when the stream is drained while the start is still being deferred.
         * In that case, we need start the stream before we actually drain it.
         * */
        if (sys->trigger != NULL)
        {
            vlc_pa_rttime_free(sys->mainloop, sys->trigger);
            sys->trigger = NULL;
        }
        stream_start_now(s, aout);
    }

    pa_operation *op = pa_stream_drain(s, NULL, NULL);
    if (op != NULL)
        pa_operation_unref(op);
    sys->last_date = VLC_TICK_INVALID;

    /* XXX: Loosy drain emulation.
     * See #18141: drain callback is never received */
    vlc_tick_t delay;
    if (TimeGet(aout, &delay) == 0 && delay <= VLC_TICK_FROM_SEC(5))
    {
        pa_threaded_mainloop_unlock(sys->mainloop);
        vlc_tick_sleep(delay);
        pa_threaded_mainloop_lock(sys->mainloop);
    }

    stream_stop(s, aout);
    pa_threaded_mainloop_unlock(sys->mainloop);
}