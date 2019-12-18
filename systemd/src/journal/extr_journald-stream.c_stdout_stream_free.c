#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ n_stdout_streams; int /*<<< orphan*/  stdout_streams_notify_queue; int /*<<< orphan*/  stdout_streams; } ;
struct TYPE_6__ {struct TYPE_6__* buffer; struct TYPE_6__* state_file; struct TYPE_6__* unit_id; struct TYPE_6__* identifier; struct TYPE_6__* label; int /*<<< orphan*/  fd; scalar_t__ event_source; TYPE_4__* server; scalar_t__ in_notify_queue; scalar_t__ context; } ;
typedef  TYPE_1__ StdoutStream ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  SD_EVENT_OFF ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  client_context_release (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_set_enabled (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ sd_event_source_unref (scalar_t__) ; 
 int /*<<< orphan*/  stdout_stream ; 
 int /*<<< orphan*/  stdout_stream_notify_queue ; 

void stdout_stream_free(StdoutStream *s) {
        if (!s)
                return;

        if (s->server) {

                if (s->context)
                        client_context_release(s->server, s->context);

                assert(s->server->n_stdout_streams > 0);
                s->server->n_stdout_streams--;
                LIST_REMOVE(stdout_stream, s->server->stdout_streams, s);

                if (s->in_notify_queue)
                        LIST_REMOVE(stdout_stream_notify_queue, s->server->stdout_streams_notify_queue, s);
        }

        if (s->event_source) {
                sd_event_source_set_enabled(s->event_source, SD_EVENT_OFF);
                s->event_source = sd_event_source_unref(s->event_source);
        }

        safe_close(s->fd);
        free(s->label);
        free(s->identifier);
        free(s->unit_id);
        free(s->state_file);
        free(s->buffer);

        free(s);
}