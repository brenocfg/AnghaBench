#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_49__   TYPE_9__ ;
typedef  struct TYPE_48__   TYPE_8__ ;
typedef  struct TYPE_47__   TYPE_7__ ;
typedef  struct TYPE_46__   TYPE_6__ ;
typedef  struct TYPE_45__   TYPE_5__ ;
typedef  struct TYPE_44__   TYPE_4__ ;
typedef  struct TYPE_43__   TYPE_3__ ;
typedef  struct TYPE_42__   TYPE_34__ ;
typedef  struct TYPE_41__   TYPE_2__ ;
typedef  struct TYPE_40__   TYPE_1__ ;
typedef  struct TYPE_39__   TYPE_18__ ;
typedef  struct TYPE_38__   TYPE_15__ ;
typedef  struct TYPE_37__   TYPE_14__ ;

/* Type definitions */
typedef  int ngx_uint_t ;
struct TYPE_43__ {int len; TYPE_9__* data; } ;
typedef  TYPE_3__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_44__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_4__ ngx_http_sub_match_t ;
struct TYPE_45__ {scalar_t__ once; } ;
typedef  TYPE_5__ ngx_http_sub_loc_conf_t ;
struct TYPE_38__ {int len; TYPE_9__* data; } ;
struct TYPE_39__ {int len; TYPE_14__* data; } ;
struct TYPE_46__ {int once; scalar_t__ pos; size_t index; int applied; int /*<<< orphan*/ * busy; int /*<<< orphan*/ * out; TYPE_14__* buf; TYPE_8__** last_out; int /*<<< orphan*/  free; TYPE_15__ looked; TYPE_2__* matches; TYPE_3__* sub; TYPE_9__* copy_end; TYPE_9__* copy_start; TYPE_18__ saved; TYPE_34__* in; } ;
typedef  TYPE_6__ ngx_http_sub_ctx_t ;
struct TYPE_47__ {int /*<<< orphan*/  pool; TYPE_1__* connection; TYPE_18__ uri; } ;
typedef  TYPE_7__ ngx_http_request_t ;
struct TYPE_48__ {struct TYPE_48__* next; TYPE_9__* buf; } ;
typedef  TYPE_8__ ngx_chain_t ;
struct TYPE_49__ {int memory; int file_last; int file_pos; int sync; scalar_t__ recycled; TYPE_14__* shadow; scalar_t__ flush; scalar_t__ last_in_chain; scalar_t__ last_buf; struct TYPE_49__* pos; struct TYPE_49__* last; scalar_t__ in_file; } ;
typedef  TYPE_9__ ngx_buf_t ;
struct TYPE_42__ {struct TYPE_42__* next; TYPE_14__* buf; } ;
struct TYPE_41__ {int nelts; TYPE_4__* elts; } ;
struct TYPE_40__ {int /*<<< orphan*/  log; } ;
struct TYPE_37__ {scalar_t__ pos; scalar_t__ last; scalar_t__ recycled; scalar_t__ flush; scalar_t__ last_in_chain; scalar_t__ last_buf; scalar_t__ sync; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_buf_in_memory (TYPE_14__*) ; 
 scalar_t__ ngx_chain_add_copy (int /*<<< orphan*/ ,TYPE_34__**,TYPE_8__*) ; 
 TYPE_8__* ngx_chain_get_free_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_http_complex_value (TYPE_7__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_6__* ngx_http_get_module_ctx (TYPE_7__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* ngx_http_get_module_loc_conf (TYPE_7__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_next_body_filter (TYPE_7__*,TYPE_8__*) ; 
 int /*<<< orphan*/  ngx_http_sub_filter_module ; 
 scalar_t__ ngx_http_sub_output (TYPE_7__*,TYPE_6__*) ; 
 scalar_t__ ngx_http_sub_parse (TYPE_7__*,TYPE_6__*,int) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_18__*) ; 
 int /*<<< orphan*/  ngx_log_debug4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,TYPE_15__*,TYPE_9__*,TYPE_9__*) ; 
 int /*<<< orphan*/  ngx_memcpy (TYPE_9__*,TYPE_14__*,int) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_9__*,int) ; 
 TYPE_3__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 TYPE_9__* ngx_pnalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_sub_body_filter(ngx_http_request_t *r, ngx_chain_t *in)
{
    ngx_int_t                  rc;
    ngx_buf_t                 *b;
    ngx_str_t                 *sub;
    ngx_uint_t                 flush, last;
    ngx_chain_t               *cl;
    ngx_http_sub_ctx_t        *ctx;
    ngx_http_sub_match_t      *match;
    ngx_http_sub_loc_conf_t   *slcf;

    ctx = ngx_http_get_module_ctx(r, ngx_http_sub_filter_module);

    if (ctx == NULL) {
        return ngx_http_next_body_filter(r, in);
    }

    if ((in == NULL
         && ctx->buf == NULL
         && ctx->in == NULL
         && ctx->busy == NULL))
    {
        return ngx_http_next_body_filter(r, in);
    }

    if (ctx->once && (ctx->buf == NULL || ctx->in == NULL)) {

        if (ctx->busy) {
            if (ngx_http_sub_output(r, ctx) == NGX_ERROR) {
                return NGX_ERROR;
            }
        }

        return ngx_http_next_body_filter(r, in);
    }

    /* add the incoming chain to the chain ctx->in */

    if (in) {
        if (ngx_chain_add_copy(r->pool, &ctx->in, in) != NGX_OK) {
            return NGX_ERROR;
        }
    }

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "http sub filter \"%V\"", &r->uri);

