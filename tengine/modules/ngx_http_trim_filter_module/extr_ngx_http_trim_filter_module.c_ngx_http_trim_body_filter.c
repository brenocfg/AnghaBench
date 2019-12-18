#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ off_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_25__ {scalar_t__ saved; int /*<<< orphan*/  busy; int /*<<< orphan*/  free; int /*<<< orphan*/  tout; int /*<<< orphan*/  tin; TYPE_4__* in; } ;
typedef  TYPE_2__ ngx_http_trim_ctx_t ;
struct TYPE_26__ {int /*<<< orphan*/  pool; TYPE_1__* connection; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_27__ {struct TYPE_27__* next; TYPE_5__* buf; } ;
typedef  TYPE_4__ ngx_chain_t ;
typedef  void* ngx_buf_tag_t ;
typedef  int /*<<< orphan*/  ngx_buf_t ;
struct TYPE_32__ {int len; int /*<<< orphan*/ * data; } ;
struct TYPE_31__ {int /*<<< orphan*/ * data; } ;
struct TYPE_30__ {int len; int /*<<< orphan*/ * data; } ;
struct TYPE_29__ {int len; int /*<<< orphan*/ * data; } ;
struct TYPE_28__ {int memory; scalar_t__ file_last; scalar_t__ file_pos; int last_buf; void* tag; scalar_t__ in_file; int /*<<< orphan*/ * pos; int /*<<< orphan*/ * last; } ;
struct TYPE_24__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_HTTP_TRIM_SAVE_HACKCSS ; 
 scalar_t__ NGX_HTTP_TRIM_SAVE_JAVASCRIPT ; 
 scalar_t__ NGX_HTTP_TRIM_SAVE_JSCSS ; 
 scalar_t__ NGX_HTTP_TRIM_SAVE_SLASH ; 
 scalar_t__ NGX_HTTP_TRIM_SAVE_SPACE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_buf_size (TYPE_5__*) ; 
 scalar_t__ ngx_chain_add_copy (int /*<<< orphan*/ ,TYPE_4__**,TYPE_4__*) ; 
 TYPE_4__* ngx_chain_get_free_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_chain_update_chains (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__**,void*) ; 
 TYPE_2__* ngx_http_get_module_ctx (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_next_body_filter (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_http_trim_filter_module ; 
 scalar_t__ ngx_http_trim_parse (TYPE_3__*,TYPE_4__*,TYPE_2__*) ; 
 TYPE_9__ ngx_http_trim_saved_css_hack ; 
 TYPE_8__ ngx_http_trim_saved_html ; 
 TYPE_7__ ngx_http_trim_saved_jscss ; 
 TYPE_6__ ngx_http_trim_script ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_5__*,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_trim_body_filter(ngx_http_request_t *r, ngx_chain_t *in)
{
    ngx_int_t             rc;
    ngx_chain_t          *cl, *ln, *out, **ll;
    ngx_http_trim_ctx_t  *ctx;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "http trim filter");

    ctx = ngx_http_get_module_ctx(r, ngx_http_trim_filter_module);
    if (ctx == NULL) {
        return ngx_http_next_body_filter(r, in);
    }

    if (in == NULL) {
        return ngx_http_next_body_filter(r, in);
    }

    ctx->in = NULL;
    if (ngx_chain_add_copy(r->pool, &ctx->in, in) != NGX_OK) {
        return NGX_ERROR;
    }

    out = NULL;
    ll = &out;

    for (ln = ctx->in; ln; ln = ln->next) {
        ctx->tin += ln->buf->last - ln->buf->pos;

        rc = ngx_http_trim_parse(r, ln, ctx);
        if (rc == NGX_ERROR) {
            return rc;
        }

        if (ctx->saved) {
            cl = ngx_chain_get_free_buf(r->pool, &ctx->free);
            if (cl == NULL) {
                return NGX_ERROR;
            }

            cl->buf->tag = (ngx_buf_tag_t) &ngx_http_trim_filter_module;
            cl->buf->memory = 1;

            if (ctx->saved > 0) {
                cl->buf->pos = ngx_http_trim_saved_html.data;
                cl->buf->last = cl->buf->pos + ctx->saved;

            } else if (ctx->saved == NGX_HTTP_TRIM_SAVE_SLASH) {
                cl->buf->pos = ngx_http_trim_saved_jscss.data;
                cl->buf->last = cl->buf->pos + 1;

            } else if (ctx->saved == NGX_HTTP_TRIM_SAVE_SPACE) {
                cl->buf->pos = (u_char *) " ";
                cl->buf->last = cl->buf->pos + 1;

            } else if (ctx->saved == NGX_HTTP_TRIM_SAVE_JSCSS) {
                cl->buf->pos = ngx_http_trim_saved_jscss.data;
                cl->buf->last = cl->buf->pos + ngx_http_trim_saved_jscss.len;

            } else if (ctx->saved == NGX_HTTP_TRIM_SAVE_HACKCSS) {
                cl->buf->pos = ngx_http_trim_saved_css_hack.data;
                cl->buf->last = cl->buf->pos + ngx_http_trim_saved_css_hack.len;

            } else if (ctx->saved == NGX_HTTP_TRIM_SAVE_JAVASCRIPT) {
                cl->buf->pos = ngx_http_trim_script.data;
                cl->buf->last = cl->buf->pos + ngx_http_trim_script.len - 1;
            }

            *ll = cl;
            ll = &cl->next;

            ctx->tout += cl->buf->last - cl->buf->pos;

            ctx->saved = 0;
        }

        if(ln->buf->in_file
           && (ln->buf->file_last - ln->buf->file_pos)
               != (off_t) (ln->buf->last - ln->buf->pos))
        {
            ln->buf->in_file = 0;
        }

        if (ngx_buf_size(ln->buf) == 0) {
            if (ln->buf->last_buf) {
                cl = ngx_chain_get_free_buf(r->pool, &ctx->free);
                if (cl == NULL) {
                    return NGX_ERROR;
                }

                ngx_memzero(cl->buf, sizeof(ngx_buf_t));
                cl->buf->tag = (ngx_buf_tag_t) &ngx_http_trim_filter_module;
                cl->buf->last_buf = 1;

                *ll = cl;
                ll = &cl->next;

            }  else {
                if (ln->next == NULL) {
                    *ll = NULL;
                }
            }

        } else {
            *ll = ln;
            ll = &ln->next;
        }

    }

    if (out == NULL) {
        return NGX_OK;
    }

    rc = ngx_http_next_body_filter(r, out);

    ngx_chain_update_chains(r->pool, &ctx->free, &ctx->busy, &out,
                           (ngx_buf_tag_t) &ngx_http_trim_filter_module);

    return rc;
}