#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_8__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_10__ {TYPE_3__* opaque; int /*<<< orphan*/  zfree; int /*<<< orphan*/  zalloc; scalar_t__ avail_in; int /*<<< orphan*/  next_in; } ;
struct TYPE_9__ {int started; int /*<<< orphan*/  flush; int /*<<< orphan*/  out; int /*<<< orphan*/ * last_out; TYPE_6__ zstream; } ;
typedef  TYPE_3__ ngx_http_gunzip_ctx_t ;
struct TYPE_7__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ MAX_WBITS ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  Z_NO_FLUSH ; 
 int /*<<< orphan*/  Z_NULL ; 
 int Z_OK ; 
 int inflateInit2 (TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_http_gunzip_filter_alloc ; 
 int /*<<< orphan*/  ngx_http_gunzip_filter_free ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_gunzip_filter_inflate_start(ngx_http_request_t *r,
    ngx_http_gunzip_ctx_t *ctx)
{
    int  rc;

    ctx->zstream.next_in = Z_NULL;
    ctx->zstream.avail_in = 0;

    ctx->zstream.zalloc = ngx_http_gunzip_filter_alloc;
    ctx->zstream.zfree = ngx_http_gunzip_filter_free;
    ctx->zstream.opaque = ctx;

    /* windowBits +16 to decode gzip, zlib 1.2.0.4+ */
    rc = inflateInit2(&ctx->zstream, MAX_WBITS + 16);

    if (rc != Z_OK) {
        ngx_log_error(NGX_LOG_ALERT, r->connection->log, 0,
                      "inflateInit2() failed: %d", rc);
        return NGX_ERROR;
    }

    ctx->started = 1;

    ctx->last_out = &ctx->out;
    ctx->flush = Z_NO_FLUSH;

    return NGX_OK;
}