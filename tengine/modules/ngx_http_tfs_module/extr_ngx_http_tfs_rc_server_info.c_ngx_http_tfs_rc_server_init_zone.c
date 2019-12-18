#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * log_ctx; TYPE_1__* data; } ;
typedef  TYPE_3__ ngx_slab_pool_t ;
struct TYPE_14__ {size_t len; } ;
struct TYPE_10__ {TYPE_6__ name; scalar_t__ exists; scalar_t__ addr; } ;
struct TYPE_12__ {TYPE_2__ shm; TYPE_5__* data; } ;
typedef  TYPE_4__ ngx_shm_zone_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_tfs_rc_shctx_t ;
struct TYPE_13__ {TYPE_3__* shpool; TYPE_1__* sh; } ;
typedef  TYPE_5__ ngx_http_tfs_rc_ctx_t ;
struct TYPE_9__ {int /*<<< orphan*/  kp_queue; int /*<<< orphan*/  queue; int /*<<< orphan*/  sentinel; int /*<<< orphan*/  rbtree; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_http_tfs_rcs_rbtree_insert_value ; 
 int /*<<< orphan*/  ngx_queue_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_rbtree_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* ngx_slab_alloc (TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  ngx_sprintf (int /*<<< orphan*/ *,char*,TYPE_6__*) ; 

ngx_int_t
ngx_http_tfs_rc_server_init_zone(ngx_shm_zone_t *shm_zone, void *data)
{
    ngx_http_tfs_rc_ctx_t  *octx = data;

    size_t                 len;
    ngx_http_tfs_rc_ctx_t *ctx;

    ctx = shm_zone->data;

    if (octx) {

        ctx->sh = octx->sh;
        ctx->shpool = octx->shpool;

        return NGX_OK;
    }

    ctx->shpool = (ngx_slab_pool_t *) shm_zone->shm.addr;

    if (shm_zone->shm.exists) {
        ctx->sh = ctx->shpool->data;

        return NGX_OK;
    }

    ctx->sh = ngx_slab_alloc(ctx->shpool, sizeof(ngx_http_tfs_rc_shctx_t));
    if (ctx->sh == NULL) {
        return NGX_ERROR;
    }

    ctx->shpool->data = ctx->sh;

    ngx_rbtree_init(&ctx->sh->rbtree, &ctx->sh->sentinel,
                    ngx_http_tfs_rcs_rbtree_insert_value);
    ngx_queue_init(&ctx->sh->queue);
    ngx_queue_init(&ctx->sh->kp_queue);

    len = sizeof(" in tfs rc servers zone \"\"") + shm_zone->shm.name.len;

    ctx->shpool->log_ctx = ngx_slab_alloc(ctx->shpool, len);
    if (ctx->shpool->log_ctx == NULL) {
        return NGX_ERROR;
    }

    ngx_sprintf(ctx->shpool->log_ctx, " in tfs rc servers zone \"%V\"%Z",
                &shm_zone->shm.name);

    return NGX_OK;
}