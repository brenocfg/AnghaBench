#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_12__ {scalar_t__ content_length_n; int /*<<< orphan*/  status; } ;
struct TYPE_13__ {scalar_t__ method; scalar_t__ header_only; TYPE_1__ headers_out; int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_14__ {int /*<<< orphan*/ * next; TYPE_4__* buf; } ;
typedef  TYPE_3__ ngx_chain_t ;
struct TYPE_15__ {scalar_t__ pos; scalar_t__ last; } ;
typedef  TYPE_4__ ngx_buf_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_HTTP_GET ; 
 scalar_t__ NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 scalar_t__ NGX_HTTP_NOT_ALLOWED ; 
 int /*<<< orphan*/  NGX_HTTP_OK ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_http_discard_request_body (TYPE_2__*) ; 
 scalar_t__ ngx_http_output_filter (TYPE_2__*,TYPE_3__*) ; 
 scalar_t__ ngx_http_send_header (TYPE_2__*) ; 
 scalar_t__ ngx_http_slab_stat_buf (int /*<<< orphan*/ ,TYPE_4__*) ; 
 TYPE_4__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_slab_stat_handler(ngx_http_request_t *r)
{
    ngx_int_t    rc;
    ngx_buf_t   *b;
    ngx_chain_t  out;

    if (r->method != NGX_HTTP_GET) {
        return NGX_HTTP_NOT_ALLOWED;
    }

    rc = ngx_http_discard_request_body(r);
    if (rc != NGX_OK) {
        return rc;
    }

    b = ngx_pcalloc(r->pool, sizeof(ngx_buf_t));
    if (b == NULL) {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    if (ngx_http_slab_stat_buf(r->pool, b) == NGX_ERROR) {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    r->headers_out.status = NGX_HTTP_OK;
    r->headers_out.content_length_n = b->last - b->pos;

    rc = ngx_http_send_header(r);

    if (rc == NGX_ERROR || rc > NGX_OK || r->header_only) {
        return rc;
    }

    out.buf = b;
    out.next = NULL;

    return ngx_http_output_filter(r, &out);
}