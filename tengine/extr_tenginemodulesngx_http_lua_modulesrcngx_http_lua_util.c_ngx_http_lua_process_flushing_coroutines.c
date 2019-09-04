#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_8__ {size_t nelts; TYPE_4__* elts; struct TYPE_8__* next; } ;
typedef  TYPE_2__ ngx_list_part_t ;
typedef  scalar_t__ ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_request_t ;
struct TYPE_10__ {scalar_t__ flushing; } ;
struct TYPE_9__ {scalar_t__ flushing_coros; TYPE_4__* cur_co_ctx; TYPE_1__* user_co_ctx; TYPE_4__ entry_co_ctx; } ;
typedef  TYPE_3__ ngx_http_lua_ctx_t ;
typedef  TYPE_4__ ngx_http_lua_co_ctx_t ;
struct TYPE_7__ {TYPE_2__ part; } ;

/* Variables and functions */
 scalar_t__ NGX_DONE ; 
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  dd (char*) ; 
 scalar_t__ ngx_http_lua_flush_resume_helper (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_lua_process_flushing_coroutines(ngx_http_request_t *r,
    ngx_http_lua_ctx_t *ctx)
{
    ngx_int_t                    rc, n;
    ngx_uint_t                   i;
    ngx_list_part_t             *part;
    ngx_http_lua_co_ctx_t       *coctx;

    dd("processing flushing coroutines");

    coctx = &ctx->entry_co_ctx;
    n = ctx->flushing_coros;

    if (coctx->flushing) {
        coctx->flushing = 0;

        ctx->flushing_coros--;
        n--;
        ctx->cur_co_ctx = coctx;

        rc = ngx_http_lua_flush_resume_helper(r, ctx);
        if (rc == NGX_ERROR || rc >= NGX_OK) {
            return rc;
        }

        /* rc == NGX_DONE */
    }

    if (n) {

        if (ctx->user_co_ctx == NULL) {
            return NGX_ERROR;
        }

        part = &ctx->user_co_ctx->part;
        coctx = part->elts;

        for (i = 0; /* void */; i++) {

            if (i >= part->nelts) {
                if (part->next == NULL) {
                    break;
                }

                part = part->next;
                coctx = part->elts;
                i = 0;
            }

            if (coctx[i].flushing) {
                coctx[i].flushing = 0;
                ctx->flushing_coros--;
                n--;
                ctx->cur_co_ctx = &coctx[i];

                rc = ngx_http_lua_flush_resume_helper(r, ctx);
                if (rc == NGX_ERROR || rc >= NGX_OK) {
                    return rc;
                }

                /* rc == NGX_DONE */

                if (n == 0) {
                    return NGX_DONE;
                }
            }
        }
    }

    if (n) {
        return NGX_ERROR;
    }

    return NGX_DONE;
}