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
typedef  scalar_t__ ngx_uint_t ;
typedef  scalar_t__ ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_request_t ;
struct TYPE_9__ {TYPE_1__* co_ctx; struct TYPE_9__* next; } ;
typedef  TYPE_2__ ngx_http_lua_posted_thread_t ;
struct TYPE_10__ {scalar_t__ entered_content_phase; TYPE_1__* cur_co_ctx; TYPE_2__* posted_threads; } ;
typedef  TYPE_3__ ngx_http_lua_ctx_t ;
struct TYPE_11__ {scalar_t__ requests; scalar_t__ destroyed; } ;
typedef  TYPE_4__ ngx_connection_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_8__ {scalar_t__ co_status; int /*<<< orphan*/  co; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_DONE ; 
 scalar_t__ NGX_HTTP_LUA_CO_RUNNING ; 
 int /*<<< orphan*/  ngx_http_lua_finalize_request (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ngx_http_lua_probe_run_posted_thread (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ngx_http_lua_run_thread (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 

ngx_int_t
ngx_http_lua_run_posted_threads(ngx_connection_t *c, lua_State *L,
    ngx_http_request_t *r, ngx_http_lua_ctx_t *ctx, ngx_uint_t nreqs)
{
    ngx_int_t                        rc;
    ngx_http_lua_posted_thread_t    *pt;

    for ( ;; ) {
        if (c->destroyed || c->requests != nreqs) {
            return NGX_DONE;
        }

        pt = ctx->posted_threads;
        if (pt == NULL) {
            return NGX_DONE;
        }

        ctx->posted_threads = pt->next;

        ngx_http_lua_probe_run_posted_thread(r, pt->co_ctx->co,
                                             (int) pt->co_ctx->co_status);

        if (pt->co_ctx->co_status != NGX_HTTP_LUA_CO_RUNNING) {
            continue;
        }

        ctx->cur_co_ctx = pt->co_ctx;

        rc = ngx_http_lua_run_thread(L, r, ctx, 0);

        if (rc == NGX_AGAIN) {
            continue;
        }

        if (rc == NGX_DONE) {
            ngx_http_lua_finalize_request(r, NGX_DONE);
            continue;
        }

        /* rc == NGX_ERROR || rc >= NGX_OK */

        if (ctx->entered_content_phase) {
            ngx_http_lua_finalize_request(r, rc);
        }

        return rc;
    }

    /* impossible to reach here */
}