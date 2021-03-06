#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  pa_threaded_mainloop ;
typedef  int /*<<< orphan*/  pa_stream ;

/* Variables and functions */
#define  PA_STREAM_FAILED 130 
#define  PA_STREAM_READY 129 
#define  PA_STREAM_TERMINATED 128 
 int pa_stream_get_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_signal (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stream_state_cb(pa_stream *s, void *userdata)
{
    pa_threaded_mainloop *mainloop = userdata;

    switch (pa_stream_get_state(s)) {
        case PA_STREAM_READY:
        case PA_STREAM_FAILED:
        case PA_STREAM_TERMINATED:
            pa_threaded_mainloop_signal(mainloop, 0);
        default:
            break;
    }
}