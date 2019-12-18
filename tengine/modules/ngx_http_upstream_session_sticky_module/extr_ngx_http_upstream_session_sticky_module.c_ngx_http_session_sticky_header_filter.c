#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  size_t ngx_uint_t ;
struct TYPE_25__ {int len; int /*<<< orphan*/  data; } ;
struct TYPE_28__ {int /*<<< orphan*/  value; TYPE_3__ key; } ;
typedef  TYPE_6__ ngx_table_elt_t ;
struct TYPE_29__ {size_t nelts; struct TYPE_29__* next; scalar_t__ elts; } ;
typedef  TYPE_7__ ngx_list_part_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_30__ {scalar_t__ uscf; } ;
typedef  TYPE_8__ ngx_http_ss_loc_conf_t ;
struct TYPE_31__ {TYPE_4__* sscf; } ;
typedef  TYPE_9__ ngx_http_ss_ctx_t ;
struct TYPE_23__ {TYPE_7__ part; } ;
struct TYPE_24__ {scalar_t__ status; TYPE_1__ headers; } ;
struct TYPE_22__ {TYPE_5__* connection; TYPE_2__ headers_out; } ;
typedef  TYPE_10__ ngx_http_request_t ;
struct TYPE_27__ {int /*<<< orphan*/  log; } ;
struct TYPE_26__ {int flag; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_CONF_UNSET_PTR ; 
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_HTTP_BAD_REQUEST ; 
 int NGX_HTTP_SESSION_STICKY_INDIRECT ; 
 int NGX_HTTP_SESSION_STICKY_INSERT ; 
 int NGX_HTTP_SESSION_STICKY_PREFIX ; 
 int NGX_HTTP_SESSION_STICKY_REWRITE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 TYPE_9__* ngx_http_get_module_ctx (TYPE_10__*,int /*<<< orphan*/ ) ; 
 TYPE_8__* ngx_http_get_module_loc_conf (TYPE_10__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_session_sticky_insert (TYPE_10__*) ; 
 scalar_t__ ngx_http_session_sticky_prefix (TYPE_10__*,TYPE_6__*) ; 
 scalar_t__ ngx_http_session_sticky_rewrite (TYPE_10__*,TYPE_6__*) ; 
 scalar_t__ ngx_http_ss_next_header_filter (TYPE_10__*) ; 
 int /*<<< orphan*/  ngx_http_upstream_session_sticky_module ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ngx_strncasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_session_sticky_header_filter(ngx_http_request_t *r)
{
    ngx_int_t                rc;
    ngx_uint_t               i;
    ngx_list_part_t         *part;
    ngx_table_elt_t         *table;
    ngx_http_ss_ctx_t       *ctx;
    ngx_http_ss_loc_conf_t  *slcf;

    if (r->headers_out.status >= NGX_HTTP_BAD_REQUEST) {
        return ngx_http_ss_next_header_filter(r);
    }

    slcf = ngx_http_get_module_loc_conf(r,
               ngx_http_upstream_session_sticky_module);

    ctx = ngx_http_get_module_ctx(r, ngx_http_upstream_session_sticky_module);
    if (ctx == NULL || ctx->sscf == NULL || ctx->sscf->flag == 0) {
        return ngx_http_ss_next_header_filter(r);
    }

    if ((slcf->uscf == NGX_CONF_UNSET_PTR)
         && ((ctx->sscf->flag & NGX_HTTP_SESSION_STICKY_PREFIX)
            || (ctx->sscf->flag & NGX_HTTP_SESSION_STICKY_INDIRECT)))
    {
        return ngx_http_ss_next_header_filter(r);
    }

    if (ctx->sscf->flag
        & (NGX_HTTP_SESSION_STICKY_PREFIX | NGX_HTTP_SESSION_STICKY_REWRITE))
    {
        part = &r->headers_out.headers.part;
        while (part) {
            table = (ngx_table_elt_t *) part->elts;
            for (i = 0; i < part->nelts; i++) {
                if (table[i].key.len == (sizeof("set-cookie") - 1)
                    && ngx_strncasecmp(table[i].key.data,
                                       (u_char *) "set-cookie",
                                       table[i].key.len) == 0)
                {
                    if (ctx->sscf->flag & NGX_HTTP_SESSION_STICKY_REWRITE) {

                        rc = ngx_http_session_sticky_rewrite(r, &table[i]);
                        if (rc == NGX_AGAIN) {
                            continue;

                        } else if (rc == NGX_ERROR) {
                            ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                                          "session_sticky [rewrite]"
                                          "set-cookie failed");
                        }

                        ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log,
                                       0,
                                       "session_sticky [rewrite] set-cookie:%V",
                                       &table[i].value);

                        return ngx_http_ss_next_header_filter(r);
                    }

                    rc = ngx_http_session_sticky_prefix(r, &table[i]);
                    if (rc == NGX_AGAIN) {
                        continue;

                    } else if (rc == NGX_ERROR) {
                        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                                      "session_sticky [prefix]"
                                      "set-cookie failed");
                    }

                    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log,
                                   0, "session_sticky [prefix]"
                                   "set-cookie: %V",
                                   &table[i].value);

                    return ngx_http_ss_next_header_filter(r);
                }
            }

            part = part->next;
        }

    } else if (ctx->sscf->flag & NGX_HTTP_SESSION_STICKY_INSERT) {
        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "session_sticky [insert]");

        rc = ngx_http_session_sticky_insert(r);
        if (rc != NGX_OK) {
            ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                          "session_sticky [insert] failed");
        }
    }

    return ngx_http_ss_next_header_filter(r);
}