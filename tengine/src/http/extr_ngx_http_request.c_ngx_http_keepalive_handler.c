#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
struct TYPE_17__ {int /*<<< orphan*/  (* handler ) (TYPE_2__*) ;int /*<<< orphan*/  kq_errno; scalar_t__ pending_eof; scalar_t__ timedout; TYPE_3__* data; } ;
typedef  TYPE_2__ ngx_event_t ;
struct TYPE_18__ {scalar_t__ (* recv ) (TYPE_3__*,int /*<<< orphan*/ *,size_t) ;scalar_t__ received; scalar_t__ destroyed; scalar_t__ sent; int /*<<< orphan*/ * data; scalar_t__ idle; TYPE_8__* log; int /*<<< orphan*/  addr_text; int /*<<< orphan*/  pool; scalar_t__ async_enable; int /*<<< orphan*/  log_error; TYPE_4__* buffer; TYPE_1__* ssl; scalar_t__ close; } ;
typedef  TYPE_3__ ngx_connection_t ;
struct TYPE_19__ {int /*<<< orphan*/ * last; int /*<<< orphan*/ * pos; int /*<<< orphan*/ * start; int /*<<< orphan*/ * end; } ;
typedef  TYPE_4__ ngx_buf_t ;
struct TYPE_20__ {char* action; int /*<<< orphan*/ * handler; } ;
struct TYPE_16__ {int no_send_shutdown; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_ERROR_IGNORE_ECONNRESET ; 
 int /*<<< orphan*/  NGX_ERROR_INFO ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 scalar_t__ NGX_OK ; 
 int NGX_USE_KQUEUE_EVENT ; 
 int /*<<< orphan*/  ngx_del_timer (TYPE_2__*) ; 
 int ngx_event_flags ; 
 scalar_t__ ngx_handle_read_event (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_close_connection (TYPE_3__*) ; 
 int /*<<< orphan*/ * ngx_http_create_request (TYPE_3__*) ; 
 int /*<<< orphan*/ * ngx_http_log_error ; 
 int /*<<< orphan*/  ngx_http_process_request_line (TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ngx_palloc (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ ngx_pfree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_reusable_connection (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_set_socket_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_socket_errno ; 
 int /*<<< orphan*/  ngx_ssl_waiting_for_async (TYPE_3__*) ; 
 scalar_t__ stub1 (TYPE_3__*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void
ngx_http_keepalive_handler(ngx_event_t *rev)
{
    size_t             size;
    ssize_t            n;
    ngx_buf_t         *b;
    ngx_connection_t  *c;

    c = rev->data;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, c->log, 0, "http keepalive handler");

    if (rev->timedout || c->close) {
        ngx_http_close_connection(c);
        return;
    }

#if (NGX_HAVE_KQUEUE)

    if (ngx_event_flags & NGX_USE_KQUEUE_EVENT) {
        if (rev->pending_eof) {
            c->log->handler = NULL;
            ngx_log_error(NGX_LOG_INFO, c->log, rev->kq_errno,
                          "kevent() reported that client %V closed "
                          "keepalive connection", &c->addr_text);
#if (NGX_HTTP_SSL)
            if (c->ssl) {
                c->ssl->no_send_shutdown = 1;
            }
#endif
            ngx_http_close_connection(c);
            return;
        }
    }

#endif

    b = c->buffer;
    size = b->end - b->start;

    if (b->pos == NULL) {

        /*
         * The c->buffer's memory was freed by ngx_http_set_keepalive().
         * However, the c->buffer->start and c->buffer->end were not changed
         * to keep the buffer size.
         */

        b->pos = ngx_palloc(c->pool, size);
        if (b->pos == NULL) {
            ngx_http_close_connection(c);
            return;
        }

        b->start = b->pos;
        b->last = b->pos;
        b->end = b->pos + size;
    }

    /*
     * MSIE closes a keepalive connection with RST flag
     * so we ignore ECONNRESET here.
     */

    c->log_error = NGX_ERROR_IGNORE_ECONNRESET;
    ngx_set_socket_errno(0);

    n = c->recv(c, b->last, size);
    c->log_error = NGX_ERROR_INFO;

    if (n == NGX_AGAIN) {
        if (ngx_handle_read_event(rev, 0) != NGX_OK) {
            ngx_http_close_connection(c);
            return;
        }

        /*
         * Like ngx_http_set_keepalive() we are trying to not hold
         * c->buffer's memory for a keepalive connection.
         */

#if (NGX_HTTP_SSL && NGX_SSL_ASYNC)
        /* For the Asynch implementation we need the same buffer to be used
         * on subsequent read requests. As such we need to turn off this optimisation that
         * frees the buffer between invocations as may end up with a buffer that is at a
         * different address */
        if ((c->async_enable && !ngx_ssl_waiting_for_async(c)) || !c->async_enable)
        {
#endif
        if (ngx_pfree(c->pool, b->start) == NGX_OK) {

            /*
             * the special note that c->buffer's memory was freed
             */

            b->pos = NULL;
        }
#if (NGX_HTTP_SSL && NGX_SSL_ASYNC)
        }
#endif

        return;
    }

    if (n == NGX_ERROR) {
        ngx_http_close_connection(c);
        return;
    }

    c->log->handler = NULL;

    if (n == 0) {
        ngx_log_error(NGX_LOG_INFO, c->log, ngx_socket_errno,
                      "client %V closed keepalive connection", &c->addr_text);
        ngx_http_close_connection(c);
        return;
    }

    b->last += n;

    c->log->handler = ngx_http_log_error;
    c->log->action = "reading client request line";

    c->idle = 0;
    ngx_reusable_connection(c, 0);

    c->data = ngx_http_create_request(c);
    if (c->data == NULL) {
        ngx_http_close_connection(c);
        return;
    }

    c->sent = 0;
    c->destroyed = 0;
#if (T_NGX_REQ_STATUS)
    c->received = n;
#endif

    ngx_del_timer(rev);

    rev->handler = ngx_http_process_request_line;
    ngx_http_process_request_line(rev);
}