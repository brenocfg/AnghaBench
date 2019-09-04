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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_5__ {int not_found; int valid; int len; int /*<<< orphan*/ * data; scalar_t__ no_cacheable; } ;
typedef  TYPE_1__ ngx_http_variable_value_t ;
typedef  int /*<<< orphan*/  ngx_http_request_t ;
struct TYPE_6__ {int /*<<< orphan*/  internal_chunked; } ;
typedef  TYPE_2__ ngx_http_proxy_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_2__* ngx_http_get_module_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_proxy_module ; 

__attribute__((used)) static ngx_int_t
ngx_http_proxy_internal_chunked_variable(ngx_http_request_t *r,
    ngx_http_variable_value_t *v, uintptr_t data)
{
    ngx_http_proxy_ctx_t  *ctx;

    ctx = ngx_http_get_module_ctx(r, ngx_http_proxy_module);

    if (ctx == NULL || !ctx->internal_chunked) {
        v->not_found = 1;
        return NGX_OK;
    }

    v->valid = 1;
    v->no_cacheable = 0;
    v->not_found = 0;

    v->data = (u_char *) "chunked";
    v->len = sizeof("chunked") - 1;

    return NGX_OK;
}