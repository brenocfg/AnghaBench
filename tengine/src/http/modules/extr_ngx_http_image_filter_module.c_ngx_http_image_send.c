#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_7__ {scalar_t__ header_only; } ;
typedef  TYPE_1__ ngx_http_request_t ;
struct TYPE_8__ {scalar_t__ phase; } ;
typedef  TYPE_2__ ngx_http_image_filter_ctx_t ;
typedef  int /*<<< orphan*/  ngx_chain_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_HTTP_IMAGE_DONE ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_http_next_body_filter (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_http_next_header_filter (TYPE_1__*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_image_send(ngx_http_request_t *r, ngx_http_image_filter_ctx_t *ctx,
    ngx_chain_t *in)
{
    ngx_int_t  rc;

    rc = ngx_http_next_header_filter(r);

    if (rc == NGX_ERROR || rc > NGX_OK || r->header_only) {
        return NGX_ERROR;
    }

    rc = ngx_http_next_body_filter(r, in);

    if (ctx->phase == NGX_HTTP_IMAGE_DONE) {
        /* NGX_ERROR resets any pending data */
        return (rc == NGX_OK) ? NGX_ERROR : rc;
    }

    return rc;
}