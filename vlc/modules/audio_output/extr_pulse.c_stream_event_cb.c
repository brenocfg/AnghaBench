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
typedef  int /*<<< orphan*/  pa_stream ;
typedef  int /*<<< orphan*/  pa_proplist ;
typedef  int /*<<< orphan*/  audio_output_t ;

/* Variables and functions */
 int /*<<< orphan*/  AOUT_RESTART_OUTPUT ; 
 int /*<<< orphan*/  PA_STREAM_EVENT_FORMAT_LOST ; 
 int /*<<< orphan*/  PA_STREAM_EVENT_REQUEST_CORK ; 
 int /*<<< orphan*/  PA_STREAM_EVENT_REQUEST_UNCORK ; 
 int /*<<< orphan*/  aout_PolicyReport (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  aout_RestartRequest (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stream_event_cb(pa_stream *s, const char *name, pa_proplist *pl,
                            void *userdata)
{
    audio_output_t *aout = userdata;

    if (!strcmp(name, PA_STREAM_EVENT_REQUEST_CORK))
        aout_PolicyReport(aout, true);
    else
    if (!strcmp(name, PA_STREAM_EVENT_REQUEST_UNCORK))
        aout_PolicyReport(aout, false);
    else
    /* FIXME: expose aout_Restart() directly */
    if (!strcmp(name, PA_STREAM_EVENT_FORMAT_LOST)) {
        msg_Dbg (aout, "format lost");
        aout_RestartRequest (aout, AOUT_RESTART_OUTPUT);
    } else
        msg_Warn (aout, "unhandled stream event \"%s\"", name);
    (void) s;
    (void) pl;
}