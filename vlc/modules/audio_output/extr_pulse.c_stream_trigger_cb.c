#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct timeval {int dummy; } ;
typedef  int /*<<< orphan*/  pa_time_event ;
typedef  int /*<<< orphan*/  pa_mainloop_api ;
struct TYPE_5__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ audio_output_t ;
struct TYPE_6__ {int /*<<< orphan*/  stream; int /*<<< orphan*/ * trigger; int /*<<< orphan*/  mainloop; } ;
typedef  TYPE_2__ aout_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stream_start_now (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_pa_rttime_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stream_trigger_cb(pa_mainloop_api *api, pa_time_event *e,
                              const struct timeval *tv, void *userdata)
{
    audio_output_t *aout = userdata;
    aout_sys_t *sys = aout->sys;

    assert (sys->trigger == e);

    msg_Dbg(aout, "starting deferred");
    vlc_pa_rttime_free(sys->mainloop, sys->trigger);
    sys->trigger = NULL;
    stream_start_now(sys->stream, aout);
    (void) api; (void) e; (void) tv;
}