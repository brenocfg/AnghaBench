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
struct server_pool {struct context* ctx; struct server_pool* owner; } ;
struct server {struct context* ctx; struct server* owner; } ;
struct context {int dummy; } ;
struct conn {struct server_pool* owner; scalar_t__ client; scalar_t__ proxy; } ;

/* Variables and functions */

struct context *
conn_to_ctx(struct conn *conn)
{
    struct server_pool *pool;

    if (conn->proxy || conn->client) {
        pool = conn->owner;
    } else {
        struct server *server = conn->owner;
        pool = server->owner;
    }

    return pool->ctx;
}