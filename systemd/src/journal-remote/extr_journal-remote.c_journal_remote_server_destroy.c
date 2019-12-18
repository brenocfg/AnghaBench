#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t sources_size; int /*<<< orphan*/  events; int /*<<< orphan*/  listen_event; int /*<<< orphan*/  sigint_event; int /*<<< orphan*/  sigterm_event; int /*<<< orphan*/  writers; int /*<<< orphan*/  _single_writer; scalar_t__ sources; int /*<<< orphan*/  daemons; } ;
typedef  TYPE_1__ RemoteServer ;

/* Variables and functions */
 int /*<<< orphan*/  MHDDaemonWrapper_free ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  hashmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap_free_with_destructor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* journal_remote_server_global ; 
 int /*<<< orphan*/  remove_source (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writer_unref (int /*<<< orphan*/ ) ; 

void journal_remote_server_destroy(RemoteServer *s) {
        size_t i;

#if HAVE_MICROHTTPD
        hashmap_free_with_destructor(s->daemons, MHDDaemonWrapper_free);
#endif

        assert(s->sources_size == 0 || s->sources);
        for (i = 0; i < s->sources_size; i++)
                remove_source(s, i);
        free(s->sources);

        writer_unref(s->_single_writer);
        hashmap_free(s->writers);

        sd_event_source_unref(s->sigterm_event);
        sd_event_source_unref(s->sigint_event);
        sd_event_source_unref(s->listen_event);
        sd_event_unref(s->events);

        if (s == journal_remote_server_global)
                journal_remote_server_global = NULL;

        /* fds that we're listening on remain open... */
}