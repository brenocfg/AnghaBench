#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  void* u_char ;
struct gztrailer {void** zlen; void** crc32; } ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_13__ {TYPE_1__* connection; int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_11__ {int total_in; int avail_out; scalar_t__ avail_in; scalar_t__ total_out; } ;
struct TYPE_14__ {int zin; int crc32; int done; TYPE_10__ zstream; TYPE_4__** last_out; TYPE_5__* out_buf; int /*<<< orphan*/  preallocated; scalar_t__ zout; } ;
typedef  TYPE_3__ ngx_http_gzip_ctx_t ;
struct TYPE_15__ {struct TYPE_15__* next; TYPE_5__* buf; } ;
typedef  TYPE_4__ ngx_chain_t ;
struct TYPE_16__ {int last; int last_buf; scalar_t__ pos; } ;
typedef  TYPE_5__ ngx_buf_t ;
struct TYPE_12__ {int /*<<< orphan*/  buffered; int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_GZIP_BUFFERED ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_OK ; 
 int Z_OK ; 
 int deflateEnd (TYPE_10__*) ; 
 TYPE_4__* ngx_alloc_chain_link (int /*<<< orphan*/ ) ; 
 TYPE_5__* ngx_create_temp_buf (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ngx_pfree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_gzip_filter_deflate_end(ngx_http_request_t *r,
    ngx_http_gzip_ctx_t *ctx)
{
    int                rc;
    ngx_buf_t         *b;
    ngx_chain_t       *cl;
    struct gztrailer  *trailer;

    ctx->zin = ctx->zstream.total_in;
    ctx->zout = 10 + ctx->zstream.total_out + 8;

    rc = deflateEnd(&ctx->zstream);

    if (rc != Z_OK) {
        ngx_log_error(NGX_LOG_ALERT, r->connection->log, 0,
                      "deflateEnd() failed: %d", rc);
        return NGX_ERROR;
    }

    ngx_pfree(r->pool, ctx->preallocated);

    cl = ngx_alloc_chain_link(r->pool);
    if (cl == NULL) {
        return NGX_ERROR;
    }

    cl->buf = ctx->out_buf;
    cl->next = NULL;
    *ctx->last_out = cl;
    ctx->last_out = &cl->next;

    if (ctx->zstream.avail_out >= 8) {
        trailer = (struct gztrailer *) ctx->out_buf->last;
        ctx->out_buf->last += 8;
        ctx->out_buf->last_buf = 1;

    } else {
        b = ngx_create_temp_buf(r->pool, 8);
        if (b == NULL) {
            return NGX_ERROR;
        }

        b->last_buf = 1;

        cl = ngx_alloc_chain_link(r->pool);
        if (cl == NULL) {
            return NGX_ERROR;
        }

        cl->buf = b;
        cl->next = NULL;
        *ctx->last_out = cl;
        ctx->last_out = &cl->next;
        trailer = (struct gztrailer *) b->pos;
        b->last += 8;
    }

#if (NGX_HAVE_LITTLE_ENDIAN && NGX_HAVE_NONALIGNED)

    trailer->crc32 = ctx->crc32;
    trailer->zlen = ctx->zin;

#else

    trailer->crc32[0] = (u_char) (ctx->crc32 & 0xff);
    trailer->crc32[1] = (u_char) ((ctx->crc32 >> 8) & 0xff);
    trailer->crc32[2] = (u_char) ((ctx->crc32 >> 16) & 0xff);
    trailer->crc32[3] = (u_char) ((ctx->crc32 >> 24) & 0xff);

    trailer->zlen[0] = (u_char) (ctx->zin & 0xff);
    trailer->zlen[1] = (u_char) ((ctx->zin >> 8) & 0xff);
    trailer->zlen[2] = (u_char) ((ctx->zin >> 16) & 0xff);
    trailer->zlen[3] = (u_char) ((ctx->zin >> 24) & 0xff);

#endif

    ctx->zstream.avail_in = 0;
    ctx->zstream.avail_out = 0;

    ctx->done = 1;

    r->connection->buffered &= ~NGX_HTTP_GZIP_BUFFERED;

    return NGX_OK;
}