#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  client_to_server_buffer_size; int /*<<< orphan*/  client_to_server_buffer; int /*<<< orphan*/  server_to_client_buffer_size; int /*<<< orphan*/  server_to_client_buffer; } ;
typedef  TYPE_1__ Connection ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int connection_create_pipes (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int connection_enable_event_sources (TYPE_1__*) ; 
 int /*<<< orphan*/  connection_free (TYPE_1__*) ; 

__attribute__((used)) static int connection_complete(Connection *c) {
        int r;

        assert(c);

        r = connection_create_pipes(c, c->server_to_client_buffer, &c->server_to_client_buffer_size);
        if (r < 0)
                goto fail;

        r = connection_create_pipes(c, c->client_to_server_buffer, &c->client_to_server_buffer_size);
        if (r < 0)
                goto fail;

        r = connection_enable_event_sources(c);
        if (r < 0)
                goto fail;

        return 0;

fail:
        connection_free(c);
        return 0; /* ignore errors, continue serving */
}