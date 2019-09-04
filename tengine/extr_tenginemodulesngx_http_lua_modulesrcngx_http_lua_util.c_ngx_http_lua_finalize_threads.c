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
typedef  size_t ngx_uint_t ;
struct TYPE_9__ {size_t nelts; TYPE_4__* elts; struct TYPE_9__* next; } ;
typedef  TYPE_2__ ngx_list_part_t ;
typedef  int /*<<< orphan*/  ngx_http_request_t ;
struct TYPE_11__ {int co_ref; scalar_t__ co_status; int /*<<< orphan*/  co; } ;
struct TYPE_10__ {scalar_t__ uthreads; TYPE_4__ entry_co_ctx; TYPE_1__* user_co_ctx; TYPE_4__* on_abort_co_ctx; } ;
typedef  TYPE_3__ ngx_http_lua_ctx_t ;
typedef  TYPE_4__ ngx_http_lua_co_ctx_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_8__ {TYPE_2__ part; } ;

/* Variables and functions */
 int LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 void* NGX_HTTP_LUA_CO_DEAD ; 
 scalar_t__ NGX_HTTP_LUA_CO_SUSPENDED ; 
 int /*<<< orphan*/  coroutines_key ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int,int) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_assert (int) ; 
 int /*<<< orphan*/  ngx_http_lua_cleanup_pending_operation (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_http_lua_lightudata_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_probe_thread_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int top ; 

__attribute__((used)) static void
ngx_http_lua_finalize_threads(ngx_http_request_t *r,
    ngx_http_lua_ctx_t *ctx, lua_State *L)
{
#ifdef NGX_LUA_USE_ASSERT
    int                              top;
#endif
    int                              inited = 0, ref;
    ngx_uint_t                       i;
    ngx_list_part_t                 *part;
    ngx_http_lua_co_ctx_t           *cc, *coctx;

#ifdef NGX_LUA_USE_ASSERT
    top = lua_gettop(L);
#endif

#if 1
    coctx = ctx->on_abort_co_ctx;
    if (coctx && coctx->co_ref != LUA_NOREF) {
        if (coctx->co_status != NGX_HTTP_LUA_CO_SUSPENDED) {
            /* the on_abort thread contributes to the coctx->uthreads
             * counter only when it actually starts running */
            ngx_http_lua_cleanup_pending_operation(coctx);
            ctx->uthreads--;
        }

        ngx_http_lua_probe_thread_delete(r, coctx->co, ctx);

        lua_pushlightuserdata(L, ngx_http_lua_lightudata_mask(
                              coroutines_key));
        lua_rawget(L, LUA_REGISTRYINDEX);
        inited = 1;

        luaL_unref(L, -1, coctx->co_ref);
        coctx->co_ref = LUA_NOREF;

        coctx->co_status = NGX_HTTP_LUA_CO_DEAD;
        ctx->on_abort_co_ctx = NULL;
    }
#endif

    if (ctx->user_co_ctx) {
        part = &ctx->user_co_ctx->part;
        cc = part->elts;

        for (i = 0; /* void */; i++) {

            if (i >= part->nelts) {
                if (part->next == NULL) {
                    break;
                }

                part = part->next;
                cc = part->elts;
                i = 0;
            }

            coctx = &cc[i];

            ref = coctx->co_ref;

            if (ref != LUA_NOREF) {
                ngx_http_lua_cleanup_pending_operation(coctx);

                ngx_http_lua_probe_thread_delete(r, coctx->co, ctx);

                if (!inited) {
                    lua_pushlightuserdata(L, ngx_http_lua_lightudata_mask(
                                          coroutines_key));
                    lua_rawget(L, LUA_REGISTRYINDEX);
                    inited = 1;
                }

                ngx_http_lua_assert(lua_gettop(L) - top == 1);

                luaL_unref(L, -1, ref);
                coctx->co_ref = LUA_NOREF;

                coctx->co_status = NGX_HTTP_LUA_CO_DEAD;
                ctx->uthreads--;
            }
        }

        ctx->user_co_ctx = NULL;
    }

    ngx_http_lua_assert(ctx->uthreads == 0);

    coctx = &ctx->entry_co_ctx;

    ref = coctx->co_ref;
    if (ref != LUA_NOREF) {
        ngx_http_lua_cleanup_pending_operation(coctx);

        ngx_http_lua_probe_thread_delete(r, coctx->co, ctx);

        if (!inited) {
            lua_pushlightuserdata(L, ngx_http_lua_lightudata_mask(
                                  coroutines_key));
            lua_rawget(L, LUA_REGISTRYINDEX);
            inited = 1;
        }

        ngx_http_lua_assert(lua_gettop(L) - top == 1);

        luaL_unref(L, -1, coctx->co_ref);
        coctx->co_ref = LUA_NOREF;
        coctx->co_status = NGX_HTTP_LUA_CO_DEAD;
    }

    if (inited) {
        lua_pop(L, 1);
    }
}