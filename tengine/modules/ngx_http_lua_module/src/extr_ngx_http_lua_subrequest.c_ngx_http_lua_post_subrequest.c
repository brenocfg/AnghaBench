#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_12__ ;
typedef  struct TYPE_24__   TYPE_11__ ;
typedef  struct TYPE_23__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_32__ {size_t len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_7__ ngx_str_t ;
typedef  int ngx_int_t ;
struct TYPE_26__ {scalar_t__ len; } ;
struct TYPE_30__ {int status; scalar_t__ content_length_n; TYPE_1__ content_type; } ;
struct TYPE_28__ {int /*<<< orphan*/  data; scalar_t__ len; } ;
struct TYPE_33__ {int err_status; int expect_tested; TYPE_5__ headers_out; TYPE_4__* connection; int /*<<< orphan*/  pool; TYPE_3__ uri; int /*<<< orphan*/  write_event_handler; struct TYPE_33__* parent; TYPE_2__* main; } ;
typedef  TYPE_8__ ngx_http_request_t ;
struct TYPE_34__ {TYPE_11__* pr_co_ctx; TYPE_10__* ctx; } ;
typedef  TYPE_9__ ngx_http_lua_post_subrequest_data_t ;
struct TYPE_23__ {int run_post_subrequest; size_t index; int free_bufs; TYPE_12__* body; int /*<<< orphan*/  busy_bufs; scalar_t__ headers_set; int /*<<< orphan*/  seen_last_for_subreq; scalar_t__ entered_content_phase; TYPE_11__* cur_co_ctx; int /*<<< orphan*/  resume_handler; scalar_t__ no_abort; } ;
typedef  TYPE_10__ ngx_http_lua_ctx_t ;
struct TYPE_24__ {scalar_t__ pending_subreqs; int* sr_statuses; TYPE_7__* sr_bodies; TYPE_5__** sr_headers; int /*<<< orphan*/ * sr_flags; } ;
typedef  TYPE_11__ ngx_http_lua_co_ctx_t ;
struct TYPE_25__ {TYPE_6__* buf; struct TYPE_25__* next; } ;
typedef  TYPE_12__ ngx_chain_t ;
typedef  int /*<<< orphan*/  ngx_buf_tag_t ;
struct TYPE_31__ {int /*<<< orphan*/  start; scalar_t__ pos; scalar_t__ last; } ;
struct TYPE_29__ {TYPE_8__* data; int /*<<< orphan*/  log; } ;
struct TYPE_27__ {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int NGX_ERROR ; 
 int NGX_HTTP_CLIENT_CLOSED_REQUEST ; 
 int NGX_HTTP_CLOSE ; 
 int NGX_HTTP_CREATED ; 
 int NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_LUA_SUBREQ_TRUNCATED ; 
 int NGX_HTTP_NO_CONTENT ; 
 int NGX_HTTP_OK ; 
 int NGX_HTTP_REQUEST_TIME_OUT ; 
 int NGX_HTTP_SPECIAL_RESPONSE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int NGX_OK ; 
 int /*<<< orphan*/  dd (char*,...) ; 
 int /*<<< orphan*/  ngx_chain_update_chains (int*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/ * ngx_copy (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ngx_http_clear_accept_ranges (TYPE_8__*) ; 
 int /*<<< orphan*/  ngx_http_clear_last_modified (TYPE_8__*) ; 
 int /*<<< orphan*/  ngx_http_core_run_phases ; 
 TYPE_10__* ngx_http_get_module_ctx (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_content_wev_handler ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 int ngx_http_lua_send_header_if_needed (TYPE_8__*,TYPE_10__*) ; 
 int ngx_http_lua_set_content_type (TYPE_8__*,TYPE_10__*) ; 
 int /*<<< orphan*/  ngx_http_lua_subrequest_resume ; 
 int /*<<< orphan*/  ngx_http_post_request_to_head (TYPE_8__*) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * ngx_palloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ngx_pfree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ngx_int_t
ngx_http_lua_post_subrequest(ngx_http_request_t *r, void *data, ngx_int_t rc)
{
    ngx_http_request_t            *pr;
    ngx_http_lua_ctx_t            *pr_ctx;
    ngx_http_lua_ctx_t            *ctx; /* subrequest ctx */
    ngx_http_lua_co_ctx_t         *pr_coctx;
    size_t                         len;
    ngx_str_t                     *body_str;
    u_char                        *p;
    ngx_chain_t                   *cl;

    ngx_http_lua_post_subrequest_data_t    *psr_data = data;

    ctx = psr_data->ctx;

    if (ctx->run_post_subrequest) {
        if (r != r->connection->data) {
            r->connection->data = r;
        }

        return NGX_OK;
    }

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "lua run post subrequest handler, rc:%i c:%ud", rc,
                   r->main->count);

    ctx->run_post_subrequest = 1;

    pr = r->parent;

    pr_ctx = ngx_http_get_module_ctx(pr, ngx_http_lua_module);
    if (pr_ctx == NULL) {
        return NGX_ERROR;
    }

    pr_coctx = psr_data->pr_co_ctx;
    pr_coctx->pending_subreqs--;

    if (pr_coctx->pending_subreqs == 0) {
        dd("all subrequests are done");

        pr_ctx->no_abort = 0;
        pr_ctx->resume_handler = ngx_http_lua_subrequest_resume;
        pr_ctx->cur_co_ctx = pr_coctx;
    }

    if (pr_ctx->entered_content_phase) {
        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "lua restoring write event handler");

        pr->write_event_handler = ngx_http_lua_content_wev_handler;

    } else {
        pr->write_event_handler = ngx_http_core_run_phases;
    }

    dd("status rc = %d", (int) rc);
    dd("status headers_out.status = %d", (int) r->headers_out.status);
    dd("uri: %.*s", (int) r->uri.len, r->uri.data);

    /*  capture subrequest response status */

    pr_coctx->sr_statuses[ctx->index] = r->headers_out.status;

    if (pr_coctx->sr_statuses[ctx->index] == 0) {
        if (rc == NGX_OK) {
            rc = NGX_HTTP_OK;
        }

        if (rc == NGX_ERROR) {
            rc = NGX_HTTP_INTERNAL_SERVER_ERROR;
        }

        if (rc >= 100) {
            pr_coctx->sr_statuses[ctx->index] = rc;
        }
    }

    if (!ctx->seen_last_for_subreq) {
        pr_coctx->sr_flags[ctx->index] |= NGX_HTTP_LUA_SUBREQ_TRUNCATED;
    }

    dd("pr_coctx status: %d", (int) pr_coctx->sr_statuses[ctx->index]);

    /* copy subrequest response headers */
    if (ctx->headers_set) {
        rc = ngx_http_lua_set_content_type(r, ctx);
        if (rc != NGX_OK) {
            ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                          "failed to set default content type: %i", rc);
            return NGX_ERROR;
        }
    }

    pr_coctx->sr_headers[ctx->index] = &r->headers_out;

    /* copy subrequest response body */

    body_str = &pr_coctx->sr_bodies[ctx->index];

    len = 0;
    for (cl = ctx->body; cl; cl = cl->next) {
        /*  ignore all non-memory buffers */
        len += cl->buf->last - cl->buf->pos;
    }

    body_str->len = len;

    if (len == 0) {
        body_str->data = NULL;

    } else {
        p = ngx_palloc(r->pool, len);
        if (p == NULL) {
            return NGX_ERROR;
        }

        body_str->data = p;

        /* copy from and then free the data buffers */

        for (cl = ctx->body; cl; cl = cl->next) {
            p = ngx_copy(p, cl->buf->pos, cl->buf->last - cl->buf->pos);

            cl->buf->last = cl->buf->pos;

#if 0
            dd("free body chain link buf ASAP");
            ngx_pfree(r->pool, cl->buf->start);
#endif
        }
    }

    if (ctx->body) {

#if defined(nginx_version) && nginx_version >= 1001004
        ngx_chain_update_chains(r->pool,
#else
        ngx_chain_update_chains(
#endif
                                &pr_ctx->free_bufs, &pr_ctx->busy_bufs,
                                &ctx->body,
                                (ngx_buf_tag_t) &ngx_http_lua_module);

        dd("free bufs: %p", pr_ctx->free_bufs);
    }

    ngx_http_post_request_to_head(pr);

    if (r != r->connection->data) {
        r->connection->data = r;
    }

    if (rc == NGX_ERROR
        || rc == NGX_HTTP_CREATED
        || rc == NGX_HTTP_NO_CONTENT
        || (rc >= NGX_HTTP_SPECIAL_RESPONSE
            && rc != NGX_HTTP_CLOSE
            && rc != NGX_HTTP_REQUEST_TIME_OUT
            && rc != NGX_HTTP_CLIENT_CLOSED_REQUEST))
    {
        /* emulate ngx_http_special_response_handler */

        if (rc > NGX_OK) {
            r->err_status = rc;

            r->expect_tested = 1;
            r->headers_out.content_type.len = 0;
            r->headers_out.content_length_n = 0;

            ngx_http_clear_accept_ranges(r);
            ngx_http_clear_last_modified(r);

            rc = ngx_http_lua_send_header_if_needed(r, ctx);
            if (rc == NGX_ERROR) {
                return NGX_ERROR;
            }
        }

        return NGX_OK;
    }

    return rc;
}