#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_11__ {TYPE_1__* connection; int /*<<< orphan*/  pool; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_10__ {int /*<<< orphan*/  log_error; int /*<<< orphan*/  log; } ;
struct TYPE_12__ {TYPE_3__* request; TYPE_2__ peer; } ;
typedef  TYPE_4__ ngx_http_proxy_connect_upstream_t ;
struct TYPE_13__ {TYPE_4__* u; } ;
typedef  TYPE_5__ ngx_http_proxy_connect_ctx_t ;
struct TYPE_9__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_ERROR_ERR ; 
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_4__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_proxy_connect_upstream_create(ngx_http_request_t *r,
    ngx_http_proxy_connect_ctx_t *ctx)
{
    ngx_http_proxy_connect_upstream_t       *u;

    u = ngx_pcalloc(r->pool, sizeof(ngx_http_proxy_connect_upstream_t));
    if (u == NULL) {
        return NGX_ERROR;
    }

    ctx->u = u;

    u->peer.log = r->connection->log;
    u->peer.log_error = NGX_ERROR_ERR;

    u->request = r;

    return NGX_OK;
}