#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_9__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_9__* connection; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_12__ {int /*<<< orphan*/  u; } ;
typedef  TYPE_3__ ngx_http_proxy_connect_ctx_t ;
struct TYPE_13__ {int timedout; TYPE_1__* read; } ;
struct TYPE_10__ {scalar_t__ timedout; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ETIMEDOUT ; 
 int /*<<< orphan*/  NGX_HTTP_REQUEST_TIME_OUT ; 
 int /*<<< orphan*/  ngx_connection_error (TYPE_9__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* ngx_http_get_module_ctx (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_proxy_connect_finalize_request (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_proxy_connect_module ; 
 int /*<<< orphan*/  ngx_http_proxy_connect_tunnel (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ngx_http_proxy_connect_read_downstream(ngx_http_request_t *r)
{
    ngx_http_proxy_connect_ctx_t       *ctx;

    ctx = ngx_http_get_module_ctx(r, ngx_http_proxy_connect_module);

    if (r->connection->read->timedout) {
        r->connection->timedout = 1;
        ngx_connection_error(r->connection, NGX_ETIMEDOUT, "client timed out");
        ngx_http_proxy_connect_finalize_request(r, ctx->u,
                                                NGX_HTTP_REQUEST_TIME_OUT);
        return;
    }

    ngx_http_proxy_connect_tunnel(r, 0, 0);
}