#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_14__ {scalar_t__ state; TYPE_4__* upstream; } ;
typedef  TYPE_5__ ngx_http_request_t ;
struct TYPE_11__ {scalar_t__ state; } ;
struct TYPE_10__ {int /*<<< orphan*/ * end; int /*<<< orphan*/ * start; scalar_t__ count; scalar_t__ code; } ;
struct TYPE_15__ {TYPE_2__ chunked; TYPE_1__ status; } ;
typedef  TYPE_6__ ngx_http_proxy_ctx_t ;
struct TYPE_13__ {int /*<<< orphan*/  input_filter; TYPE_3__* pipe; int /*<<< orphan*/  process_header; } ;
struct TYPE_12__ {int /*<<< orphan*/  input_filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_6__* ngx_http_get_module_ctx (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_proxy_copy_filter ; 
 int /*<<< orphan*/  ngx_http_proxy_module ; 
 int /*<<< orphan*/  ngx_http_proxy_non_buffered_copy_filter ; 
 int /*<<< orphan*/  ngx_http_proxy_process_status_line ; 

__attribute__((used)) static ngx_int_t
ngx_http_proxy_reinit_request(ngx_http_request_t *r)
{
    ngx_http_proxy_ctx_t  *ctx;

    ctx = ngx_http_get_module_ctx(r, ngx_http_proxy_module);

    if (ctx == NULL) {
        return NGX_OK;
    }

    ctx->status.code = 0;
    ctx->status.count = 0;
    ctx->status.start = NULL;
    ctx->status.end = NULL;
    ctx->chunked.state = 0;

    r->upstream->process_header = ngx_http_proxy_process_status_line;
    r->upstream->pipe->input_filter = ngx_http_proxy_copy_filter;
    r->upstream->input_filter = ngx_http_proxy_non_buffered_copy_filter;
    r->state = 0;

    return NGX_OK;
}