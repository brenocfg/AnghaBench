#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_err_t ;
struct TYPE_9__ {TYPE_1__* ssl; TYPE_6__* read; TYPE_5__* write; int /*<<< orphan*/  log; scalar_t__ timedout; } ;
typedef  TYPE_2__ ngx_connection_t ;
struct TYPE_11__ {void* handler; } ;
struct TYPE_10__ {void* handler; } ;
struct TYPE_8__ {int /*<<< orphan*/  connection; scalar_t__ no_send_shutdown; scalar_t__ no_wait_shutdown; } ;

/* Variables and functions */
 scalar_t__ ERR_peek_error () ; 
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 scalar_t__ NGX_OK ; 
 int SSL_ERROR_SYSCALL ; 
 int SSL_ERROR_WANT_READ ; 
 int SSL_ERROR_WANT_WRITE ; 
 int SSL_ERROR_ZERO_RETURN ; 
 int SSL_RECEIVED_SHUTDOWN ; 
 int SSL_SENT_SHUTDOWN ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ ) ; 
 int SSL_get_error (int /*<<< orphan*/ ,int) ; 
 int SSL_get_shutdown (int /*<<< orphan*/ ) ; 
 scalar_t__ SSL_in_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_quiet_shutdown (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SSL_set_shutdown (int /*<<< orphan*/ ,int) ; 
 int SSL_shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_6__*,int) ; 
 int /*<<< orphan*/  ngx_errno ; 
 scalar_t__ ngx_handle_read_event (TYPE_6__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_handle_write_event (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ngx_ssl_clear_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_ssl_connection_error (TYPE_2__*,int,int /*<<< orphan*/ ,char*) ; 
 void* ngx_ssl_shutdown_handler ; 

ngx_int_t
ngx_ssl_shutdown(ngx_connection_t *c)
{
    int        n, sslerr, mode;
    ngx_err_t  err;

    if (SSL_in_init(c->ssl->connection)) {
        /*
         * OpenSSL 1.0.2f complains if SSL_shutdown() is called during
         * an SSL handshake, while previous versions always return 0.
         * Avoid calling SSL_shutdown() if handshake wasn't completed.
         */

#if (NGX_SSL && NGX_SSL_ASYNC)
        if (c->async_enable) {
            /* Check if there is inflight request */
            if (SSL_want_async(c->ssl->connection) && !c->timedout) {
                c->async->handler = ngx_ssl_shutdown_async_handler;
                ngx_ssl_async_process_fds(c);
                ngx_add_timer(c->async, 300);
                return NGX_AGAIN;
            }

            /* Ignore errors from ngx_ssl_async_process_fds as
               we want to carry on and close the SSL connection
               anyway. */
            ngx_ssl_async_process_fds(c);
            if (ngx_del_async_conn) {
                if (c->num_async_fds) {
                    ngx_del_async_conn(c, NGX_DISABLE_EVENT);
                    c->num_async_fds--;
                }
            }
            ngx_del_conn(c, NGX_DISABLE_EVENT);
        }
#endif

        SSL_free(c->ssl->connection);
        c->ssl = NULL;

        return NGX_OK;
    }

    if (c->timedout) {
        mode = SSL_RECEIVED_SHUTDOWN|SSL_SENT_SHUTDOWN;
        SSL_set_quiet_shutdown(c->ssl->connection, 1);

    } else {
        mode = SSL_get_shutdown(c->ssl->connection);

        if (c->ssl->no_wait_shutdown) {
            mode |= SSL_RECEIVED_SHUTDOWN;
        }

        if (c->ssl->no_send_shutdown) {
            mode |= SSL_SENT_SHUTDOWN;
        }

        if (c->ssl->no_wait_shutdown && c->ssl->no_send_shutdown) {
            SSL_set_quiet_shutdown(c->ssl->connection, 1);
        }
    }

    SSL_set_shutdown(c->ssl->connection, mode);

    ngx_ssl_clear_error(c->log);

    n = SSL_shutdown(c->ssl->connection);

    ngx_log_debug1(NGX_LOG_DEBUG_EVENT, c->log, 0, "SSL_shutdown: %d", n);

    sslerr = 0;

    /* before 0.9.8m SSL_shutdown() returned 0 instead of -1 on errors */

    if (n != 1 && ERR_peek_error()) {
#if (NGX_SSL && NGX_SSL_ASYNC)
        if (c->async_enable && ngx_ssl_async_process_fds(c) == NGX_ERROR) {
            return NGX_ERROR;
        }
#endif
        sslerr = SSL_get_error(c->ssl->connection, n);

        ngx_log_debug1(NGX_LOG_DEBUG_EVENT, c->log, 0,
                       "SSL_get_error: %d", sslerr);
    }

#if (NGX_SSL && NGX_SSL_ASYNC)
    else if (c->async_enable && n == -1) {
        sslerr = SSL_get_error(c->ssl->connection, n);
        ngx_log_debug1(NGX_LOG_DEBUG_EVENT, c->log, 0,
                       "SSL_get_error async: %d", sslerr);
    }
#endif
    if (n == 1 || sslerr == 0 || sslerr == SSL_ERROR_ZERO_RETURN) {
#if (NGX_SSL && NGX_SSL_ASYNC)
         if (c->async_enable) {
            /* Ignore errors from ngx_ssl_async_process_fds as
               we want to carry on and close the SSL connection
               anyway. */
            ngx_ssl_async_process_fds(c);
            if (ngx_del_async_conn) {
                if (c->num_async_fds) {
                    ngx_del_async_conn(c, NGX_DISABLE_EVENT);
                    c->num_async_fds--;
                }
            }
            ngx_del_conn(c, NGX_DISABLE_EVENT);
        }
#endif
        SSL_free(c->ssl->connection);
        c->ssl = NULL;

        return NGX_OK;
    }

    if (sslerr == SSL_ERROR_WANT_READ || sslerr == SSL_ERROR_WANT_WRITE) {
#if (NGX_SSL && NGX_SSL_ASYNC)
        if (c->async_enable && ngx_ssl_async_process_fds(c) == NGX_ERROR) {
            return NGX_ERROR;
        }
#endif
        c->read->handler = ngx_ssl_shutdown_handler;
        c->write->handler = ngx_ssl_shutdown_handler;

        if (ngx_handle_read_event(c->read, 0) != NGX_OK) {
            return NGX_ERROR;
        }

        if (ngx_handle_write_event(c->write, 0) != NGX_OK) {
            return NGX_ERROR;
        }

        if (sslerr == SSL_ERROR_WANT_READ) {
            ngx_add_timer(c->read, 30000);
        }

        return NGX_AGAIN;
    }

#if (NGX_SSL && NGX_SSL_ASYNC)
    if (c->async_enable) {
        if (sslerr == SSL_ERROR_WANT_ASYNC) {
            c->async->handler = ngx_ssl_shutdown_async_handler;
            c->read->saved_handler = ngx_ssl_shutdown_handler;
            c->read->handler = ngx_ssl_empty_handler;
            c->write->handler = ngx_ssl_shutdown_handler;

            ngx_log_debug1(NGX_LOG_DEBUG_EVENT, c->log, 0,
                           "SSL ASYNC WANT recieved: \"%s\"", __func__);

            /* Ignore errors from ngx_ssl_async_process_fds as
               we want to carry on anyway */
            ngx_ssl_async_process_fds(c);
            return NGX_AGAIN;
        }

        /* Ignore errors from ngx_ssl_async_process_fds as
           we want to carry on and close the SSL connection
           anyway. */
        ngx_ssl_async_process_fds(c);
        if (ngx_del_async_conn) {
            if (c->num_async_fds) {
                ngx_del_async_conn(c, NGX_DISABLE_EVENT);
                c->num_async_fds--;
            }
        }
        ngx_del_conn(c, NGX_DISABLE_EVENT);
    }
#endif
    err = (sslerr == SSL_ERROR_SYSCALL) ? ngx_errno : 0;

    ngx_ssl_connection_error(c, sslerr, err, "SSL_shutdown() failed");

    SSL_free(c->ssl->connection);
    c->ssl = NULL;

    return NGX_ERROR;
}