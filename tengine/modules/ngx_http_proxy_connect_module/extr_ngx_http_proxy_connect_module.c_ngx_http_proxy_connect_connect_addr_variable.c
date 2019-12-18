#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_10__ {int not_found; int valid; int /*<<< orphan*/  data; scalar_t__ no_cacheable; int /*<<< orphan*/  len; } ;
typedef  TYPE_3__ ngx_http_variable_value_t ;
typedef  int /*<<< orphan*/  ngx_http_request_t ;
struct TYPE_9__ {TYPE_1__* name; } ;
struct TYPE_11__ {TYPE_2__ peer; } ;
typedef  TYPE_4__ ngx_http_proxy_connect_upstream_t ;
struct TYPE_12__ {TYPE_4__* u; } ;
typedef  TYPE_5__ ngx_http_proxy_connect_ctx_t ;
struct TYPE_8__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_5__* ngx_http_get_module_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_proxy_connect_module ; 

__attribute__((used)) static ngx_int_t
ngx_http_proxy_connect_connect_addr_variable(ngx_http_request_t *r,
    ngx_http_variable_value_t *v, uintptr_t data)
{

    ngx_http_proxy_connect_upstream_t     *u;
    ngx_http_proxy_connect_ctx_t          *ctx;

    ctx = ngx_http_get_module_ctx(r, ngx_http_proxy_connect_module);

    if (ctx == NULL) {
        v->not_found = 1;
        return NGX_OK;
    }

    u = ctx->u;

    if (u == NULL || u->peer.name == NULL) {
        v->not_found = 1;
        return NGX_OK;
    }

    v->len = u->peer.name->len;
    v->valid = 1;
    v->no_cacheable = 0;
    v->not_found = 0;
    v->data = u->peer.name->data;

    return NGX_OK;
}