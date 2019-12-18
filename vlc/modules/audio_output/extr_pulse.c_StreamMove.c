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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  pa_operation ;
struct TYPE_7__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ audio_output_t ;
struct TYPE_8__ {int /*<<< orphan*/  mainloop; int /*<<< orphan*/  context; int /*<<< orphan*/ * stream; int /*<<< orphan*/  sink_force; } ;
typedef  TYPE_2__ aout_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  aout_DeviceReport (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,char const*) ; 
 int /*<<< orphan*/ * pa_context_move_sink_input_by_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_operation_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_stream_get_index (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 int /*<<< orphan*/  vlc_pa_error (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int StreamMove(audio_output_t *aout, const char *name)
{
    aout_sys_t *sys = aout->sys;

    if (sys->stream == NULL)
    {
        msg_Dbg(aout, "will connect to sink %s", name);
        free(sys->sink_force);
        sys->sink_force = strdup(name);
        aout_DeviceReport(aout, name);
        return 0;
    }

    pa_operation *op;
    uint32_t idx = pa_stream_get_index(sys->stream);

    pa_threaded_mainloop_lock(sys->mainloop);
    op = pa_context_move_sink_input_by_name(sys->context, idx, name,
                                            NULL, NULL);
    if (likely(op != NULL)) {
        pa_operation_unref(op);
        msg_Dbg(aout, "moving to sink %s", name);
    } else
        vlc_pa_error(aout, "cannot move sink input", sys->context);
    pa_threaded_mainloop_unlock(sys->mainloop);

    return (op != NULL) ? 0 : -1;
}