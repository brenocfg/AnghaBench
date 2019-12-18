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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  pa_threaded_mainloop ;
typedef  int /*<<< orphan*/  pa_context ;

/* Variables and functions */
 int /*<<< orphan*/  pa_context_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_context_set_event_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_context_set_state_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_context_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_unlock (int /*<<< orphan*/ *) ; 

void vlc_pa_disconnect (vlc_object_t *obj, pa_context *ctx,
                        pa_threaded_mainloop *mainloop)
{
    pa_threaded_mainloop_lock (mainloop);
    pa_context_disconnect (ctx);
    pa_context_set_event_callback (ctx, NULL, NULL);
    pa_context_set_state_callback (ctx, NULL, NULL);
    pa_context_unref (ctx);
    pa_threaded_mainloop_unlock (mainloop);

    pa_threaded_mainloop_stop (mainloop);
    pa_threaded_mainloop_free (mainloop);
    (void) obj;
}