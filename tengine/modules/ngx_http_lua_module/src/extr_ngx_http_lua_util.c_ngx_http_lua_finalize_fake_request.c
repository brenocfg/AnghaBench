#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_ssl_conn_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_14__ {TYPE_5__* connection; TYPE_1__* main; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_15__ {scalar_t__ exit_code; } ;
typedef  TYPE_4__ ngx_http_lua_ssl_ctx_t ;
struct TYPE_16__ {TYPE_10__* write; TYPE_10__* read; TYPE_2__* ssl; TYPE_3__* data; int /*<<< orphan*/  log; } ;
typedef  TYPE_5__ ngx_connection_t ;
struct TYPE_13__ {int /*<<< orphan*/ * connection; } ;
struct TYPE_12__ {int /*<<< orphan*/  count; } ;
struct TYPE_11__ {scalar_t__ delayed; scalar_t__ timer_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_DONE ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_SPECIAL_RESPONSE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  ngx_del_timer (TYPE_10__*) ; 
 int /*<<< orphan*/  ngx_http_lua_close_fake_request (TYPE_3__*) ; 
 TYPE_4__* ngx_http_lua_ssl_get_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_debug3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_5__* ngx_ssl_get_connection (int /*<<< orphan*/ *) ; 

void
ngx_http_lua_finalize_fake_request(ngx_http_request_t *r, ngx_int_t rc)
{
    ngx_connection_t          *c;
#if (NGX_HTTP_SSL)
    ngx_ssl_conn_t            *ssl_conn;
    ngx_http_lua_ssl_ctx_t    *cctx;
#endif

    c = r->connection;

    ngx_log_debug3(NGX_LOG_DEBUG_HTTP, c->log, 0,
                   "http lua finalize fake request: %d, a:%d, c:%d",
                   rc, r == c->data, r->main->count);

    if (rc == NGX_DONE) {
        ngx_http_lua_close_fake_request(r);
        return;
    }

    if (rc == NGX_ERROR || rc >= NGX_HTTP_SPECIAL_RESPONSE) {

#if (NGX_HTTP_SSL)

        if (r->connection->ssl) {
            ssl_conn = r->connection->ssl->connection;
            if (ssl_conn) {
                c = ngx_ssl_get_connection(ssl_conn);

                if (c && c->ssl) {
                    cctx = ngx_http_lua_ssl_get_ctx(c->ssl->connection);
                    if (cctx != NULL) {
                        cctx->exit_code = 0;
                    }
                }
            }
        }

#endif

        ngx_http_lua_close_fake_request(r);
        return;
    }

    if (c->read->timer_set) {
        ngx_del_timer(c->read);
    }

    if (c->write->timer_set) {
        c->write->delayed = 0;
        ngx_del_timer(c->write);
    }

    ngx_http_lua_close_fake_request(r);
}