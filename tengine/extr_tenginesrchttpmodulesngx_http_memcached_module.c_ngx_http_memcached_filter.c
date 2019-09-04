#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_10__ {int /*<<< orphan*/  tag; } ;
struct TYPE_17__ {int pos; int /*<<< orphan*/ * last; } ;
struct TYPE_14__ {scalar_t__ length; int keepalive; TYPE_1__ output; int /*<<< orphan*/  free_bufs; TYPE_7__* out_bufs; TYPE_8__ buffer; } ;
typedef  TYPE_5__ ngx_http_upstream_t ;
struct TYPE_15__ {scalar_t__ rest; TYPE_3__* request; } ;
typedef  TYPE_6__ ngx_http_memcached_ctx_t ;
struct TYPE_16__ {TYPE_4__* buf; struct TYPE_16__* next; } ;
typedef  TYPE_7__ ngx_chain_t ;
typedef  TYPE_8__ ngx_buf_t ;
struct TYPE_13__ {int flush; int memory; int /*<<< orphan*/ * last; int /*<<< orphan*/  tag; int /*<<< orphan*/ * pos; } ;
struct TYPE_12__ {TYPE_2__* connection; int /*<<< orphan*/  pool; TYPE_5__* upstream; } ;
struct TYPE_11__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 scalar_t__ NGX_HTTP_MEMCACHED_END ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_7__* ngx_chain_get_free_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_http_memcached_end ; 
 int /*<<< orphan*/  ngx_log_debug4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ngx_strncmp (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_memcached_filter(void *data, ssize_t bytes)
{
    ngx_http_memcached_ctx_t  *ctx = data;

    u_char               *last;
    ngx_buf_t            *b;
    ngx_chain_t          *cl, **ll;
    ngx_http_upstream_t  *u;

    u = ctx->request->upstream;
    b = &u->buffer;

    if (u->length == (ssize_t) ctx->rest) {

        if (ngx_strncmp(b->last,
                   ngx_http_memcached_end + NGX_HTTP_MEMCACHED_END - ctx->rest,
                   bytes)
            != 0)
        {
            ngx_log_error(NGX_LOG_ERR, ctx->request->connection->log, 0,
                          "memcached sent invalid trailer");

            u->length = 0;
            ctx->rest = 0;

            return NGX_OK;
        }

        u->length -= bytes;
        ctx->rest -= bytes;

        if (u->length == 0) {
            u->keepalive = 1;
        }

        return NGX_OK;
    }

    for (cl = u->out_bufs, ll = &u->out_bufs; cl; cl = cl->next) {
        ll = &cl->next;
    }

    cl = ngx_chain_get_free_buf(ctx->request->pool, &u->free_bufs);
    if (cl == NULL) {
        return NGX_ERROR;
    }

    cl->buf->flush = 1;
    cl->buf->memory = 1;

    *ll = cl;

    last = b->last;
    cl->buf->pos = last;
    b->last += bytes;
    cl->buf->last = b->last;
    cl->buf->tag = u->output.tag;

    ngx_log_debug4(NGX_LOG_DEBUG_HTTP, ctx->request->connection->log, 0,
                   "memcached filter bytes:%z size:%z length:%O rest:%z",
                   bytes, b->last - b->pos, u->length, ctx->rest);

    if (bytes <= (ssize_t) (u->length - NGX_HTTP_MEMCACHED_END)) {
        u->length -= bytes;
        return NGX_OK;
    }

    last += (size_t) (u->length - NGX_HTTP_MEMCACHED_END);

    if (ngx_strncmp(last, ngx_http_memcached_end, b->last - last) != 0) {
        ngx_log_error(NGX_LOG_ERR, ctx->request->connection->log, 0,
                      "memcached sent invalid trailer");

        b->last = last;
        cl->buf->last = last;
        u->length = 0;
        ctx->rest = 0;

        return NGX_OK;
    }

    ctx->rest -= b->last - last;
    b->last = last;
    cl->buf->last = last;
    u->length = ctx->rest;

    if (u->length == 0) {
        u->keepalive = 1;
    }

    return NGX_OK;
}