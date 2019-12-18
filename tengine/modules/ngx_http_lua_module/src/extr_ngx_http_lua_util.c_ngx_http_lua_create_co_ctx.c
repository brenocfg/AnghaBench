#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ ngx_http_request_t ;
struct TYPE_10__ {int /*<<< orphan*/ * user_co_ctx; } ;
typedef  TYPE_2__ ngx_http_lua_ctx_t ;
struct TYPE_11__ {int /*<<< orphan*/  co_ref; } ;
typedef  TYPE_3__ ngx_http_lua_co_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_NOREF ; 
 int /*<<< orphan*/ * ngx_list_create (int /*<<< orphan*/ ,int,int) ; 
 TYPE_3__* ngx_list_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_3__*,int) ; 

ngx_http_lua_co_ctx_t *
ngx_http_lua_create_co_ctx(ngx_http_request_t *r, ngx_http_lua_ctx_t *ctx)
{
    ngx_http_lua_co_ctx_t       *coctx;

    if (ctx->user_co_ctx == NULL) {
        ctx->user_co_ctx = ngx_list_create(r->pool, 4,
                                           sizeof(ngx_http_lua_co_ctx_t));
        if (ctx->user_co_ctx == NULL) {
            return NULL;
        }
    }

    coctx = ngx_list_push(ctx->user_co_ctx);
    if (coctx == NULL) {
        return NULL;
    }

    ngx_memzero(coctx, sizeof(ngx_http_lua_co_ctx_t));

    coctx->co_ref = LUA_NOREF;

    return coctx;
}