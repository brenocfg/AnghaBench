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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct server_pool {int dummy; } ;
struct server {int dummy; } ;
struct context {int dummy; } ;
struct conn {int dummy; } ;
typedef  scalar_t__ rstatus_t ;

/* Variables and functions */
 scalar_t__ NC_OK ; 
 int /*<<< orphan*/  server_close (struct context*,struct conn*) ; 
 struct conn* server_conn (struct server*) ; 
 scalar_t__ server_connect (struct context*,struct server*,struct conn*) ; 
 struct server* server_pool_server (struct server_pool*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ server_pool_update (struct server_pool*) ; 

struct conn *
server_pool_conn(struct context *ctx, struct server_pool *pool, uint8_t *key,
                 uint32_t keylen)
{
    rstatus_t status;
    struct server *server;
    struct conn *conn;

    status = server_pool_update(pool);
    if (status != NC_OK) {
        return NULL;
    }

    /* from a given {key, keylen} pick a server from pool */
    server = server_pool_server(pool, key, keylen);
    if (server == NULL) {
        return NULL;
    }

    /* pick a connection to a given server */
    conn = server_conn(server);
    if (conn == NULL) {
        return NULL;
    }

    status = server_connect(ctx, server, conn);
    if (status != NC_OK) {
        server_close(ctx, conn);
        return NULL;
    }

    return conn;
}