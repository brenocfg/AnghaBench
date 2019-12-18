#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_16__ ;
typedef  struct TYPE_19__   TYPE_15__ ;
typedef  struct TYPE_18__   TYPE_14__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
typedef  int ngx_uint_t ;
struct TYPE_23__ {TYPE_6__* connection; TYPE_2__* proxy; TYPE_7__* buffer; } ;
typedef  TYPE_3__ ngx_mail_session_t ;
struct TYPE_24__ {int /*<<< orphan*/  timeout; } ;
typedef  TYPE_4__ ngx_mail_proxy_conf_t ;
struct TYPE_25__ {int /*<<< orphan*/  log; scalar_t__ write; scalar_t__ timedout; TYPE_6__* data; } ;
typedef  TYPE_5__ ngx_event_t ;
struct TYPE_26__ {int timedout; scalar_t__ (* send ) (TYPE_6__*,size_t,size_t) ;scalar_t__ (* recv ) (TYPE_6__*,size_t,size_t) ;TYPE_16__* read; TYPE_15__* write; TYPE_14__* log; int /*<<< orphan*/  fd; scalar_t__ close; TYPE_3__* data; } ;
typedef  TYPE_6__ ngx_connection_t ;
struct TYPE_27__ {size_t last; size_t pos; scalar_t__ start; size_t end; } ;
typedef  TYPE_7__ ngx_buf_t ;
struct TYPE_21__ {TYPE_6__* connection; } ;
struct TYPE_22__ {TYPE_1__ upstream; TYPE_7__* buffer; } ;
struct TYPE_20__ {int eof; scalar_t__ ready; } ;
struct TYPE_19__ {scalar_t__ ready; } ;
struct TYPE_18__ {char* action; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_ETIMEDOUT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_MAIL ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_16__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_handle_read_event (TYPE_16__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_handle_write_event (TYPE_15__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,TYPE_14__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_4__* ngx_mail_get_module_srv_conf (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_mail_proxy_close_session (TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_mail_proxy_module ; 
 scalar_t__ stub1 (TYPE_6__*,size_t,size_t) ; 
 scalar_t__ stub2 (TYPE_6__*,size_t,size_t) ; 

__attribute__((used)) static void
ngx_mail_proxy_handler(ngx_event_t *ev)
{
    char                   *action, *recv_action, *send_action;
    size_t                  size;
    ssize_t                 n;
    ngx_buf_t              *b;
    ngx_uint_t              do_write;
    ngx_connection_t       *c, *src, *dst;
    ngx_mail_session_t     *s;
    ngx_mail_proxy_conf_t  *pcf;

    c = ev->data;
    s = c->data;

    if (ev->timedout || c->close) {
        c->log->action = "proxying";

        if (c->close) {
            ngx_log_error(NGX_LOG_INFO, c->log, 0, "shutdown timeout");

        } else if (c == s->connection) {
            ngx_log_error(NGX_LOG_INFO, c->log, NGX_ETIMEDOUT,
                          "client timed out");
            c->timedout = 1;

        } else {
            ngx_log_error(NGX_LOG_INFO, c->log, NGX_ETIMEDOUT,
                          "upstream timed out");
        }

        ngx_mail_proxy_close_session(s);
        return;
    }

    if (c == s->connection) {
        if (ev->write) {
            recv_action = "proxying and reading from upstream";
            send_action = "proxying and sending to client";
            src = s->proxy->upstream.connection;
            dst = c;
            b = s->proxy->buffer;

        } else {
            recv_action = "proxying and reading from client";
            send_action = "proxying and sending to upstream";
            src = c;
            dst = s->proxy->upstream.connection;
            b = s->buffer;
        }

    } else {
        if (ev->write) {
            recv_action = "proxying and reading from client";
            send_action = "proxying and sending to upstream";
            src = s->connection;
            dst = c;
            b = s->buffer;

        } else {
            recv_action = "proxying and reading from upstream";
            send_action = "proxying and sending to client";
            src = c;
            dst = s->connection;
            b = s->proxy->buffer;
        }
    }

    do_write = ev->write ? 1 : 0;

    ngx_log_debug3(NGX_LOG_DEBUG_MAIL, ev->log, 0,
                   "mail proxy handler: %ui, #%d > #%d",
                   do_write, src->fd, dst->fd);

    for ( ;; ) {

        if (do_write) {

            size = b->last - b->pos;

            if (size && dst->write->ready) {
                c->log->action = send_action;

                n = dst->send(dst, b->pos, size);

                if (n == NGX_ERROR) {
                    ngx_mail_proxy_close_session(s);
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
            c->log->action = recv_action;

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

    c->log->action = "proxying";

    if ((s->connection->read->eof && s->buffer->pos == s->buffer->last)
        || (s->proxy->upstream.connection->read->eof
            && s->proxy->buffer->pos == s->proxy->buffer->last)
        || (s->connection->read->eof
            && s->proxy->upstream.connection->read->eof))
    {
        action = c->log->action;
        c->log->action = NULL;
        ngx_log_error(NGX_LOG_INFO, c->log, 0, "proxied session done");
        c->log->action = action;

        ngx_mail_proxy_close_session(s);
        return;
    }

    if (ngx_handle_write_event(dst->write, 0) != NGX_OK) {
        ngx_mail_proxy_close_session(s);
        return;
    }

    if (ngx_handle_read_event(dst->read, 0) != NGX_OK) {
        ngx_mail_proxy_close_session(s);
        return;
    }

    if (ngx_handle_write_event(src->write, 0) != NGX_OK) {
        ngx_mail_proxy_close_session(s);
        return;
    }

    if (ngx_handle_read_event(src->read, 0) != NGX_OK) {
        ngx_mail_proxy_close_session(s);
        return;
    }

    if (c == s->connection) {
        pcf = ngx_mail_get_module_srv_conf(s, ngx_mail_proxy_module);
        ngx_add_timer(c->read, pcf->timeout);
    }
}