#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/ * off_t ;
typedef  int /*<<< orphan*/  ngx_queue_t ;
struct TYPE_11__ {int cached; TYPE_5__* connection; int /*<<< orphan*/  log; int /*<<< orphan*/  socklen; scalar_t__ sockaddr; } ;
typedef  TYPE_3__ ngx_peer_connection_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_12__ {int /*<<< orphan*/  queue; int /*<<< orphan*/  index; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; TYPE_5__* connection; } ;
typedef  TYPE_4__ ngx_http_upstream_keepalive_cache_t ;
struct TYPE_13__ {TYPE_8__* read; TYPE_2__* pool; TYPE_1__* write; int /*<<< orphan*/  log; scalar_t__ idle; } ;
typedef  TYPE_5__ ngx_connection_t ;
struct TYPE_14__ {scalar_t__ timer_set; int /*<<< orphan*/  log; } ;
struct TYPE_10__ {int /*<<< orphan*/  log; } ;
struct TYPE_9__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_DONE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_del_timer (TYPE_8__*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_5__*) ; 
 scalar_t__ ngx_memn2cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_queue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_queue_insert_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ngx_queue_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_queue_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ngx_queue_sentinel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_do_get_keepalive_peer(ngx_peer_connection_t *pc,
    ngx_queue_t *cache, ngx_queue_t *free, off_t offset)
{
    ngx_queue_t       *q;
    ngx_connection_t  *c;

    ngx_http_upstream_keepalive_cache_t  *item;

    for (q = ngx_queue_head(cache);
         q != ngx_queue_sentinel(cache);
         q = ngx_queue_next(q))
    {
        item = (ngx_http_upstream_keepalive_cache_t *) ((u_char *) q - offset);
        c = item->connection;

        if (ngx_memn2cmp((u_char *) &item->sockaddr, (u_char *) pc->sockaddr,
                         item->socklen, pc->socklen)
            == 0)
        {
            ngx_queue_remove(&item->index);
            ngx_queue_remove(&item->queue);
            ngx_queue_insert_head(free, &item->queue);

            ngx_log_debug1(NGX_LOG_DEBUG_HTTP, pc->log, 0,
                           "get keepalive peer: using connection %p", c);

            c->idle = 0;
            c->log = pc->log;
            c->read->log = pc->log;
            c->write->log = pc->log;
            c->pool->log = pc->log;

            if (c->read->timer_set) {
                ngx_del_timer(c->read);
            }

            pc->connection = c;
            pc->cached = 1;

            return NGX_DONE;
        }
    }

    return NGX_OK;
}