#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  pa_stream ;
struct TYPE_3__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_4__ {int /*<<< orphan*/  mainloop; int /*<<< orphan*/  context; int /*<<< orphan*/ * stream; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_stream_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_stream_set_buffer_attr_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_stream_set_moved_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_stream_set_overflow_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_stream_set_read_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_stream_set_started_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_stream_set_state_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_stream_set_suspended_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_stream_set_underflow_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_stream_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_pa_disconnect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Close (vlc_object_t *obj)
{
    demux_t *demux = (demux_t *)obj;
    demux_sys_t *sys = demux->p_sys;
    pa_stream *s = sys->stream;

    if (likely(s != NULL)) {
        pa_threaded_mainloop_lock(sys->mainloop);
        pa_stream_disconnect(s);
        pa_stream_set_state_callback(s, NULL, NULL);
        pa_stream_set_read_callback(s, NULL, NULL);
        pa_stream_set_buffer_attr_callback(s, NULL, NULL);
        pa_stream_set_moved_callback(s, NULL, NULL);
        pa_stream_set_overflow_callback(s, NULL, NULL);
        pa_stream_set_started_callback(s, NULL, NULL);
        pa_stream_set_suspended_callback(s, NULL, NULL);
        pa_stream_set_underflow_callback(s, NULL, NULL);
        pa_stream_unref(s);
        pa_threaded_mainloop_unlock(sys->mainloop);
    }

    vlc_pa_disconnect(obj, sys->context, sys->mainloop);
}