#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/  data; scalar_t__ len; } ;
typedef  TYPE_3__ ngx_str_t ;
typedef  size_t ngx_int_t ;
struct TYPE_22__ {int /*<<< orphan*/  data; scalar_t__ len; scalar_t__ not_found; } ;
typedef  TYPE_4__ ngx_http_variable_value_t ;
struct TYPE_19__ {TYPE_3__ charset; } ;
struct TYPE_23__ {TYPE_1__ headers_out; } ;
typedef  TYPE_5__ ngx_http_request_t ;
struct TYPE_24__ {TYPE_3__ name; } ;
typedef  TYPE_6__ ngx_http_charset_t ;
struct TYPE_20__ {TYPE_6__* elts; } ;
struct TYPE_25__ {TYPE_2__ charsets; } ;
typedef  TYPE_7__ ngx_http_charset_main_conf_t ;
struct TYPE_26__ {size_t source_charset; } ;
typedef  TYPE_8__ ngx_http_charset_loc_conf_t ;

/* Variables and functions */
 size_t NGX_ERROR ; 
 size_t NGX_HTTP_CHARSET_OFF ; 
 size_t NGX_HTTP_CHARSET_VAR ; 
 int /*<<< orphan*/  ngx_http_charset_filter_module ; 
 size_t ngx_http_get_charset (TYPE_5__*,TYPE_3__*) ; 
 TYPE_4__* ngx_http_get_indexed_variable (TYPE_5__*,size_t) ; 
 TYPE_8__* ngx_http_get_module_loc_conf (TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_7__* ngx_http_get_module_main_conf (TYPE_5__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_source_charset(ngx_http_request_t *r, ngx_str_t *name)
{
    ngx_int_t                      charset;
    ngx_http_charset_t            *charsets;
    ngx_http_variable_value_t     *vv;
    ngx_http_charset_loc_conf_t   *lcf;
    ngx_http_charset_main_conf_t  *mcf;

    if (r->headers_out.charset.len) {
        *name = r->headers_out.charset;
        return ngx_http_get_charset(r, name);
    }

    lcf = ngx_http_get_module_loc_conf(r, ngx_http_charset_filter_module);

    charset = lcf->source_charset;

    if (charset == NGX_HTTP_CHARSET_OFF) {
        name->len = 0;
        return charset;
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