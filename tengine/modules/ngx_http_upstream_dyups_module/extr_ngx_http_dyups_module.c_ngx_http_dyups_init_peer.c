#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_15__ ;
typedef  struct TYPE_16__   TYPE_12__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  handler; } ;
typedef  TYPE_3__ ngx_pool_cleanup_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_21__ {TYPE_6__** srv_conf; } ;
typedef  TYPE_4__ ngx_http_upstream_srv_conf_t ;
struct TYPE_22__ {int /*<<< orphan*/  pool; TYPE_2__* upstream; } ;
typedef  TYPE_5__ ngx_http_request_t ;
struct TYPE_23__ {scalar_t__ (* init ) (TYPE_5__*,TYPE_4__*) ;int /*<<< orphan*/  ref; } ;
typedef  TYPE_6__ ngx_http_dyups_upstream_srv_conf_t ;
struct TYPE_24__ {int /*<<< orphan*/  free; int /*<<< orphan*/  get; struct TYPE_24__* data; TYPE_6__* scf; } ;
typedef  TYPE_7__ ngx_http_dyups_ctx_t ;
struct TYPE_18__ {int /*<<< orphan*/  save_session; int /*<<< orphan*/  set_session; int /*<<< orphan*/  free; int /*<<< orphan*/  get; TYPE_7__* data; } ;
struct TYPE_19__ {TYPE_1__ peer; } ;
struct TYPE_17__ {int /*<<< orphan*/  log; } ;
struct TYPE_16__ {size_t ctx_index; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 TYPE_15__* ngx_cycle ; 
 int /*<<< orphan*/  ngx_http_dyups_clean_request ; 
 int /*<<< orphan*/  ngx_http_dyups_free_peer ; 
 int /*<<< orphan*/  ngx_http_dyups_get_peer ; 
 TYPE_12__ ngx_http_dyups_module ; 
 int /*<<< orphan*/  ngx_http_dyups_save_peer_session ; 
 int /*<<< orphan*/  ngx_http_dyups_set_peer_session ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 TYPE_7__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 TYPE_3__* ngx_pool_cleanup_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_5__*,TYPE_4__*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_dyups_init_peer(ngx_http_request_t *r,
    ngx_http_upstream_srv_conf_t *us)
{
    ngx_int_t                            rc;
    ngx_pool_cleanup_t                  *cln;
    ngx_http_dyups_ctx_t                *ctx;
    ngx_http_dyups_upstream_srv_conf_t  *dscf;

    dscf = us->srv_conf[ngx_http_dyups_module.ctx_index];

    rc = dscf->init(r, us);

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, ngx_cycle->log, 0,
                   "[dyups] dynamic upstream init peer: %i",
                   rc);

    if (rc != NGX_OK) {
        return rc;
    }

    ctx = ngx_pcalloc(r->pool, sizeof(ngx_http_dyups_ctx_t));
    if (ctx == NULL) {
        return NGX_ERROR;
    }

    ctx->scf = dscf;
    ctx->data = r->upstream->peer.data;
    ctx->get = r->upstream->peer.get;
    ctx->free = r->upstream->peer.free;

    r->upstream->peer.data = ctx;
    r->upstream->peer.get = ngx_http_dyups_get_peer;
    r->upstream->peer.free = ngx_http_dyups_free_peer;

#if (NGX_HTTP_SSL)
    r->upstream->peer.set_session = ngx_http_dyups_set_peer_session;
    r->upstream->peer.save_session = ngx_http_dyups_save_peer_session;
#endif

    cln = ngx_pool_cleanup_add(r->pool, 0);
    if (cln == NULL) {
        return NGX_ERROR;
    }

    dscf->ref++;

    cln->handler = ngx_http_dyups_clean_request;
    cln->data = &dscf->ref;

    return NGX_OK;
}