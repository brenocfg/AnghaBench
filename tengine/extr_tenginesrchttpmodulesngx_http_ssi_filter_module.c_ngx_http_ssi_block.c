#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_10__ {int block; scalar_t__ output; int /*<<< orphan*/ * blocks; } ;
typedef  TYPE_2__ ngx_http_ssi_ctx_t ;
struct TYPE_11__ {scalar_t__ count; int /*<<< orphan*/ * bufs; int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ ngx_http_ssi_block_t ;
struct TYPE_12__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  main; TYPE_1__* connection; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_9__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 size_t NGX_HTTP_SSI_BLOCK_NAME ; 
 int /*<<< orphan*/  NGX_HTTP_SSI_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/ * ngx_array_create (int /*<<< orphan*/ ,int,int) ; 
 TYPE_3__* ngx_array_push (int /*<<< orphan*/ *) ; 
 TYPE_2__* ngx_http_get_module_ctx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_ssi_filter_module ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_ssi_block(ngx_http_request_t *r, ngx_http_ssi_ctx_t *ctx,
    ngx_str_t **params)
{
    ngx_http_ssi_ctx_t    *mctx;
    ngx_http_ssi_block_t  *bl;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "ssi block");

    mctx = ngx_http_get_module_ctx(r->main, ngx_http_ssi_filter_module);

    if (mctx->blocks == NULL) {
        mctx->blocks = ngx_array_create(r->pool, 4,
                                        sizeof(ngx_http_ssi_block_t));
        if (mctx->blocks == NULL) {
            return NGX_HTTP_SSI_ERROR;
        }
    }

    bl = ngx_array_push(mctx->blocks);
    if (bl == NULL) {
        return NGX_HTTP_SSI_ERROR;
    }

    bl->name = *params[NGX_HTTP_SSI_BLOCK_NAME];
    bl->bufs = NULL;
    bl->count = 0;

    ctx->output = 0;
    ctx->block = 1;

    return NGX_OK;
}