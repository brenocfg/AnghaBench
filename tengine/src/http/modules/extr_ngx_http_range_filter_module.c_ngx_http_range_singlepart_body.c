#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_20__ {int /*<<< orphan*/  pool; struct TYPE_20__* main; TYPE_2__* connection; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_21__ {scalar_t__ end; scalar_t__ start; } ;
typedef  TYPE_4__ ngx_http_range_t ;
struct TYPE_18__ {TYPE_4__* elts; } ;
struct TYPE_22__ {scalar_t__ offset; TYPE_1__ ranges; } ;
typedef  TYPE_5__ ngx_http_range_filter_ctx_t ;
struct TYPE_23__ {struct TYPE_23__* next; TYPE_7__* buf; } ;
typedef  TYPE_6__ ngx_chain_t ;
struct TYPE_24__ {size_t pos; size_t last; int sync; int last_buf; int last_in_chain; int /*<<< orphan*/  file_last; scalar_t__ in_file; int /*<<< orphan*/  file_pos; } ;
typedef  TYPE_7__ ngx_buf_t ;
struct TYPE_19__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 TYPE_6__* ngx_alloc_chain_link (int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_buf_in_memory (TYPE_7__*) ; 
 scalar_t__ ngx_buf_size (TYPE_7__*) ; 
 scalar_t__ ngx_buf_special (TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_free_chain (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_http_next_body_filter (TYPE_3__*,TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static ngx_int_t
ngx_http_range_singlepart_body(ngx_http_request_t *r,
    ngx_http_range_filter_ctx_t *ctx, ngx_chain_t *in)
{
    off_t              start, last;
    ngx_int_t          rc;
    ngx_buf_t         *buf;
    ngx_chain_t       *out, *cl, *tl, **ll;
    ngx_http_range_t  *range;

    out = NULL;
    ll = &out;
    range = ctx->ranges.elts;

    for (cl = in; cl; cl = cl->next) {

        buf = cl->buf;

        start = ctx->offset;
        last = ctx->offset + ngx_buf_size(buf);

        ctx->offset = last;

        ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "http range body buf: %O-%O", start, last);

        if (ngx_buf_special(buf)) {

            if (range->end <= start) {
                continue;
            }

            tl = ngx_alloc_chain_link(r->pool);
            if (tl == NULL) {
                return NGX_ERROR;
            }

            tl->buf = buf;
            tl->next = NULL;

            *ll = tl;
            ll = &tl->next;

            continue;
        }

        if (range->end <= start || range->start >= last) {

            ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                           "http range body skip");

            if (buf->in_file) {
                buf->file_pos = buf->file_last;
            }

            buf->pos = buf->last;
            buf->sync = 1;

            continue;
        }

        if (range->start > start) {

            if (buf->in_file) {
                buf->file_pos += range->start - start;
            }

            if (ngx_buf_in_memory(buf)) {
                buf->pos += (size_t) (range->start - start);
            }
        }

        if (range->end <= last) {

            if (buf->in_file) {
                buf->file_last -= last - range->end;
            }

            if (ngx_buf_in_memory(buf)) {
                buf->last -= (size_t) (last - range->end);
            }

            buf->last_buf = (r == r->main) ? 1 : 0;
            buf->last_in_chain = 1;

            tl = ngx_alloc_chain_link(r->pool);
            if (tl == NULL) {
                return NGX_ERROR;
            }

            tl->buf = buf;
            tl->next = NULL;

            *ll = tl;
            ll = &tl->next;

            continue;
        }

        tl = ngx_alloc_chain_link(r->pool);
        if (tl == NULL) {
            return NGX_ERROR;
        }

        tl->buf = buf;
        tl->next = NULL;

        *ll = tl;
        ll = &tl->next;
    }

    rc = ngx_http_next_body_filter(r, out);

    while (out) {
        cl = out;
        out = out->next;
        ngx_free_chain(r->pool, cl);
    }

    return rc;
}