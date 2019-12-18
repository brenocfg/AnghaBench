#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_http_request_t ;
struct TYPE_8__ {TYPE_5__* co_ctx; struct TYPE_8__* next; } ;
typedef  TYPE_1__ ngx_http_lua_posted_thread_t ;
struct TYPE_9__ {int /*<<< orphan*/  uthreads; } ;
typedef  TYPE_2__ ngx_http_lua_ctx_t ;
struct TYPE_10__ {TYPE_1__* zombie_child_threads; } ;
typedef  TYPE_3__ ngx_http_lua_co_ctx_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_11__ {scalar_t__ co_ref; } ;

/* Variables and functions */
 scalar_t__ LUA_NOREF ; 
 int /*<<< orphan*/  ngx_http_lua_del_thread (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,TYPE_5__*) ; 

__attribute__((used)) static void
ngx_http_lua_cleanup_zombie_child_uthreads(ngx_http_request_t *r,
    lua_State *L, ngx_http_lua_ctx_t *ctx, ngx_http_lua_co_ctx_t *coctx)
{
    ngx_http_lua_posted_thread_t   *pt;

    for (pt = coctx->zombie_child_threads; pt; pt = pt->next) {
        if (pt->co_ctx->co_ref != LUA_NOREF) {
            ngx_http_lua_del_thread(r, L, ctx, pt->co_ctx);
            ctx->uthreads--;
        }
    }

    coctx->zombie_child_threads = NULL;
}