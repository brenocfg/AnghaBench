#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_17__ {scalar_t__ status; } ;
struct TYPE_18__ {int preserve_body; int /*<<< orphan*/  pool; struct TYPE_18__* main; TYPE_3__ headers_out; } ;
typedef  TYPE_4__ ngx_http_request_t ;
typedef  int /*<<< orphan*/  ngx_http_addition_ctx_t ;
struct TYPE_16__ {scalar_t__ len; } ;
struct TYPE_15__ {scalar_t__ len; } ;
struct TYPE_19__ {int /*<<< orphan*/  types; TYPE_2__ after_body; TYPE_1__ before_body; } ;
typedef  TYPE_5__ ngx_http_addition_conf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 scalar_t__ NGX_HTTP_OK ; 
 int /*<<< orphan*/  ngx_http_addition_filter_module ; 
 int /*<<< orphan*/  ngx_http_clear_accept_ranges (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_http_clear_content_length (TYPE_4__*) ; 
 TYPE_5__* ngx_http_get_module_loc_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_next_header_filter (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_http_set_ctx (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_http_test_content_type (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_weak_etag (TYPE_4__*) ; 
 int /*<<< orphan*/ * ngx_pcalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_addition_header_filter(ngx_http_request_t *r)
{
    ngx_http_addition_ctx_t   *ctx;
    ngx_http_addition_conf_t  *conf;

    if (r->headers_out.status != NGX_HTTP_OK || r != r->main) {
        return ngx_http_next_header_filter(r);
    }

    conf = ngx_http_get_module_loc_conf(r, ngx_http_addition_filter_module);

    if (conf->before_body.len == 0 && conf->after_body.len == 0) {
        return ngx_http_next_header_filter(r);
    }

    if (ngx_http_test_content_type(r, &conf->types) == NULL) {
        return ngx_http_next_header_filter(r);
    }

    ctx = ngx_pcalloc(r->pool, sizeof(ngx_http_addition_ctx_t));
    if (ctx == NULL) {
        return NGX_ERROR;
    }

    ngx_http_set_ctx(r, ctx, ngx_http_addition_filter_module);

    ngx_http_clear_content_length(r);
    ngx_http_clear_accept_ranges(r);
    ngx_http_weak_etag(r);

    r->preserve_body = 1;

    return ngx_http_next_header_filter(r);
}