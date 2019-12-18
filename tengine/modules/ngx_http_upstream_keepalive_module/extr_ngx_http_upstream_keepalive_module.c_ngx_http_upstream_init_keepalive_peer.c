#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_upstream_srv_conf_t ;
struct TYPE_17__ {scalar_t__ (* original_init_peer ) (TYPE_6__*,int /*<<< orphan*/ *) ;scalar_t__ max_key_length; int /*<<< orphan*/  slice_key; scalar_t__ index; } ;
typedef  TYPE_4__ ngx_http_upstream_keepalive_srv_conf_t ;
struct TYPE_20__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_18__ {int /*<<< orphan*/  original_save_session; int /*<<< orphan*/  original_set_session; int /*<<< orphan*/  original_free_peer; int /*<<< orphan*/  original_get_peer; struct TYPE_18__* data; TYPE_3__* upstream; TYPE_9__ key; int /*<<< orphan*/  hash; TYPE_6__* request; TYPE_4__* conf; } ;
typedef  TYPE_5__ ngx_http_upstream_keepalive_peer_data_t ;
struct TYPE_19__ {TYPE_3__* upstream; TYPE_1__* connection; int /*<<< orphan*/  pool; } ;
typedef  TYPE_6__ ngx_http_request_t ;
struct TYPE_15__ {int /*<<< orphan*/  save_session; int /*<<< orphan*/  set_session; int /*<<< orphan*/  free; int /*<<< orphan*/  get; TYPE_5__* data; } ;
struct TYPE_16__ {TYPE_2__ peer; } ;
struct TYPE_14__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_http_complex_value (TYPE_6__*,int /*<<< orphan*/ ,TYPE_9__*) ; 
 TYPE_4__* ngx_http_conf_upstream_srv_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_upstream_free_keepalive_peer ; 
 int /*<<< orphan*/  ngx_http_upstream_get_keepalive_peer ; 
 int /*<<< orphan*/  ngx_http_upstream_keepalive_module ; 
 int /*<<< orphan*/  ngx_http_upstream_keepalive_save_session ; 
 int /*<<< orphan*/  ngx_http_upstream_keepalive_set_session ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_9__*) ; 
 int /*<<< orphan*/  ngx_murmur_hash2 (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_5__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (TYPE_6__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_init_keepalive_peer(ngx_http_request_t *r,
    ngx_http_upstream_srv_conf_t *us)
{
    ngx_http_upstream_keepalive_peer_data_t  *kp;
    ngx_http_upstream_keepalive_srv_conf_t   *kcf;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "init keepalive peer");

    kcf = ngx_http_conf_upstream_srv_conf(us,
                                          ngx_http_upstream_keepalive_module);

    kp = ngx_pcalloc(r->pool, sizeof(ngx_http_upstream_keepalive_peer_data_t));
    if (kp == NULL) {
        return NGX_ERROR;
    }

    if (kcf->original_init_peer(r, us) != NGX_OK) {
        return NGX_ERROR;
    }

    kp->conf = kcf;
    kp->request = r;

    if (kcf->index) {
        if (ngx_http_complex_value(r, kcf->slice_key, &kp->key) != NGX_OK) {
            return NGX_ERROR;
        }

        if (kp->key.len > kcf->max_key_length) {
            kp->key.len = kcf->max_key_length;
        }

        kp->hash = ngx_murmur_hash2(kp->key.data, kp->key.len);

        ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "init keepalive slice \"%V\"", &kp->key);
    }

    kp->upstream = r->upstream;
    kp->data = r->upstream->peer.data;
    kp->original_get_peer = r->upstream->peer.get;
    kp->original_free_peer = r->upstream->peer.free;

    r->upstream->peer.data = kp;
    r->upstream->peer.get = ngx_http_upstream_get_keepalive_peer;
    r->upstream->peer.free = ngx_http_upstream_free_keepalive_peer;

#if (NGX_HTTP_SSL)
    kp->original_set_session = r->upstream->peer.set_session;
    kp->original_save_session = r->upstream->peer.save_session;
    r->upstream->peer.set_session = ngx_http_upstream_keepalive_set_session;
    r->upstream->peer.save_session = ngx_http_upstream_keepalive_save_session;
#endif

    return NGX_OK;
}