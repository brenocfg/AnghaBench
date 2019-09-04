#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_userid_ctx_t ;
struct TYPE_11__ {scalar_t__ enable; } ;
typedef  TYPE_1__ ngx_http_userid_conf_t ;
struct TYPE_12__ {struct TYPE_12__* main; } ;
typedef  TYPE_2__ ngx_http_request_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 scalar_t__ NGX_HTTP_USERID_V1 ; 
 scalar_t__ NGX_OK ; 
 TYPE_1__* ngx_http_get_module_loc_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_next_header_filter (TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_http_userid_filter_module ; 
 int /*<<< orphan*/ * ngx_http_userid_get_uid (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ ngx_http_userid_set_uid (TYPE_2__*,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_userid_filter(ngx_http_request_t *r)
{
    ngx_http_userid_ctx_t   *ctx;
    ngx_http_userid_conf_t  *conf;

    if (r != r->main) {
        return ngx_http_next_header_filter(r);
    }

    conf = ngx_http_get_module_loc_conf(r, ngx_http_userid_filter_module);

    if (conf->enable < NGX_HTTP_USERID_V1) {
        return ngx_http_next_header_filter(r);
    }

    ctx = ngx_http_userid_get_uid(r, conf);

    if (ctx == NULL) {
        return NGX_ERROR;
    }

    if (ngx_http_userid_set_uid(r, ctx, conf) == NGX_OK) {
        return ngx_http_next_header_filter(r);
    }

    return NGX_ERROR;
}