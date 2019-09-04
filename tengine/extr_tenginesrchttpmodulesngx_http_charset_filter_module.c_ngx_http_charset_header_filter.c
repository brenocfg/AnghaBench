#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_9__ ;
typedef  struct TYPE_37__   TYPE_8__ ;
typedef  struct TYPE_36__   TYPE_7__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;
typedef  struct TYPE_29__   TYPE_10__ ;

/* Type definitions */
struct TYPE_36__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_7__ ngx_str_t ;
typedef  size_t ngx_int_t ;
struct TYPE_33__ {int /*<<< orphan*/  len; } ;
struct TYPE_34__ {int /*<<< orphan*/  content_type_len; TYPE_4__ content_type; TYPE_2__* content_encoding; } ;
struct TYPE_37__ {TYPE_6__* connection; TYPE_5__ headers_out; struct TYPE_37__* main; } ;
typedef  TYPE_8__ ngx_http_request_t ;
struct TYPE_38__ {int /*<<< orphan*/ ** tables; } ;
typedef  TYPE_9__ ngx_http_charset_t ;
struct TYPE_32__ {TYPE_9__* elts; } ;
struct TYPE_29__ {TYPE_3__ charsets; } ;
typedef  TYPE_10__ ngx_http_charset_main_conf_t ;
struct TYPE_35__ {int /*<<< orphan*/  log; } ;
struct TYPE_30__ {scalar_t__ len; } ;
struct TYPE_31__ {TYPE_1__ value; } ;

/* Variables and functions */
 size_t NGX_DECLINED ; 
 size_t NGX_ERROR ; 
 size_t NGX_HTTP_CHARSET_OFF ; 
 size_t NGX_HTTP_NO_CHARSET ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 size_t ngx_http_charset_ctx (TYPE_8__*,TYPE_9__*,size_t,size_t) ; 
 int /*<<< orphan*/  ngx_http_charset_filter_module ; 
 size_t ngx_http_destination_charset (TYPE_8__*,TYPE_7__*) ; 
 TYPE_10__* ngx_http_get_module_main_conf (TYPE_8__*,int /*<<< orphan*/ ) ; 
 size_t ngx_http_main_request_charset (TYPE_8__*,TYPE_7__*) ; 
 size_t ngx_http_next_header_filter (TYPE_8__*) ; 
 int /*<<< orphan*/  ngx_http_set_charset (TYPE_8__*,TYPE_7__*) ; 
 size_t ngx_http_source_charset (TYPE_8__*,TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_7__*,TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_7__*,TYPE_7__*) ; 
 scalar_t__ ngx_strncasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_charset_header_filter(ngx_http_request_t *r)
{
    ngx_int_t                      charset, source_charset;
    ngx_str_t                      dst, src;
    ngx_http_charset_t            *charsets;
    ngx_http_charset_main_conf_t  *mcf;

    if (r == r->main) {
        charset = ngx_http_destination_charset(r, &dst);

    } else {
        charset = ngx_http_main_request_charset(r, &dst);
    }

    if (charset == NGX_ERROR) {
        return NGX_ERROR;
    }

    if (charset == NGX_DECLINED) {
        return ngx_http_next_header_filter(r);
    }

    /* charset: charset index or NGX_HTTP_NO_CHARSET */

    source_charset = ngx_http_source_charset(r, &src);

    if (source_charset == NGX_ERROR) {
        return NGX_ERROR;
    }

    /*
     * source_charset: charset index, NGX_HTTP_NO_CHARSET,
     *                 or NGX_HTTP_CHARSET_OFF
     */

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "charset: \"%V\" > \"%V\"", &src, &dst);

    if (source_charset == NGX_HTTP_CHARSET_OFF) {
        ngx_http_set_charset(r, &dst);

        return ngx_http_next_header_filter(r);
    }

    if (charset == NGX_HTTP_NO_CHARSET
        || source_charset == NGX_HTTP_NO_CHARSET)
    {
        if (source_charset != charset
            || ngx_strncasecmp(dst.data, src.data, dst.len) != 0)
        {
            goto no_charset_map;
        }

        ngx_http_set_charset(r, &dst);

        return ngx_http_next_header_filter(r);
    }

    if (source_charset == charset) {
        r->headers_out.content_type.len = r->headers_out.content_type_len;

        ngx_http_set_charset(r, &dst);

        return ngx_http_next_header_filter(r);
    }

    /* source_charset != charset */

    if (r->headers_out.content_encoding
        && r->headers_out.content_encoding->value.len)
    {
        return ngx_http_next_header_filter(r);
    }

    mcf = ngx_http_get_module_main_conf(r, ngx_http_charset_filter_module);
    charsets = mcf->charsets.elts;

    if (charsets[source_charset].tables == NULL
        || charsets[source_charset].tables[charset] == NULL)
    {
        goto no_charset_map;
    }

    r->headers_out.content_type.len = r->headers_out.content_type_len;

    ngx_http_set_charset(r, &dst);

    return ngx_http_charset_ctx(r, charsets, charset, source_charset);

no_charset_map:

    ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                  "no \"charset_map\" between the charsets \"%V\" and \"%V\"",
                  &src, &dst);

    return ngx_http_next_header_filter(r);
}