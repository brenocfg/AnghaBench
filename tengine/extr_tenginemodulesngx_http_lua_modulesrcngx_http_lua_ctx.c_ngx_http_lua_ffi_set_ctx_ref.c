#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_http_request_t ;
struct TYPE_3__ {int ctx_ref; } ;
typedef  TYPE_1__ ngx_http_lua_ctx_t ;

/* Variables and functions */
 int NGX_ERROR ; 
 int NGX_HTTP_LUA_FFI_NO_REQ_CTX ; 
 scalar_t__ NGX_OK ; 
 TYPE_1__* ngx_http_get_module_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 scalar_t__ ngx_http_lua_ngx_ctx_add_cleanup (int /*<<< orphan*/ *,int) ; 

int
ngx_http_lua_ffi_set_ctx_ref(ngx_http_request_t *r, int ref)
{
    ngx_http_lua_ctx_t  *ctx;

    ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);
    if (ctx == NULL) {
        return NGX_HTTP_LUA_FFI_NO_REQ_CTX;
    }

    ctx->ctx_ref = ref;

    if (ngx_http_lua_ngx_ctx_add_cleanup(r, ref) != NGX_OK) {
        return NGX_ERROR;
    }

    return NGX_OK;
}