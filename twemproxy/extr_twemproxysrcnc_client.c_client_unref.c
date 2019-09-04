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
struct server_pool {scalar_t__ nc_conn_q; TYPE_1__ name; int /*<<< orphan*/  c_conn_q; } ;
struct conn {struct server_pool* owner; int /*<<< orphan*/  proxy; scalar_t__ client; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  LOG_VVERB ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conn_tqe ; 
 int /*<<< orphan*/  log_debug (int /*<<< orphan*/ ,char*,struct conn*,struct server_pool*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
client_unref(struct conn *conn)
{
    struct server_pool *pool;

    ASSERT(conn->client && !conn->proxy);
    ASSERT(conn->owner != NULL);

    pool = conn->owner;
    conn->owner = NULL;

    ASSERT(pool->nc_conn_q != 0);
    pool->nc_conn_q--;
    TAILQ_REMOVE(&pool->c_conn_q, conn, conn_tqe);

    log_debug(LOG_VVERB, "unref conn %p owner %p from pool '%.*s'", conn,
              pool, pool->name.len, pool->name.data);
}