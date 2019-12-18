#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_upstream_srv_conf_t ;
struct TYPE_10__ {TYPE_2__* upstream; int /*<<< orphan*/  pool; } ;
typedef  TYPE_3__ ngx_http_request_t ;
typedef  int /*<<< orphan*/  ngx_http_lua_srv_conf_t ;
struct TYPE_11__ {TYPE_3__* request; int /*<<< orphan*/ * conf; int /*<<< orphan*/  rrp; } ;
typedef  TYPE_4__ ngx_http_lua_balancer_peer_data_t ;
struct TYPE_8__ {int /*<<< orphan*/  save_session; int /*<<< orphan*/  set_session; int /*<<< orphan*/  free; int /*<<< orphan*/  get; int /*<<< orphan*/ * data; } ;
struct TYPE_9__ {TYPE_1__ peer; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/ * ngx_http_conf_upstream_srv_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_balancer_free_peer ; 
 int /*<<< orphan*/  ngx_http_lua_balancer_get_peer ; 
 int /*<<< orphan*/  ngx_http_lua_balancer_save_session ; 
 int /*<<< orphan*/  ngx_http_lua_balancer_set_session ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 scalar_t__ ngx_http_upstream_init_round_robin_peer (TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_4__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_lua_balancer_init_peer(ngx_http_request_t *r,
    ngx_http_upstream_srv_conf_t *us)
{
    ngx_http_lua_srv_conf_t            *bcf;
    ngx_http_lua_balancer_peer_data_t  *bp;

    bp = ngx_pcalloc(r->pool, sizeof(ngx_http_lua_balancer_peer_data_t));
    if (bp == NULL) {
        return NGX_ERROR;
    }

    r->upstream->peer.data = &bp->rrp;

    if (ngx_http_upstream_init_round_robin_peer(r, us) != NGX_OK) {
        return NGX_ERROR;
    }

    r->upstream->peer.get = ngx_http_lua_balancer_get_peer;
    r->upstream->peer.free = ngx_http_lua_balancer_free_peer;

#if (NGX_HTTP_SSL)
    r->upstream->peer.set_session = ngx_http_lua_balancer_set_session;
    r->upstream->peer.save_session = ngx_http_lua_balancer_save_session;
#endif

    bcf = ngx_http_conf_upstream_srv_conf(us, ngx_http_lua_module);

    bp->conf = bcf;
    bp->request = r;

    return NGX_OK;
}