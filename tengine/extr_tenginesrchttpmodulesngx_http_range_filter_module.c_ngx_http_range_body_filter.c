#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_request_t ;
struct TYPE_13__ {int nelts; } ;
struct TYPE_14__ {TYPE_1__ ranges; } ;
typedef  TYPE_2__ ngx_http_range_filter_ctx_t ;
struct TYPE_15__ {int /*<<< orphan*/  buf; } ;
typedef  TYPE_3__ ngx_chain_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_buf_special (int /*<<< orphan*/ ) ; 
 TYPE_2__* ngx_http_get_module_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_next_body_filter (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_http_range_body_filter_module ; 
 int /*<<< orphan*/  ngx_http_range_multipart_body (int /*<<< orphan*/ *,TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_http_range_singlepart_body (int /*<<< orphan*/ *,TYPE_2__*,TYPE_3__*) ; 
 scalar_t__ ngx_http_range_test_overlapped (int /*<<< orphan*/ *,TYPE_2__*,TYPE_3__*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_range_body_filter(ngx_http_request_t *r, ngx_chain_t *in)
{
    ngx_http_range_filter_ctx_t  *ctx;

    if (in == NULL) {
        return ngx_http_next_body_filter(r, in);
    }

    ctx = ngx_http_get_module_ctx(r, ngx_http_range_body_filter_module);

    if (ctx == NULL) {
        return ngx_http_next_body_filter(r, in);
    }

    if (ctx->ranges.nelts == 1) {
        return ngx_http_range_singlepart_body(r, ctx, in);
    }

    /*
     * multipart ranges are supported only if whole body is in a single buffer
     */

    if (ngx_buf_special(in->buf)) {
        return ngx_http_next_body_filter(r, in);
    }

    if (ngx_http_range_test_overlapped(r, ctx, in) != NGX_OK) {
        return NGX_ERROR;
    }

    return ngx_http_range_multipart_body(r, ctx, in);
}