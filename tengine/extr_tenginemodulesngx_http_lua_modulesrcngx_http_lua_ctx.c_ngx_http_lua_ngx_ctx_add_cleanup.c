#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* data; int /*<<< orphan*/  handler; } ;
typedef  TYPE_1__ ngx_pool_cleanup_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_9__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_10__ {int ref; int /*<<< orphan*/ * vm; } ;
typedef  TYPE_3__ ngx_http_lua_ngx_ctx_cleanup_data_t ;
typedef  int /*<<< orphan*/  ngx_http_lua_ctx_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/ * ngx_http_get_module_ctx (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_http_lua_get_lua_vm (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 int /*<<< orphan*/  ngx_http_lua_ngx_ctx_cleanup ; 
 TYPE_1__* ngx_pool_cleanup_add (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_lua_ngx_ctx_add_cleanup(ngx_http_request_t *r, int ref)
{
    lua_State                   *L;
    ngx_pool_cleanup_t          *cln;
    ngx_http_lua_ctx_t          *ctx;

    ngx_http_lua_ngx_ctx_cleanup_data_t    *data;

    ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);
    L = ngx_http_lua_get_lua_vm(r, ctx);

    cln = ngx_pool_cleanup_add(r->pool,
                               sizeof(ngx_http_lua_ngx_ctx_cleanup_data_t));
    if (cln == NULL) {
        return NGX_ERROR;
    }

    cln->handler = ngx_http_lua_ngx_ctx_cleanup;

    data = cln->data;
    data->vm = L;
    data->ref = ref;

    return NGX_OK;
}