#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_19__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_27__ {int /*<<< orphan*/  pool; TYPE_2__* connection; } ;
typedef  TYPE_5__ ngx_http_request_t ;
struct TYPE_23__ {TYPE_8__* connection; } ;
struct TYPE_28__ {TYPE_4__* conf; int /*<<< orphan*/  send_timeout; int /*<<< orphan*/  write_event_handler; scalar_t__ raw_downstream; int /*<<< orphan*/  socket_errno; TYPE_3__* request_bufs; TYPE_1__ peer; } ;
typedef  TYPE_6__ ngx_http_lua_socket_tcp_upstream_t ;
struct TYPE_29__ {int writing_raw_req_socket; int /*<<< orphan*/  busy_bufs; int /*<<< orphan*/  free_bufs; } ;
typedef  TYPE_7__ ngx_http_lua_ctx_t ;
struct TYPE_30__ {scalar_t__ (* send ) (TYPE_8__*,scalar_t__,scalar_t__) ;int error; TYPE_19__* write; int /*<<< orphan*/  log; } ;
typedef  TYPE_8__ ngx_connection_t ;
typedef  int /*<<< orphan*/  ngx_buf_tag_t ;
struct TYPE_31__ {scalar_t__ pos; scalar_t__ last; } ;
typedef  TYPE_9__ ngx_buf_t ;
struct TYPE_26__ {int /*<<< orphan*/  send_lowat; } ;
struct TYPE_25__ {TYPE_9__* buf; } ;
struct TYPE_24__ {int /*<<< orphan*/  log; } ;
struct TYPE_22__ {scalar_t__ timer_set; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_LUA_SOCKET_FT_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_19__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_chain_update_chains (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ngx_del_timer (TYPE_19__*) ; 
 scalar_t__ ngx_handle_write_event (TYPE_19__*,int /*<<< orphan*/ ) ; 
 TYPE_7__* ngx_http_get_module_ctx (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 int /*<<< orphan*/  ngx_http_lua_socket_dummy_handler ; 
 int /*<<< orphan*/  ngx_http_lua_socket_handle_write_error (TYPE_5__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_socket_handle_write_success (TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_http_lua_socket_send_handler ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_socket_errno ; 
 scalar_t__ stub1 (TYPE_8__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static ngx_int_t
ngx_http_lua_socket_send(ngx_http_request_t *r,
    ngx_http_lua_socket_tcp_upstream_t *u)
{
    ngx_int_t                    n;
    ngx_connection_t            *c;
    ngx_http_lua_ctx_t          *ctx;
    ngx_buf_t                   *b;

    c = u->peer.connection;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "lua tcp socket send data");

    ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);
    if (ctx == NULL) {
        ngx_http_lua_socket_handle_write_error(r, u,
                                               NGX_HTTP_LUA_SOCKET_FT_ERROR);
        return NGX_ERROR;
    }

    b = u->request_bufs->buf;

    for (;;) {
        n = c->send(c, b->pos, b->last - b->pos);

        if (n >= 0) {
            b->pos += n;

            if (b->pos == b->last) {
                ngx_log_debug0(NGX_LOG_DEBUG_HTTP, c->log, 0,
                               "lua tcp socket sent all the data");

                if (c->write->timer_set) {
                    ngx_del_timer(c->write);
                }


#if defined(nginx_version) && nginx_version >= 1001004
                ngx_chain_update_chains(r->pool,
#else
                ngx_chain_update_chains(
#endif
                                        &ctx->free_bufs, &ctx->busy_bufs,
                                        &u->request_bufs,
                                        (ngx_buf_tag_t) &ngx_http_lua_module);

                u->write_event_handler = ngx_http_lua_socket_dummy_handler;

                if (ngx_handle_write_event(c->write, 0) != NGX_OK) {
                    ngx_http_lua_socket_handle_write_error(r, u,
                                                NGX_HTTP_LUA_SOCKET_FT_ERROR);
                    return NGX_ERROR;
                }

                ngx_http_lua_socket_handle_write_success(r, u);
                return NGX_OK;
            }

            /* keep sending more data */
            continue;
        }

        /* NGX_ERROR || NGX_AGAIN */
        break;
    }

    if (n == NGX_ERROR) {
        c->error = 1;
        u->socket_errno = ngx_socket_errno;
        ngx_http_lua_socket_handle_write_error(r, u,
                                               NGX_HTTP_LUA_SOCKET_FT_ERROR);
        return NGX_ERROR;
    }

    /* n == NGX_AGAIN */

    if (u->raw_downstream) {
        ctx->writing_raw_req_socket = 1;
    }

    u->write_event_handler = ngx_http_lua_socket_send_handler;

    ngx_add_timer(c->write, u->send_timeout);

    if (ngx_handle_write_event(c->write, u->conf->send_lowat) != NGX_OK) {
        ngx_http_lua_socket_handle_write_error(r, u,
                                               NGX_HTTP_LUA_SOCKET_FT_ERROR);
        return NGX_ERROR;
    }

    return NGX_AGAIN;
}