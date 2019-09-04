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
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct server {TYPE_1__ pname; } ;
struct context {int dummy; } ;
struct conn {int connected; int /*<<< orphan*/  sd; int /*<<< orphan*/  (* post_connect ) (struct context*,struct conn*,struct server*) ;scalar_t__ connecting; int /*<<< orphan*/  proxy; int /*<<< orphan*/  client; struct server* owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  log_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  server_connections ; 
 int /*<<< orphan*/  stats_server_incr (struct context*,struct server*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct context*,struct conn*,struct server*) ; 

void
server_connected(struct context *ctx, struct conn *conn)
{
    struct server *server = conn->owner;

    ASSERT(!conn->client && !conn->proxy);
    ASSERT(conn->connecting && !conn->connected);

    stats_server_incr(ctx, server, server_connections);

    conn->connecting = 0;
    conn->connected = 1;

    conn->post_connect(ctx, conn, server);

    log_debug(LOG_INFO, "connected on s %d to server '%.*s'", conn->sd,
              server->pname.len, server->pname.data);
}