#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_upstream_srv_conf_t ;
struct TYPE_18__ {int /*<<< orphan*/ * ranges; scalar_t__ two; } ;
typedef  TYPE_5__ ngx_http_upstream_random_srv_conf_t ;
struct TYPE_17__ {TYPE_9__* peers; } ;
struct TYPE_19__ {TYPE_4__ rrp; scalar_t__ tries; TYPE_5__* conf; } ;
typedef  TYPE_6__ ngx_http_upstream_random_peer_data_t ;
struct TYPE_20__ {TYPE_3__* upstream; int /*<<< orphan*/  pool; TYPE_1__* connection; } ;
typedef  TYPE_7__ ngx_http_request_t ;
struct TYPE_21__ {scalar_t__ shpool; } ;
struct TYPE_15__ {int /*<<< orphan*/  get; TYPE_4__* data; } ;
struct TYPE_16__ {TYPE_2__ peer; } ;
struct TYPE_14__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 TYPE_5__* ngx_http_conf_upstream_srv_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_upstream_get_random2_peer ; 
 int /*<<< orphan*/  ngx_http_upstream_get_random_peer ; 
 scalar_t__ ngx_http_upstream_init_round_robin_peer (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_upstream_random_module ; 
 int /*<<< orphan*/  ngx_http_upstream_rr_peers_rlock (TYPE_9__*) ; 
 int /*<<< orphan*/  ngx_http_upstream_rr_peers_unlock (TYPE_9__*) ; 
 scalar_t__ ngx_http_upstream_update_random (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_6__* ngx_palloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_init_random_peer(ngx_http_request_t *r,
    ngx_http_upstream_srv_conf_t *us)
{
    ngx_http_upstream_random_srv_conf_t   *rcf;
    ngx_http_upstream_random_peer_data_t  *rp;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "init random peer");

    rcf = ngx_http_conf_upstream_srv_conf(us, ngx_http_upstream_random_module);

    rp = ngx_palloc(r->pool, sizeof(ngx_http_upstream_random_peer_data_t));
    if (rp == NULL) {
        return NGX_ERROR;
    }

    r->upstream->peer.data = &rp->rrp;

    if (ngx_http_upstream_init_round_robin_peer(r, us) != NGX_OK) {
        return NGX_ERROR;
    }

    if (rcf->two) {
        r->upstream->peer.get = ngx_http_upstream_get_random2_peer;

    } else {
        r->upstream->peer.get = ngx_http_upstream_get_random_peer;
    }

    rp->conf = rcf;
    rp->tries = 0;

    ngx_http_upstream_rr_peers_rlock(rp->rrp.peers);

#if (NGX_HTTP_UPSTREAM_ZONE)
    if (rp->rrp.peers->shpool && rcf->ranges == NULL) {
        if (ngx_http_upstream_update_random(NULL, us) != NGX_OK) {
            ngx_http_upstream_rr_peers_unlock(rp->rrp.peers);
            return NGX_ERROR;
        }
    }
#endif

    ngx_http_upstream_rr_peers_unlock(rp->rrp.peers);

    return NGX_OK;
}