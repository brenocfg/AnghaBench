#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_uint_t ;
struct TYPE_12__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  handler; } ;
typedef  TYPE_3__ ngx_pool_cleanup_t ;
struct TYPE_13__ {TYPE_1__* connection; scalar_t__ cached; } ;
typedef  TYPE_4__ ngx_peer_connection_t ;
struct TYPE_14__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* free ) (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_2__* scf; } ;
typedef  TYPE_5__ ngx_http_dyups_ctx_t ;
struct TYPE_15__ {int /*<<< orphan*/  log; } ;
struct TYPE_11__ {int /*<<< orphan*/  ref; } ;
struct TYPE_10__ {int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 TYPE_9__* ngx_cycle ; 
 int /*<<< orphan*/  ngx_http_dyups_clean_request ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_3__* ngx_pool_cleanup_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ngx_http_dyups_free_peer(ngx_peer_connection_t *pc, void *data,
    ngx_uint_t state)
{
    ngx_http_dyups_ctx_t  *ctx = data;

    ngx_pool_cleanup_t  *cln;


    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, ngx_cycle->log, 0,
                   "[dyups] dynamic upstream free handler count %i",
                   ctx->scf->ref);

    /* upstream connect failed */
    if (pc->connection == NULL) {
        goto done;
    }

    if (pc->cached) {
        goto done;
    }

    ctx->scf->ref++;

    cln = ngx_pool_cleanup_add(pc->connection->pool, 0);
    if (cln == NULL) {
        ngx_log_error(NGX_LOG_ERR, ngx_cycle->log, 0,
                      "[dyups] dynamic upstream free peer may cause memleak %i",
                      ctx->scf->ref);
        goto done;
    }

    cln->handler = ngx_http_dyups_clean_request;
    cln->data = &ctx->scf->ref;

 done:

    ctx->free(pc, ctx->data, state);
}