    flush = 0;
    last = 0;

    while (ctx->in || ctx->buf) {

        if (ctx->buf == NULL) {
            ctx->buf = ctx->in->buf;
            ctx->in = ctx->in->next;
            ctx->pos = ctx->buf->pos;
        }

        if (ctx->buf->flush || ctx->buf->recycled) {
            flush = 1;
        }

        if (ctx->in == NULL) {
            last = flush;
        }

        b = NULL;

        while (ctx->pos < ctx->buf->last) {

            rc = ngx_http_sub_parse(r, ctx, last);

            ngx_log_debug4(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                           "parse: %i, looked: \"%V\" %p-%p",
                           rc, &ctx->looked, ctx->copy_start, ctx->copy_end);

            if (rc == NGX_ERROR) {
                return rc;
            }

            if (ctx->saved.len) {

                ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                               "saved: \"%V\"", &ctx->saved);

                cl = ngx_chain_get_free_buf(r->pool, &ctx->free);
                if (cl == NULL) {
                    return NGX_ERROR;
                }

                b = cl->buf;

                ngx_memzero(b, sizeof(ngx_buf_t));

                b->pos = ngx_pnalloc(r->pool, ctx->saved.len);
                if (b->pos == NULL) {
                    return NGX_ERROR;
                }

                ngx_memcpy(b->pos, ctx->saved.data, ctx->saved.len);
                b->last = b->pos + ctx->saved.len;
                b->memory = 1;

                *ctx->last_out = cl;
                ctx->last_out = &cl->next;

                ctx->saved.len = 0;
            }

            if (ctx->copy_start != ctx->copy_end) {

                cl = ngx_chain_get_free_buf(r->pool, &ctx->free);
                if (cl == NULL) {
                    return NGX_ERROR;
                }

                b = cl->buf;

                ngx_memcpy(b, ctx->buf, sizeof(ngx_buf_t));

                b->pos = ctx->copy_start;
                b->last = ctx->copy_end;
                b->shadow = NULL;
                b->last_buf = 0;
                b->last_in_chain = 0;
                b->recycled = 0;

                if (b->in_file) {
                    b->file_last = b->file_pos + (b->last - ctx->buf->pos);
                    b->file_pos += b->pos - ctx->buf->pos;
                }

                *ctx->last_out = cl;
                ctx->last_out = &cl->next;
            }

            if (rc == NGX_AGAIN) {
                continue;
            }


            /* rc == NGX_OK */

            cl = ngx_chain_get_free_buf(r->pool, &ctx->free);
            if (cl == NULL) {
                return NGX_ERROR;
            }

            b = cl->buf;

            ngx_memzero(b, sizeof(ngx_buf_t));

            slcf = ngx_http_get_module_loc_conf(r, ngx_http_sub_filter_module);

            if (ctx->sub == NULL) {
                ctx->sub = ngx_pcalloc(r->pool, sizeof(ngx_str_t)
                                                * ctx->matches->nelts);
                if (ctx->sub == NULL) {
                    return NGX_ERROR;
                }
            }

            sub = &ctx->sub[ctx->index];

            if (sub->data == NULL) {
                match = ctx->matches->elts;

                if (ngx_http_complex_value(r, match[ctx->index].value, sub)
                    != NGX_OK)
                {
                    return NGX_ERROR;
                }
            }

            if (sub->len) {
                b->memory = 1;
                b->pos = sub->data;
                b->last = sub->data + sub->len;

            } else {
                b->sync = 1;
            }

            *ctx->last_out = cl;
            ctx->last_out = &cl->next;

            ctx->index = 0;
            ctx->once = slcf->once && (++ctx->applied == ctx->matches->nelts);

            continue;
        }

        if (ctx->looked.len
            && (ctx->buf->last_buf || ctx->buf->last_in_chain))
        {
            cl = ngx_chain_get_free_buf(r->pool, &ctx->free);
            if (cl == NULL) {
                return NGX_ERROR;
            }

            b = cl->buf;

            ngx_memzero(b, sizeof(ngx_buf_t));

            b->pos = ctx->looked.data;
            b->last = b->pos + ctx->looked.len;
            b->memory = 1;

            *ctx->last_out = cl;
            ctx->last_out = &cl->next;

            ctx->looked.len = 0;
        }

        if (ctx->buf->last_buf || ctx->buf->flush || ctx->buf->sync
            || ngx_buf_in_memory(ctx->buf))
        {
            if (b == NULL) {
                cl = ngx_chain_get_free_buf(r->pool, &ctx->free);
                if (cl == NULL) {
                    return NGX_ERROR;
                }

                b = cl->buf;

                ngx_memzero(b, sizeof(ngx_buf_t));

                b->sync = 1;

                *ctx->last_out = cl;
                ctx->last_out = &cl->next;
            }

            b->last_buf = ctx->buf->last_buf;
            b->last_in_chain = ctx->buf->last_in_chain;
            b->flush = ctx->buf->flush;
            b->shadow = ctx->buf;

            b->recycled = ctx->buf->recycled;
        }

        ctx->buf = NULL;
    }

    if (ctx->out == NULL && ctx->busy == NULL) {
        return NGX_OK;
    }

    return ngx_http_sub_output(r, ctx);
}