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
typedef  struct TYPE_25__   TYPE_11__ ;
typedef  struct TYPE_24__   TYPE_10__ ;

/* Type definitions */
struct TYPE_31__ {int /*<<< orphan*/  data; scalar_t__ len; } ;
typedef  TYPE_6__ ngx_str_t ;
typedef  size_t ngx_int_t ;
struct TYPE_32__ {int /*<<< orphan*/  data; scalar_t__ len; scalar_t__ not_found; } ;
typedef  TYPE_7__ ngx_http_variable_value_t ;
struct TYPE_28__ {scalar_t__ len; } ;
struct TYPE_26__ {scalar_t__ len; } ;
struct TYPE_29__ {TYPE_3__ charset; TYPE_6__* override_charset; TYPE_1__ content_type; } ;
struct TYPE_33__ {TYPE_4__ headers_out; TYPE_2__* connection; } ;
typedef  TYPE_8__ ngx_http_request_t ;
struct TYPE_34__ {TYPE_6__ name; } ;
typedef  TYPE_9__ ngx_http_charset_t ;
struct TYPE_30__ {TYPE_9__* elts; } ;
struct TYPE_24__ {TYPE_5__ charsets; } ;
typedef  TYPE_10__ ngx_http_charset_main_conf_t ;
struct TYPE_25__ {size_t charset; scalar_t__ override_charset; int /*<<< orphan*/  types; } ;
typedef  TYPE_11__ ngx_http_charset_loc_conf_t ;
struct TYPE_27__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 size_t NGX_DECLINED ; 
 size_t NGX_ERROR ; 
 size_t NGX_HTTP_CHARSET_OFF ; 
 size_t NGX_HTTP_CHARSET_VAR ; 
 size_t NGX_HTTP_NO_CHARSET ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  ngx_http_charset_filter_module ; 
 size_t ngx_http_get_charset (TYPE_8__*,TYPE_6__*) ; 
 TYPE_7__* ngx_http_get_indexed_variable (TYPE_8__*,size_t) ; 
 TYPE_11__* ngx_http_get_module_loc_conf (TYPE_8__*,int /*<<< orphan*/ ) ; 
 TYPE_10__* ngx_http_get_module_main_conf (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_http_test_content_type (TYPE_8__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_6__*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_destination_charset(ngx_http_request_t *r, ngx_str_t *name)
{
    ngx_int_t                      charset;
    ngx_http_charset_t            *charsets;
    ngx_http_variable_value_t     *vv;
    ngx_http_charset_loc_conf_t   *mlcf;
    ngx_http_charset_main_conf_t  *mcf;

    if (r->headers_out.content_type.len == 0) {
        return NGX_DECLINED;
    }

    if (r->headers_out.override_charset
        && r->headers_out.override_charset->len)
    {
        *name = *r->headers_out.override_charset;

        charset = ngx_http_get_charset(r, name);

        if (charset != NGX_HTTP_NO_CHARSET) {
            return charset;
        }

        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                      "unknown charset \"%V\" to override", name);

        return NGX_DECLINED;
    }

    mlcf = ngx_http_get_module_loc_conf(r, ngx_http_charset_filter_module);
    charset = mlcf->charset;

    if (charset == NGX_HTTP_CHARSET_OFF) {
        return NGX_DECLINED;
    }

    if (r->headers_out.charset.len) {
        if (mlcf->override_charset == 0) {
            return NGX_DECLINED;
        }

    } else {
        if (ngx_http_test_content_type(r, &mlcf->types) == NULL) {
            return NGX_DECLINED;
        }
    }

    if (charset < NGX_HTTP_CHARSET_VAR) {
        mcf = ngx_http_get_module_main_conf(r, ngx_http_charset_filter_module);
        charsets = mcf->charsets.elts;
        *name = charsets[charset].name;
        return charset;
    }

    vv = ngx_http_get_indexed_variable(r, charset - NGX_HTTP_CHARSET_VAR);

    if (vv == NULL || vv->not_found) {
        return NGX_ERROR;
    }

    name->len = vv->len;
    name->data = vv->data;

    return ngx_http_get_charset(r, name);
}