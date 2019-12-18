#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_9__ ;
typedef  struct TYPE_36__   TYPE_8__ ;
typedef  struct TYPE_35__   TYPE_7__ ;
typedef  struct TYPE_34__   TYPE_6__ ;
typedef  struct TYPE_33__   TYPE_5__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
typedef  int off_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_33__ {size_t request_length; TYPE_4__* request_body; TYPE_3__* connection; int /*<<< orphan*/  args; int /*<<< orphan*/  uri; TYPE_1__* header_in; } ;
typedef  TYPE_5__ ngx_http_request_t ;
struct TYPE_28__ {size_t last; size_t pos; size_t end; } ;
struct TYPE_30__ {TYPE_9__* connection; } ;
struct TYPE_34__ {int eof; scalar_t__ (* input_filter ) (int /*<<< orphan*/ ,size_t) ;int /*<<< orphan*/  read_timeout; scalar_t__ body_downstream; int /*<<< orphan*/  socket_errno; scalar_t__ raw_downstream; TYPE_10__ buffer; scalar_t__ read_waiting; scalar_t__ ft_type; int /*<<< orphan*/  input_filter_ctx; TYPE_2__ peer; } ;
typedef  TYPE_6__ ngx_http_lua_socket_tcp_upstream_t ;
struct TYPE_35__ {scalar_t__ check_client_abort; } ;
typedef  TYPE_7__ ngx_http_lua_loc_conf_t ;
struct TYPE_36__ {scalar_t__ timer_set; scalar_t__ active; scalar_t__ ready; } ;
typedef  TYPE_8__ ngx_event_t ;
struct TYPE_37__ {scalar_t__ (* recv ) (TYPE_9__*,size_t,size_t) ;TYPE_8__* read; int /*<<< orphan*/  log; } ;
typedef  TYPE_9__ ngx_connection_t ;
typedef  TYPE_10__ ngx_buf_t ;
struct TYPE_32__ {size_t rest; } ;
struct TYPE_31__ {int /*<<< orphan*/  log; } ;
struct TYPE_29__ {int last; int pos; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_HTTP_CLIENT_CLOSED_REQUEST ; 
 int /*<<< orphan*/  NGX_HTTP_LUA_SOCKET_FT_CLIENTABORT ; 
 int /*<<< orphan*/  NGX_HTTP_LUA_SOCKET_FT_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_LUA_SOCKET_FT_NOMEM ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  dd (char*,...) ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_8__*,int /*<<< orphan*/ ) ; 
 void* ngx_copy (size_t,int,size_t) ; 
 int /*<<< orphan*/  ngx_del_timer (TYPE_8__*) ; 
 scalar_t__ ngx_handle_read_event (TYPE_8__*,int /*<<< orphan*/ ) ; 
 TYPE_7__* ngx_http_get_module_loc_conf (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_lua_check_broken_connection (TYPE_5__*,TYPE_8__*) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 int /*<<< orphan*/  ngx_http_lua_probe_req_socket_consume_preread (TYPE_5__*,int,size_t) ; 
 scalar_t__ ngx_http_lua_socket_add_input_buffer (TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_http_lua_socket_handle_read_error (TYPE_5__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_socket_handle_read_success (TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ngx_log_debug3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_debug4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_socket_errno ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ stub2 (TYPE_9__*,size_t,size_t) ; 

__attribute__((used)) static ngx_int_t
ngx_http_lua_socket_tcp_read(ngx_http_request_t *r,
    ngx_http_lua_socket_tcp_upstream_t *u)
{
    ngx_int_t                    rc;
    ngx_connection_t            *c;
    ngx_buf_t                   *b;
    ngx_event_t                 *rev;
    size_t                       size;
    ssize_t                      n;
    unsigned                     read;
    off_t                        preread = 0;
    ngx_http_lua_loc_conf_t     *llcf;

    c = u->peer.connection;
    rev = c->read;

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, c->log, 0,
                   "lua tcp socket read data: wait:%d",
                   (int) u->read_waiting);

    b = &u->buffer;
    read = 0;

    for ( ;; ) {

        size = b->last - b->pos;

        if (size || u->eof) {

            rc = u->input_filter(u->input_filter_ctx, size);

            if (rc == NGX_OK) {

                ngx_log_debug4(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                               "lua tcp socket receive done: wait:%d, eof:%d, "
                               "uri:\"%V?%V\"", (int) u->read_waiting,
                               (int) u->eof, &r->uri, &r->args);

                if (u->body_downstream
                    && b->last == b->pos
                    && r->request_body->rest == 0)
                {

                    llcf = ngx_http_get_module_loc_conf(r, ngx_http_lua_module);

                    if (llcf->check_client_abort) {
                        rc = ngx_http_lua_check_broken_connection(r, rev);

                        if (rc == NGX_OK) {
                            goto success;
                        }

                        if (rc == NGX_HTTP_CLIENT_CLOSED_REQUEST) {
                            ngx_http_lua_socket_handle_read_error(r, u,
                                          NGX_HTTP_LUA_SOCKET_FT_CLIENTABORT);

                        } else {
                            ngx_http_lua_socket_handle_read_error(r, u,
                                             NGX_HTTP_LUA_SOCKET_FT_ERROR);
                        }

                        return NGX_ERROR;
                    }
                }

#if 1
                if (ngx_handle_read_event(rev, 0) != NGX_OK) {
                    ngx_http_lua_socket_handle_read_error(r, u,
                                     NGX_HTTP_LUA_SOCKET_FT_ERROR);
                    return NGX_ERROR;
                }
#endif

success:

                ngx_http_lua_socket_handle_read_success(r, u);
                return NGX_OK;
            }

            if (rc == NGX_ERROR) {
                dd("input filter error: ft_type:%d wait:%d",
                   (int) u->ft_type, (int) u->read_waiting);

                ngx_http_lua_socket_handle_read_error(r, u,
                                                NGX_HTTP_LUA_SOCKET_FT_ERROR);
                return NGX_ERROR;
            }

            /* rc == NGX_AGAIN */

            if (u->body_downstream && r->request_body->rest == 0) {
                u->eof = 1;
            }

            continue;
        }

        if (read && !rev->ready) {
            rc = NGX_AGAIN;
            break;
        }

        size = b->end - b->last;

        if (size == 0) {
            rc = ngx_http_lua_socket_add_input_buffer(r, u);
            if (rc == NGX_ERROR) {
                ngx_http_lua_socket_handle_read_error(r, u,
                                                NGX_HTTP_LUA_SOCKET_FT_NOMEM);

                return NGX_ERROR;
            }

            b = &u->buffer;
            size = (size_t) (b->end - b->last);
        }

        if (u->raw_downstream) {
            preread = r->header_in->last - r->header_in->pos;

            if (preread) {

                if ((off_t) size > preread) {
                    size = (size_t) preread;
                }

                ngx_http_lua_probe_req_socket_consume_preread(r,
                                                              r->header_in->pos,
                                                              size);

                b->last = ngx_copy(b->last, r->header_in->pos, size);
                r->header_in->pos += size;
                continue;
            }

        } else if (u->body_downstream) {

            if (r->request_body->rest == 0) {

                dd("request body rest is zero");

                u->eof = 1;

                ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                               "lua request body exhausted");

                continue;
            }

            /* try to process the preread body */

            preread = r->header_in->last - r->header_in->pos;

            if (preread) {

                /* there is the pre-read part of the request body */

                ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                               "http client request body preread %O", preread);

                if (preread >= r->request_body->rest) {
                    preread = r->request_body->rest;
                }

                if ((off_t) size > preread) {
                    size = (size_t) preread;
                }

                ngx_http_lua_probe_req_socket_consume_preread(r,
                                                              r->header_in->pos,
                                                              size);

                b->last = ngx_copy(b->last, r->header_in->pos, size);

                r->header_in->pos += size;
                r->request_length += size;

                if (r->request_body->rest) {
                    r->request_body->rest -= size;
                }

                continue;
            }

            if (size > (size_t) r->request_body->rest) {
                size = (size_t) r->request_body->rest;
            }
        }

#if 1
        if (rev->active && !rev->ready) {
            rc = NGX_AGAIN;
            break;
        }
#endif

        ngx_log_debug3(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "lua tcp socket try to recv data %uz: \"%V?%V\"",
                       size, &r->uri, &r->args);

        n = c->recv(c, b->last, size);

        dd("read event ready: %d", (int) c->read->ready);

        read = 1;

        ngx_log_debug3(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "lua tcp socket recv returned %d: \"%V?%V\"",
                       (int) n, &r->uri, &r->args);

        if (n == NGX_AGAIN) {
            rc = NGX_AGAIN;
            dd("socket recv busy");
            break;
        }

        if (n == 0) {

            if (u->raw_downstream || u->body_downstream) {

                llcf = ngx_http_get_module_loc_conf(r, ngx_http_lua_module);

                if (llcf->check_client_abort) {

                    ngx_http_lua_socket_handle_read_error(r, u,
                                          NGX_HTTP_LUA_SOCKET_FT_CLIENTABORT);
                    return NGX_ERROR;
                }

                /* llcf->check_client_abort == 0 */

                if (u->body_downstream && r->request_body->rest) {
                    ngx_http_lua_socket_handle_read_error(r, u,
                                          NGX_HTTP_LUA_SOCKET_FT_CLIENTABORT);
                    return NGX_ERROR;
                }
            }

            u->eof = 1;

            ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                           "lua tcp socket closed");

            continue;
        }

        if (n == NGX_ERROR) {
            u->socket_errno = ngx_socket_errno;
            ngx_http_lua_socket_handle_read_error(r, u,
                                                  NGX_HTTP_LUA_SOCKET_FT_ERROR);
            return NGX_ERROR;
        }

        b->last += n;

        if (u->body_downstream) {
            r->request_length += n;
            r->request_body->rest -= n;
        }
    }

#if 1
    if (ngx_handle_read_event(rev, 0) != NGX_OK) {
        ngx_http_lua_socket_handle_read_error(r, u,
                                              NGX_HTTP_LUA_SOCKET_FT_ERROR);
        return NGX_ERROR;
    }
#endif

    if (rev->active) {
        ngx_add_timer(rev, u->read_timeout);

    } else if (rev->timer_set) {
        ngx_del_timer(rev);
    }

    return rc;
}