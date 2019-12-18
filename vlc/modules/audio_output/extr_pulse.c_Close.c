#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct sink {struct sink* sink_force; struct sink* next; struct sink* sinks; int /*<<< orphan*/  mainloop; int /*<<< orphan*/ * context; } ;
typedef  int /*<<< orphan*/  pa_context ;
struct TYPE_2__ {struct sink* sys; } ;
typedef  TYPE_1__ audio_output_t ;
typedef  struct sink aout_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct sink*) ; 
 int /*<<< orphan*/  pa_context_set_subscribe_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_pa_disconnect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Close(vlc_object_t *obj)
{
    audio_output_t *aout = (audio_output_t *)obj;
    aout_sys_t *sys = aout->sys;
    pa_context *ctx = sys->context;

    pa_threaded_mainloop_lock(sys->mainloop);
    pa_context_set_subscribe_callback(sys->context, NULL, NULL);
    pa_threaded_mainloop_unlock(sys->mainloop);
    vlc_pa_disconnect(obj, ctx, sys->mainloop);

    for (struct sink *sink = sys->sinks, *next; sink != NULL; sink = next)
    {
        next = sink->next;
        free(sink);
    }
    free(sys->sink_force);
    free(sys);
}