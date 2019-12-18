#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_5__* connection; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_12__ {scalar_t__ pos; scalar_t__ last; } ;
struct TYPE_14__ {TYPE_2__ buf; int /*<<< orphan*/  u; } ;
typedef  TYPE_4__ ngx_http_proxy_connect_ctx_t ;
struct TYPE_15__ {int timedout; int /*<<< orphan*/  log; TYPE_1__* write; } ;
typedef  TYPE_5__ ngx_connection_t ;
struct TYPE_11__ {scalar_t__ timedout; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_HTTP_REQUEST_TIME_OUT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 TYPE_4__* ngx_http_get_module_ctx (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_proxy_connect_finalize_request (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_proxy_connect_module ; 
 int /*<<< orphan*/  ngx_http_proxy_connect_send_connection_established (TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
ngx_http_proxy_connect_send_handler(ngx_http_request_t *r)
{
    ngx_connection_t                 *c;
    ngx_http_proxy_connect_ctx_t     *ctx;

    c = r->connection;
    ctx = ngx_http_get_module_ctx(r, ngx_http_proxy_connect_module);

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "proxy_connect: send connection established handler");

    if (c->write->timedout) {
        c->timedout = 1;
        ngx_log_error(NGX_LOG_ERR, c->log, 0,
                      "proxy_connect: client write timed out");
        ngx_http_proxy_connect_finalize_request(r, ctx->u,
                                                NGX_HTTP_REQUEST_TIME_OUT);
        return;
    }

    if (ctx->buf.pos != ctx->buf.last) {
        ngx_http_proxy_connect_send_connection_established(r);
    }
}