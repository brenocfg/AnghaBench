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
struct TYPE_9__ {TYPE_6__* read; TYPE_1__* ssl; TYPE_5__* write; int /*<<< orphan*/  log; int /*<<< orphan*/  send_chain; int /*<<< orphan*/  recv_chain; int /*<<< orphan*/  send; int /*<<< orphan*/  recv; } ;
typedef  TYPE_2__ ngx_connection_t ;
struct TYPE_11__ {int eof; int error; void* handler; scalar_t__ ready; } ;
struct TYPE_10__ {void* handler; scalar_t__ ready; } ;
struct TYPE_8__ {int handshaked; int no_wait_shutdown; int no_send_shutdown; int /*<<< orphan*/  connection; } ;

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
 int SSL_do_handshake (int /*<<< orphan*/ ) ; 
 int SSL_get_error (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_connection_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_errno ; 
 scalar_t__ ngx_handle_read_event (TYPE_6__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_handle_write_event (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ngx_ssl_clear_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_ssl_connection_error (TYPE_2__*,int,int /*<<< orphan*/ ,char*) ; 
 void* ngx_ssl_handshake_handler ; 
 int /*<<< orphan*/  ngx_ssl_recv ; 
 int /*<<< orphan*/  ngx_ssl_recv_chain ; 
 int /*<<< orphan*/  ngx_ssl_send_chain ; 
 int /*<<< orphan*/  ngx_ssl_write ; 

ngx_int_t
ngx_ssl_handshake(ngx_connection_t *c)
{
    int        n, sslerr;
    ngx_err_t  err;

#ifdef SSL_READ_EARLY_DATA_SUCCESS
    if (c->ssl->try_early_data) {
        return ngx_ssl_try_early_data(c);
    }
#endif

    ngx_ssl_clear_error(c->log);

    n = SSL_do_handshake(c->ssl->connection);

    ngx_log_debug1(NGX_LOG_DEBUG_EVENT, c->log, 0, "SSL_do_handshake: %d", n);

    if (n == 1) {

#if (NGX_SSL && NGX_SSL_ASYNC)
        if (c->async_enable && ngx_ssl_async_process_fds(c) == NGX_ERROR) {
            return NGX_ERROR;
        }
#endif

        if (ngx_handle_read_event(c->read, 0) != NGX_OK) {
            return NGX_ERROR;
        }

        if (ngx_handle_write_event(c->write, 0) != NGX_OK) {
            return NGX_ERROR;
        }

#if (NGX_DEBUG)
        ngx_ssl_handshake_log(c);
#endif

        c->ssl->handshaked = 1;

#if (T_NGX_SSL_HANDSHAKE_TIME)
        ngx_time_t *tp;
        tp = ngx_timeofday();
        c->ssl->handshake_end_msec = tp->sec * 1000 + tp->msec;
#endif

        c->recv = ngx_ssl_recv;
        c->send = ngx_ssl_write;
        c->recv_chain = ngx_ssl_recv_chain;
        c->send_chain = ngx_ssl_send_chain;

#ifndef SSL_OP_NO_RENEGOTIATION
#if OPENSSL_VERSION_NUMBER < 0x10100000L
#ifdef SSL3_FLAGS_NO_RENEGOTIATE_CIPHERS

        /* initial handshake done, disable renegotiation (CVE-2009-3555) */
        if (c->ssl->connection->s3 && SSL_is_server(c->ssl->connection)) {
            c->ssl->connection->s3->flags |= SSL3_FLAGS_NO_RENEGOTIATE_CIPHERS;
        }

#endif
#endif
#endif

        return NGX_OK;
    }

    sslerr = SSL_get_error(c->ssl->connection, n);

    ngx_log_debug1(NGX_LOG_DEBUG_EVENT, c->log, 0, "SSL_get_error: %d", sslerr);

    if (sslerr == SSL_ERROR_WANT_READ) {

#if (NGX_SSL && NGX_SSL_ASYNC)
        if (c->async_enable && ngx_ssl_async_process_fds(c) == NGX_ERROR) {
            return NGX_ERROR;
        }
#endif

        c->read->ready = 0;
        c->read->handler = ngx_ssl_handshake_handler;
        c->write->handler = ngx_ssl_handshake_handler;

        if (ngx_handle_read_event(c->read, 0) != NGX_OK) {
            return NGX_ERROR;
        }

        if (ngx_handle_write_event(c->write, 0) != NGX_OK) {
            return NGX_ERROR;
        }

        return NGX_AGAIN;
    }

    if (sslerr == SSL_ERROR_WANT_WRITE) {

#if (NGX_SSL && NGX_SSL_ASYNC)
        if (c->async_enable && ngx_ssl_async_process_fds(c) == NGX_ERROR) {
            return NGX_ERROR;
        }
#endif

        c->write->ready = 0;
        c->read->handler = ngx_ssl_handshake_handler;
        c->write->handler = ngx_ssl_handshake_handler;

        if (ngx_handle_read_event(c->read, 0) != NGX_OK) {
            return NGX_ERROR;
        }

        if (ngx_handle_write_event(c->write, 0) != NGX_OK) {
            return NGX_ERROR;
        }

        return NGX_AGAIN;
    }

#if (NGX_SSL && NGX_SSL_ASYNC)
    if (c->async_enable && sslerr == SSL_ERROR_WANT_ASYNC)
    {
        c->async->handler = ngx_ssl_handshake_async_handler;
        c->read->saved_handler = c->read->handler;
        c->read->handler = ngx_ssl_empty_handler;

        ngx_log_debug1(NGX_LOG_DEBUG_EVENT, c->log, 0,
                       "SSL ASYNC WANT recieved: \"%s\"", __func__);

        if (ngx_ssl_async_process_fds(c) == NGX_ERROR) {
            return NGX_ERROR;
        }

        return NGX_AGAIN;
    }
#endif

    err = (sslerr == SSL_ERROR_SYSCALL) ? ngx_errno : 0;

    c->ssl->no_wait_shutdown = 1;
    c->ssl->no_send_shutdown = 1;
    c->read->eof = 1;

    if (sslerr == SSL_ERROR_ZERO_RETURN || ERR_peek_error() == 0) {
        ngx_connection_error(c, err,
                             "peer closed connection in SSL handshake");

        return NGX_ERROR;
    }

    c->read->error = 1;

    ngx_ssl_connection_error(c, sslerr, err, "SSL_do_handshake() failed");

    return NGX_ERROR;
}