#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_16__ ;

/* Type definitions */
struct TYPE_21__ {TYPE_1__* connection; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_20__ {int /*<<< orphan*/  name; TYPE_6__* connection; } ;
struct TYPE_22__ {TYPE_2__ peer; scalar_t__ connected; } ;
typedef  TYPE_4__ ngx_http_proxy_connect_upstream_t ;
struct TYPE_23__ {int /*<<< orphan*/  send_established_done; int /*<<< orphan*/  send_established; } ;
typedef  TYPE_5__ ngx_http_proxy_connect_ctx_t ;
struct TYPE_24__ {TYPE_16__* write; int /*<<< orphan*/  log; } ;
typedef  TYPE_6__ ngx_connection_t ;
struct TYPE_19__ {int /*<<< orphan*/  log; } ;
struct TYPE_18__ {scalar_t__ timer_set; scalar_t__ timedout; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_HTTP_BAD_GATEWAY ; 
 int /*<<< orphan*/  NGX_HTTP_GATEWAY_TIME_OUT ; 
 int /*<<< orphan*/  NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_del_timer (TYPE_16__*) ; 
 scalar_t__ ngx_handle_write_event (TYPE_16__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* ngx_http_get_module_ctx (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_proxy_connect_finalize_request (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_proxy_connect_module ; 
 int /*<<< orphan*/  ngx_http_proxy_connect_send_connection_established (TYPE_3__*) ; 
 scalar_t__ ngx_http_proxy_connect_test_connect (TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_http_proxy_connect_tunnel (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ngx_http_proxy_connect_write_upstream(ngx_http_request_t *r,
    ngx_http_proxy_connect_upstream_t *u)
{
    ngx_connection_t  *c;
    ngx_http_proxy_connect_ctx_t          *ctx;

    c = u->peer.connection;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "proxy_connect: upstream write handler");

    if (c->write->timedout) {
        ngx_log_error(NGX_LOG_ERR, c->log, 0,
                      "proxy_connect: upstream %s timed out (peer:%V)",
                      u->connected ? "write" : "connect", u->peer.name);
        ngx_http_proxy_connect_finalize_request(r, u,
                                                NGX_HTTP_GATEWAY_TIME_OUT);
        return;
    }

    ctx = ngx_http_get_module_ctx(r, ngx_http_proxy_connect_module);

    if (c->write->timer_set) {
        ngx_del_timer(c->write);
    }

    if (!ctx->send_established &&
        ngx_http_proxy_connect_test_connect(c) != NGX_OK)
    {
        ngx_http_proxy_connect_finalize_request(r, u, NGX_HTTP_BAD_GATEWAY);
        return;
    }

    if (!ctx->send_established) {
        ngx_http_proxy_connect_send_connection_established(r);
        return;
    }

    if (!ctx->send_established_done) {
        if (ngx_handle_write_event(c->write, 0) != NGX_OK) {
            ngx_http_proxy_connect_finalize_request(r, u,
                                               NGX_HTTP_INTERNAL_SERVER_ERROR);
            return;
        }

        return;
    }

    ngx_http_proxy_connect_tunnel(r, 0, 1);
}