#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_18__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
typedef  int ngx_uint_t ;
struct TYPE_25__ {int /*<<< orphan*/  pool; TYPE_8__* header_in; TYPE_7__* connection; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_30__ {scalar_t__ last; scalar_t__ pos; int temporary; int /*<<< orphan*/ * end; int /*<<< orphan*/ * start; } ;
struct TYPE_23__ {TYPE_7__* connection; } ;
struct TYPE_26__ {TYPE_2__* conf; TYPE_8__ from_client; TYPE_8__ buffer; TYPE_1__ peer; } ;
typedef  TYPE_4__ ngx_http_proxy_connect_upstream_t ;
struct TYPE_27__ {int /*<<< orphan*/  read_timeout; int /*<<< orphan*/  send_timeout; TYPE_4__* u; } ;
typedef  TYPE_5__ ngx_http_proxy_connect_ctx_t ;
struct TYPE_28__ {int /*<<< orphan*/  client_body_timeout; int /*<<< orphan*/  send_timeout; int /*<<< orphan*/  send_lowat; } ;
typedef  TYPE_6__ ngx_http_core_loc_conf_t ;
struct TYPE_29__ {scalar_t__ (* send ) (TYPE_7__*,int /*<<< orphan*/ *,size_t) ;scalar_t__ (* recv ) (TYPE_7__*,int /*<<< orphan*/ *,size_t) ;TYPE_18__* read; TYPE_18__* write; int /*<<< orphan*/  log; } ;
typedef  TYPE_7__ ngx_connection_t ;
typedef  TYPE_8__ ngx_buf_t ;
struct TYPE_24__ {int buffer_size; int /*<<< orphan*/  send_lowat; } ;
struct TYPE_22__ {int eof; scalar_t__ timer_set; scalar_t__ ready; scalar_t__ active; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_18__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_del_timer (TYPE_18__*) ; 
 scalar_t__ ngx_handle_read_event (TYPE_18__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_handle_write_event (TYPE_18__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 TYPE_5__* ngx_http_get_module_ctx (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_6__* ngx_http_get_module_loc_conf (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_proxy_connect_finalize_request (TYPE_3__*,TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_http_proxy_connect_module ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/ * ngx_palloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (TYPE_7__*,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ stub2 (TYPE_7__*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void
ngx_http_proxy_connect_tunnel(ngx_http_request_t *r,
    ngx_uint_t from_upstream, ngx_uint_t do_write)
{
    size_t                              size;
    ssize_t                             n;
    ngx_buf_t                          *b;
    ngx_connection_t                   *c, *downstream, *upstream, *dst, *src;
    ngx_http_core_loc_conf_t           *clcf;
    ngx_http_proxy_connect_ctx_t       *ctx;
    ngx_http_proxy_connect_upstream_t  *u;

    ctx = ngx_http_get_module_ctx(r, ngx_http_proxy_connect_module);

    c = r->connection;
    u = ctx->u;

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, c->log, 0,
                   "proxy_connect: tunnel fu:%ui write:%ui",
                   from_upstream, do_write);

    downstream = c;
    upstream = u->peer.connection;

    if (from_upstream) {
        src = upstream;
        dst = downstream;
        b = &u->buffer;

    } else {
        src = downstream;
        dst = upstream;
        b = &u->from_client;

        if (r->header_in->last > r->header_in->pos) {
            b = r->header_in;
            b->end = b->last;
            do_write = 1;
        }

        if (b->start == NULL) {
            b->start = ngx_palloc(r->pool, u->conf->buffer_size);
            if (b->start == NULL) {
                ngx_http_proxy_connect_finalize_request(r, u, NGX_ERROR);
                return;
            }

            b->pos = b->start;
            b->last = b->start;
            b->end = b->start + u->conf->buffer_size;
            b->temporary = 1;
        }
    }

    for ( ;; ) {

        if (do_write) {

            size = b->last - b->pos;

            if (size && dst->write->ready) {

                n = dst->send(dst, b->pos, size);

                if (n == NGX_AGAIN) {
                    break;
                }

                if (n == NGX_ERROR) {
                    ngx_http_proxy_connect_finalize_request(r, u, NGX_ERROR);
                    return;
                }

                if (n > 0) {
                    b->pos += n;

                    if (b->pos == b->last) {
                        b->pos = b->start;
                        b->last = b->start;
                    }
                }
            }
        }

        size = b->end - b->last;

        if (size && src->read->ready) {

            n = src->recv(src, b->last, size);

            if (n == NGX_AGAIN || n == 0) {
                break;
            }

            if (n > 0) {
                do_write = 1;
                b->last += n;

                continue;
            }

            if (n == NGX_ERROR) {
                src->read->eof = 1;
            }
        }

        break;
    }

    if ((upstream->read->eof && u->buffer.pos == u->buffer.last)
        || (downstream->read->eof && u->from_client.pos == u->from_client.last)
        || (downstream->read->eof && upstream->read->eof))
    {
        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, c->log, 0,
                       "proxy_connect: tunnel done");
        ngx_http_proxy_connect_finalize_request(r, u, 0);
        return;
    }

    clcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);

    if (ngx_handle_write_event(upstream->write, u->conf->send_lowat)
        != NGX_OK)
    {
        ngx_http_proxy_connect_finalize_request(r, u, NGX_ERROR);
        return;
    }

    if (upstream->write->active && !upstream->write->ready) {
        ngx_add_timer(upstream->write, ctx->send_timeout);

    } else if (upstream->write->timer_set) {
        ngx_del_timer(upstream->write);
    }

    if (ngx_handle_read_event(upstream->read, 0) != NGX_OK) {
        ngx_http_proxy_connect_finalize_request(r, u, NGX_ERROR);
        return;
    }

    if (upstream->read->active && !upstream->read->ready) {
        if (from_upstream) {
            ngx_add_timer(upstream->read, ctx->read_timeout);
        }

    } else if (upstream->read->timer_set) {
        ngx_del_timer(upstream->read);
    }

    if (ngx_handle_write_event(downstream->write, clcf->send_lowat)
        != NGX_OK)
    {
        ngx_http_proxy_connect_finalize_request(r, u, NGX_ERROR);
        return;
    }

    if (ngx_handle_read_event(downstream->read, 0) != NGX_OK) {
        ngx_http_proxy_connect_finalize_request(r, u, NGX_ERROR);
        return;
    }

    if (downstream->write->active && !downstream->write->ready) {
        ngx_add_timer(downstream->write, clcf->send_timeout);

    } else if (downstream->write->timer_set) {
        ngx_del_timer(downstream->write);
    }

    if (downstream->read->active && !downstream->read->ready) {
        if (!from_upstream) {
            ngx_add_timer(downstream->read, clcf->client_body_timeout);
        }

    } else if (downstream->read->timer_set) {
        ngx_del_timer(downstream->read);
    }
}