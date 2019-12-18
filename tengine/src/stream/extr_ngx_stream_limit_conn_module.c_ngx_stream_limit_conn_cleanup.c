#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ conn; } ;
typedef  TYPE_3__ ngx_stream_limit_conn_node_t ;
struct TYPE_14__ {int /*<<< orphan*/  rbtree; } ;
typedef  TYPE_4__ ngx_stream_limit_conn_ctx_t ;
struct TYPE_15__ {TYPE_2__* shm_zone; TYPE_7__* node; } ;
typedef  TYPE_5__ ngx_stream_limit_conn_cleanup_t ;
struct TYPE_16__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_6__ ngx_slab_pool_t ;
struct TYPE_17__ {int /*<<< orphan*/  key; int /*<<< orphan*/  color; } ;
typedef  TYPE_7__ ngx_rbtree_node_t ;
struct TYPE_11__ {int /*<<< orphan*/  log; scalar_t__ addr; } ;
struct TYPE_12__ {TYPE_1__ shm; TYPE_4__* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_STREAM ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ngx_rbtree_delete (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_shmtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_shmtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_slab_free_locked (TYPE_6__*,TYPE_7__*) ; 

__attribute__((used)) static void
ngx_stream_limit_conn_cleanup(void *data)
{
    ngx_stream_limit_conn_cleanup_t  *lccln = data;

    ngx_slab_pool_t               *shpool;
    ngx_rbtree_node_t             *node;
    ngx_stream_limit_conn_ctx_t   *ctx;
    ngx_stream_limit_conn_node_t  *lc;

    ctx = lccln->shm_zone->data;
    shpool = (ngx_slab_pool_t *) lccln->shm_zone->shm.addr;
    node = lccln->node;
    lc = (ngx_stream_limit_conn_node_t *) &node->color;

    ngx_shmtx_lock(&shpool->mutex);

    ngx_log_debug2(NGX_LOG_DEBUG_STREAM, lccln->shm_zone->shm.log, 0,
                   "limit conn cleanup: %08Xi %d", node->key, lc->conn);

    lc->conn--;

    if (lc->conn == 0) {
        ngx_rbtree_delete(ctx->rbtree, node);
        ngx_slab_free_locked(shpool, node);
    }

    ngx_shmtx_unlock(&shpool->mutex);
}