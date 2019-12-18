#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_upstream_srv_conf_t ;
struct TYPE_14__ {scalar_t__ (* original_init_peer ) (TYPE_6__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_4__ ngx_http_upstream_dynamic_srv_conf_t ;
struct TYPE_15__ {int /*<<< orphan*/  original_save_session; int /*<<< orphan*/  original_set_session; TYPE_6__* request; int /*<<< orphan*/  original_free_peer; int /*<<< orphan*/  original_get_peer; struct TYPE_15__* data; TYPE_3__* upstream; TYPE_4__* conf; } ;
typedef  TYPE_5__ ngx_http_upstream_dynamic_peer_data_t ;
struct TYPE_16__ {TYPE_3__* upstream; int /*<<< orphan*/  pool; TYPE_1__* connection; } ;
typedef  TYPE_6__ ngx_http_request_t ;
struct TYPE_12__ {int /*<<< orphan*/  save_session; int /*<<< orphan*/  set_session; int /*<<< orphan*/  free; int /*<<< orphan*/  get; TYPE_5__* data; } ;
struct TYPE_13__ {TYPE_2__ peer; } ;
struct TYPE_11__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 TYPE_4__* ngx_http_conf_upstream_srv_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_upstream_dynamic_module ; 
 int /*<<< orphan*/  ngx_http_upstream_dynamic_save_session ; 
 int /*<<< orphan*/  ngx_http_upstream_dynamic_set_session ; 
 int /*<<< orphan*/  ngx_http_upstream_free_dynamic_peer ; 
 int /*<<< orphan*/  ngx_http_upstream_get_dynamic_peer ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_5__* ngx_palloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (TYPE_6__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_init_dynamic_peer(ngx_http_request_t *r,
    ngx_http_upstream_srv_conf_t *us)
{
    ngx_http_upstream_dynamic_peer_data_t  *dp;
    ngx_http_upstream_dynamic_srv_conf_t   *dcf;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "init dynamic peer");

    dcf = ngx_http_conf_upstream_srv_conf(us,
                                          ngx_http_upstream_dynamic_module);

    dp = ngx_palloc(r->pool, sizeof(ngx_http_upstream_dynamic_peer_data_t));
    if (dp == NULL) {
        return NGX_ERROR;
    }

    if (dcf->original_init_peer(r, us) != NGX_OK) {
        return NGX_ERROR;
    }

    dp->conf = dcf;
    dp->upstream = r->upstream;
    dp->data = r->upstream->peer.data;
    dp->original_get_peer = r->upstream->peer.get;
    dp->original_free_peer = r->upstream->peer.free;
    dp->request = r;

    r->upstream->peer.data = dp;
    r->upstream->peer.get = ngx_http_upstream_get_dynamic_peer;
    r->upstream->peer.free = ngx_http_upstream_free_dynamic_peer;

#if (NGX_HTTP_SSL)
    dp->original_set_session = r->upstream->peer.set_session;
    dp->original_save_session = r->upstream->peer.save_session;
    r->upstream->peer.set_session = ngx_http_upstream_dynamic_set_session;
    r->upstream->peer.save_session = ngx_http_upstream_dynamic_save_session;
#endif

    return NGX_OK;
}