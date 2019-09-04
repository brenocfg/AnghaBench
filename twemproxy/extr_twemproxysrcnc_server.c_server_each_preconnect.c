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
struct server_pool {int /*<<< orphan*/  ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct server {TYPE_1__ pname; struct server_pool* owner; } ;
struct conn {int dummy; } ;
typedef  scalar_t__ rstatus_t ;

/* Variables and functions */
 scalar_t__ NC_ENOMEM ; 
 scalar_t__ NC_OK ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  log_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  server_close (int /*<<< orphan*/ ,struct conn*) ; 
 struct conn* server_conn (struct server*) ; 
 scalar_t__ server_connect (int /*<<< orphan*/ ,struct server*,struct conn*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static rstatus_t
server_each_preconnect(void *elem, void *data)
{
    rstatus_t status;
    struct server *server;
    struct server_pool *pool;
    struct conn *conn;

    server = elem;
    pool = server->owner;

    conn = server_conn(server);
    if (conn == NULL) {
        return NC_ENOMEM;
    }

    status = server_connect(pool->ctx, server, conn);
    if (status != NC_OK) {
        log_warn("connect to server '%.*s' failed, ignored: %s",
                 server->pname.len, server->pname.data, strerror(errno));
        server_close(pool->ctx, conn);
    }

    return NC_OK;
}