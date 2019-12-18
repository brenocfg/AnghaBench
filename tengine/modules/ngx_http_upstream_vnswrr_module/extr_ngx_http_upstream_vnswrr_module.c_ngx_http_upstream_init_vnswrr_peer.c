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
typedef  int /*<<< orphan*/  ngx_http_upstream_vnswrr_srv_conf_t ;
struct TYPE_10__ {int /*<<< orphan*/  rrp; int /*<<< orphan*/ * uvnscf; } ;
typedef  TYPE_3__ ngx_http_upstream_vnswrr_peer_data_t ;
typedef  int /*<<< orphan*/  ngx_http_upstream_srv_conf_t ;
struct TYPE_11__ {TYPE_1__* upstream; int /*<<< orphan*/  pool; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_9__ {int /*<<< orphan*/  get; int /*<<< orphan*/ * data; } ;
struct TYPE_8__ {TYPE_2__ peer; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/ * ngx_http_conf_upstream_srv_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_upstream_get_vnswrr_peer ; 
 scalar_t__ ngx_http_upstream_init_round_robin_peer (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_upstream_vnswrr_module ; 
 TYPE_3__* ngx_palloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_init_vnswrr_peer(ngx_http_request_t *r,
    ngx_http_upstream_srv_conf_t *us)
{
    ngx_http_upstream_vnswrr_srv_conf_t    *uvnscf;
    ngx_http_upstream_vnswrr_peer_data_t   *vnsp;

    uvnscf = ngx_http_conf_upstream_srv_conf(us,
                                          ngx_http_upstream_vnswrr_module);

    vnsp = ngx_palloc(r->pool, sizeof(ngx_http_upstream_vnswrr_peer_data_t));
    if (vnsp == NULL) {
        return NGX_ERROR;
    }

    vnsp->uvnscf = uvnscf;
    r->upstream->peer.data = &vnsp->rrp;

    if (ngx_http_upstream_init_round_robin_peer(r, us) != NGX_OK) {
        return NGX_ERROR;
    }

    r->upstream->peer.get = ngx_http_upstream_get_vnswrr_peer;

    return NGX_OK;
}