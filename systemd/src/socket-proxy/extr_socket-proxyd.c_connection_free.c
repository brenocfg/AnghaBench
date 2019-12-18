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
struct TYPE_8__ {int /*<<< orphan*/  resolve_query; int /*<<< orphan*/  client_to_server_buffer; int /*<<< orphan*/  server_to_client_buffer; int /*<<< orphan*/  client_fd; int /*<<< orphan*/  server_fd; int /*<<< orphan*/  client_event_source; int /*<<< orphan*/  server_event_source; TYPE_1__* context; } ;
struct TYPE_7__ {int /*<<< orphan*/  connections; } ;
typedef  TYPE_2__ Connection ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_close_pair (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_resolve_query_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_remove (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void connection_free(Connection *c) {
        assert(c);

        if (c->context)
                set_remove(c->context->connections, c);

        sd_event_source_unref(c->server_event_source);
        sd_event_source_unref(c->client_event_source);

        safe_close(c->server_fd);
        safe_close(c->client_fd);

        safe_close_pair(c->server_to_client_buffer);
        safe_close_pair(c->client_to_server_buffer);

        sd_resolve_query_unref(c->resolve_query);

        free(c);
}