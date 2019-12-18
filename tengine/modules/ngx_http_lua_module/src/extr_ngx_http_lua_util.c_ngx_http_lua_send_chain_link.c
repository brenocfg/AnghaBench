#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_20__ {scalar_t__ content_length_n; } ;
struct TYPE_22__ {int method; int header_only; scalar_t__ http_version; TYPE_2__* connection; struct TYPE_22__* main; int /*<<< orphan*/  request_body; TYPE_1__ headers_out; int /*<<< orphan*/  header_sent; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_23__ {scalar_t__ http10_buffering; } ;
typedef  TYPE_4__ ngx_http_lua_loc_conf_t ;
struct TYPE_24__ {int eof; int buffering; TYPE_6__* out; int /*<<< orphan*/  header_sent; scalar_t__ acquired_raw_req_socket; } ;
typedef  TYPE_5__ ngx_http_lua_ctx_t ;
struct TYPE_25__ {struct TYPE_25__* next; } ;
typedef  TYPE_6__ ngx_chain_t ;
struct TYPE_21__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int NGX_HTTP_HEAD ; 
 int /*<<< orphan*/  NGX_HTTP_LAST ; 
 scalar_t__ NGX_HTTP_SPECIAL_RESPONSE ; 
 scalar_t__ NGX_HTTP_VERSION_11 ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  dd (char*) ; 
 scalar_t__ ngx_http_discard_request_body (TYPE_3__*) ; 
 TYPE_4__* ngx_http_get_module_loc_conf (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 scalar_t__ ngx_http_lua_output_filter (TYPE_3__*,TYPE_6__*) ; 
 scalar_t__ ngx_http_lua_send_header_if_needed (TYPE_3__*,TYPE_5__*) ; 
 scalar_t__ ngx_http_lua_send_http10_headers (TYPE_3__*,TYPE_5__*) ; 
 scalar_t__ ngx_http_lua_send_special (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

ngx_int_t
ngx_http_lua_send_chain_link(ngx_http_request_t *r, ngx_http_lua_ctx_t *ctx,
    ngx_chain_t *in)
{
    ngx_int_t                     rc;
    ngx_chain_t                  *cl;
    ngx_chain_t                 **ll;
    ngx_http_lua_loc_conf_t      *llcf;

#if 1
    if (ctx->acquired_raw_req_socket || ctx->eof) {
        dd("ctx->eof already set or raw req socket already acquired");
        return NGX_OK;
    }
#endif

    if ((r->method & NGX_HTTP_HEAD) && !r->header_only) {
        r->header_only = 1;
    }

    llcf = ngx_http_get_module_loc_conf(r, ngx_http_lua_module);

    if (llcf->http10_buffering
        && !ctx->buffering
        && !r->header_sent
        && !ctx->header_sent
        && r->http_version < NGX_HTTP_VERSION_11
        && r->headers_out.content_length_n < 0)
    {
        ctx->buffering = 1;
    }

    rc = ngx_http_lua_send_header_if_needed(r, ctx);

    if (rc == NGX_ERROR || rc > NGX_OK) {
        return rc;
    }

    if (r->header_only) {
        ctx->eof = 1;

        if (ctx->buffering) {
            return ngx_http_lua_send_http10_headers(r, ctx);
        }

        return rc;
    }

    if (in == NULL) {
        dd("last buf to be sent");

#if 1
        if (!r->request_body && r == r->main) {
            if (ngx_http_discard_request_body(r) != NGX_OK) {
                return NGX_ERROR;
            }
        }
#endif

        if (ctx->buffering) {
            rc = ngx_http_lua_send_http10_headers(r, ctx);
            if (rc == NGX_ERROR || rc >= NGX_HTTP_SPECIAL_RESPONSE) {
                return rc;
            }

            if (ctx->out) {

                rc = ngx_http_lua_output_filter(r, ctx->out);

                if (rc == NGX_ERROR || rc >= NGX_HTTP_SPECIAL_RESPONSE) {
                    return rc;
                }

                ctx->out = NULL;
            }
        }

#if defined(nginx_version) && nginx_version <= 8004

        /* earlier versions of nginx does not allow subrequests
           to send last_buf themselves */
        if (r != r->main) {
            return NGX_OK;
        }

#endif

        ctx->eof = 1;

        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "lua sending last buf of the response body");

        rc = ngx_http_lua_send_special(r, NGX_HTTP_LAST);

        if (rc == NGX_ERROR || rc >= NGX_HTTP_SPECIAL_RESPONSE) {
            return rc;
        }

        return NGX_OK;
    }

    /* in != NULL */

    if (ctx->buffering) {
        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "lua buffering output bufs for the HTTP 1.0 request");

        for (cl = ctx->out, ll = &ctx->out; cl; cl = cl->next) {
            ll = &cl->next;
        }

        *ll = in;

        return NGX_OK;
    }

    return ngx_http_lua_output_filter(r, in);
}