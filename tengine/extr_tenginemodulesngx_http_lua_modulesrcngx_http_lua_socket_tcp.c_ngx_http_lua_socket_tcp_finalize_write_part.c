#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_1__* connection; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_16__ {TYPE_6__* connection; } ;
struct TYPE_18__ {int write_closed; TYPE_2__ peer; scalar_t__ body_downstream; scalar_t__ raw_downstream; } ;
typedef  TYPE_4__ ngx_http_lua_socket_tcp_upstream_t ;
struct TYPE_19__ {scalar_t__ writing_raw_req_socket; } ;
typedef  TYPE_5__ ngx_http_lua_ctx_t ;
struct TYPE_20__ {TYPE_11__* write; } ;
typedef  TYPE_6__ ngx_connection_t ;
struct TYPE_15__ {TYPE_11__* write; } ;
struct TYPE_14__ {int error; int closed; scalar_t__ prev; scalar_t__ disabled; scalar_t__ active; scalar_t__ timer_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_CLOSE_EVENT ; 
 int /*<<< orphan*/  NGX_WRITE_EVENT ; 
 int /*<<< orphan*/  ngx_del_event (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_del_timer (TYPE_11__*) ; 
 int /*<<< orphan*/  ngx_delete_posted_event (TYPE_11__*) ; 
 TYPE_5__* ngx_http_get_module_ctx (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 

__attribute__((used)) static void
ngx_http_lua_socket_tcp_finalize_write_part(ngx_http_request_t *r,
    ngx_http_lua_socket_tcp_upstream_t *u)
{
    ngx_connection_t                    *c;
    ngx_http_lua_ctx_t                  *ctx;

    if (u->write_closed) {
        return;
    }

    u->write_closed = 1;

    ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);

    if (u->raw_downstream || u->body_downstream) {
        if (ctx && ctx->writing_raw_req_socket) {
            ctx->writing_raw_req_socket = 0;
            if (r->connection->write->timer_set) {
                ngx_del_timer(r->connection->write);
            }

            r->connection->write->error = 1;
        }
        return;
    }

    c = u->peer.connection;

    if (c) {
        if (c->write->timer_set) {
            ngx_del_timer(c->write);
        }

        if (c->write->active || c->write->disabled) {
            ngx_del_event(c->write, NGX_WRITE_EVENT, NGX_CLOSE_EVENT);
        }

#if defined(nginx_version) && nginx_version >= 1007005
        if (c->write->posted) {
#else
        if (c->write->prev) {
#endif
            ngx_delete_posted_event(c->write);
        }

        c->write->closed = 1;

        /* TODO: shutdown the writing part of the connection */
    }
}