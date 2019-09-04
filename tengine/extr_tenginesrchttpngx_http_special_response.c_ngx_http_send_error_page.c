#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_7__ ;
typedef  struct TYPE_34__   TYPE_6__ ;
typedef  struct TYPE_33__   TYPE_5__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_25__ ;
typedef  struct TYPE_28__   TYPE_1__ ;

/* Type definitions */
struct TYPE_32__ {char* data; scalar_t__ len; } ;
struct TYPE_31__ {int hash; TYPE_4__ value; int /*<<< orphan*/  key; } ;
typedef  TYPE_3__ ngx_table_elt_t ;
typedef  TYPE_4__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_30__ {scalar_t__ msie; } ;
struct TYPE_28__ {TYPE_3__* location; int /*<<< orphan*/  headers; } ;
struct TYPE_33__ {int expect_tested; scalar_t__ err_status; scalar_t__ method; TYPE_2__ headers_in; TYPE_1__ headers_out; int /*<<< orphan*/  method_name; } ;
typedef  TYPE_5__ ngx_http_request_t ;
struct TYPE_29__ {scalar_t__ lengths; } ;
struct TYPE_34__ {scalar_t__ overwrite; TYPE_4__ args; TYPE_25__ value; } ;
typedef  TYPE_6__ ngx_http_err_page_t ;
struct TYPE_35__ {scalar_t__ msie_refresh; } ;
typedef  TYPE_7__ ngx_http_core_loc_conf_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_HTTP_GET ; 
 scalar_t__ NGX_HTTP_HEAD ; 
 scalar_t__ NGX_HTTP_MOVED_PERMANENTLY ; 
 scalar_t__ NGX_HTTP_MOVED_TEMPORARILY ; 
 scalar_t__ NGX_HTTP_OFF_3XX ; 
 scalar_t__ NGX_HTTP_OK ; 
 scalar_t__ NGX_HTTP_PERMANENT_REDIRECT ; 
 scalar_t__ NGX_HTTP_SEE_OTHER ; 
 scalar_t__ NGX_HTTP_TEMPORARY_REDIRECT ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_http_clear_location (TYPE_5__*) ; 
 scalar_t__ ngx_http_complex_value (TYPE_5__*,TYPE_25__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_http_core_get_method ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 TYPE_7__* ngx_http_get_module_loc_conf (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_internal_redirect (TYPE_5__*,TYPE_4__*,TYPE_4__*) ; 
 scalar_t__ ngx_http_named_location (TYPE_5__*,TYPE_4__*) ; 
 scalar_t__ ngx_http_send_refresh (TYPE_5__*) ; 
 scalar_t__ ngx_http_send_special_response (TYPE_5__*,TYPE_7__*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_http_split_args (TYPE_5__*,TYPE_4__*,TYPE_4__*) ; 
 TYPE_3__* ngx_list_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_str_set (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_send_error_page(ngx_http_request_t *r, ngx_http_err_page_t *err_page)
{
    ngx_int_t                  overwrite;
    ngx_str_t                  uri, args;
    ngx_table_elt_t           *location;
    ngx_http_core_loc_conf_t  *clcf;

    overwrite = err_page->overwrite;

    if (overwrite && overwrite != NGX_HTTP_OK) {
        r->expect_tested = 1;
    }

    if (overwrite >= 0) {
        r->err_status = overwrite;
    }

    if (ngx_http_complex_value(r, &err_page->value, &uri) != NGX_OK) {
        return NGX_ERROR;
    }

    if (uri.len && uri.data[0] == '/') {

        if (err_page->value.lengths) {
            ngx_http_split_args(r, &uri, &args);

        } else {
            args = err_page->args;
        }

        if (r->method != NGX_HTTP_HEAD) {
            r->method = NGX_HTTP_GET;
            r->method_name = ngx_http_core_get_method;
        }

        return ngx_http_internal_redirect(r, &uri, &args);
    }

    if (uri.len && uri.data[0] == '@') {
        return ngx_http_named_location(r, &uri);
    }

    location = ngx_list_push(&r->headers_out.headers);

    if (location == NULL) {
        return NGX_ERROR;
    }

    if (overwrite != NGX_HTTP_MOVED_PERMANENTLY
        && overwrite != NGX_HTTP_MOVED_TEMPORARILY
        && overwrite != NGX_HTTP_SEE_OTHER
        && overwrite != NGX_HTTP_TEMPORARY_REDIRECT
        && overwrite != NGX_HTTP_PERMANENT_REDIRECT)
    {
        r->err_status = NGX_HTTP_MOVED_TEMPORARILY;
    }

    location->hash = 1;
    ngx_str_set(&location->key, "Location");
    location->value = uri;

    ngx_http_clear_location(r);

    r->headers_out.location = location;

    clcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);

    if (clcf->msie_refresh && r->headers_in.msie) {
        return ngx_http_send_refresh(r);
    }

    return ngx_http_send_special_response(r, clcf, r->err_status
                                                   - NGX_HTTP_MOVED_PERMANENTLY
                                                   + NGX_HTTP_OFF_3XX);
}