#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_11__ {TYPE_1__* connection; int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_14__ {TYPE_3__* opaque; int /*<<< orphan*/  zfree; int /*<<< orphan*/  zalloc; } ;
struct TYPE_12__ {int /*<<< orphan*/  flush; int /*<<< orphan*/  out; int /*<<< orphan*/ * last_out; int /*<<< orphan*/  memlevel; scalar_t__ wbits; TYPE_9__ zstream; int /*<<< orphan*/ * preallocated; int /*<<< orphan*/ * free_mem; int /*<<< orphan*/  allocated; } ;
typedef  TYPE_3__ ngx_http_gzip_ctx_t ;
struct TYPE_13__ {scalar_t__ level; } ;
typedef  TYPE_4__ ngx_http_gzip_conf_t ;
struct TYPE_10__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  Z_DEFAULT_STRATEGY ; 
 int /*<<< orphan*/  Z_DEFLATED ; 
 int /*<<< orphan*/  Z_NO_FLUSH ; 
 int Z_OK ; 
 int deflateInit2 (TYPE_9__*,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* ngx_http_get_module_loc_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_gzip_filter_alloc ; 
 int /*<<< orphan*/  ngx_http_gzip_filter_free ; 
 int /*<<< orphan*/  ngx_http_gzip_filter_module ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * ngx_palloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_gzip_filter_deflate_start(ngx_http_request_t *r,
    ngx_http_gzip_ctx_t *ctx)
{
    int                    rc;
    ngx_http_gzip_conf_t  *conf;

    conf = ngx_http_get_module_loc_conf(r, ngx_http_gzip_filter_module);

    ctx->preallocated = ngx_palloc(r->pool, ctx->allocated);
    if (ctx->preallocated == NULL) {
        return NGX_ERROR;
    }

    ctx->free_mem = ctx->preallocated;

    ctx->zstream.zalloc = ngx_http_gzip_filter_alloc;
    ctx->zstream.zfree = ngx_http_gzip_filter_free;
    ctx->zstream.opaque = ctx;

    rc = deflateInit2(&ctx->zstream, (int) conf->level, Z_DEFLATED,
                      ctx->wbits + 16, ctx->memlevel, Z_DEFAULT_STRATEGY);

    if (rc != Z_OK) {
        ngx_log_error(NGX_LOG_ALERT, r->connection->log, 0,
                      "deflateInit2() failed: %d", rc);
        return NGX_ERROR;
    }

    ctx->last_out = &ctx->out;
    ctx->flush = Z_NO_FLUSH;

    return NGX_OK;
}