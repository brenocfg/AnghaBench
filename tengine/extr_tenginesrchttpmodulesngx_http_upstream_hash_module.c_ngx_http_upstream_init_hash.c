#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_5__ {int /*<<< orphan*/  init; } ;
struct TYPE_6__ {TYPE_1__ peer; } ;
typedef  TYPE_2__ ngx_http_upstream_srv_conf_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_http_upstream_init_hash_peer ; 
 scalar_t__ ngx_http_upstream_init_round_robin (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_init_hash(ngx_conf_t *cf, ngx_http_upstream_srv_conf_t *us)
{
    if (ngx_http_upstream_init_round_robin(cf, us) != NGX_OK) {
        return NGX_ERROR;
    }

    us->peer.init = ngx_http_upstream_init_hash_peer;

    return NGX_OK;
}