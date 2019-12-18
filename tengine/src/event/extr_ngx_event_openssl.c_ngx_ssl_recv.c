#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int ssize_t ;
struct TYPE_9__ {TYPE_2__* ssl; TYPE_1__* read; int /*<<< orphan*/  log; } ;
typedef  TYPE_3__ ngx_connection_t ;
struct TYPE_8__ {int last; int /*<<< orphan*/  connection; scalar_t__ in_early; } ;
struct TYPE_7__ {int error; int ready; int eof; } ;

/* Variables and functions */
#define  NGX_AGAIN 130 
#define  NGX_DONE 129 
#define  NGX_ERROR 128 
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 int NGX_OK ; 
 int SSL_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ngx_ssl_clear_error (int /*<<< orphan*/ ) ; 
 int ngx_ssl_handle_recv (TYPE_3__*,int) ; 
 int ngx_ssl_recv_early (TYPE_3__*,int /*<<< orphan*/ *,size_t) ; 

ssize_t
ngx_ssl_recv(ngx_connection_t *c, u_char *buf, size_t size)
{
    int  n, bytes;

#ifdef SSL_READ_EARLY_DATA_SUCCESS
    if (c->ssl->in_early) {
        return ngx_ssl_recv_early(c, buf, size);
    }
#endif

    if (c->ssl->last == NGX_ERROR) {
        c->read->error = 1;
        return NGX_ERROR;
    }

    if (c->ssl->last == NGX_DONE) {
        c->read->ready = 0;
        c->read->eof = 1;
        return 0;
    }

    bytes = 0;

    ngx_ssl_clear_error(c->log);

    /*
     * SSL_read() may return data in parts, so try to read
     * until SSL_read() would return no data
     */

    for ( ;; ) {

        n = SSL_read(c->ssl->connection, buf, size);

        ngx_log_debug1(NGX_LOG_DEBUG_EVENT, c->log, 0, "SSL_read: %d", n);

        if (n > 0) {
            bytes += n;
        }

        c->ssl->last = ngx_ssl_handle_recv(c, n);

        if (c->ssl->last == NGX_OK) {

            size -= n;

            if (size == 0) {
                c->read->ready = 1;
                return bytes;
            }

            buf += n;

            continue;
        }

        if (bytes) {
            if (c->ssl->last != NGX_AGAIN) {
                c->read->ready = 1;
            }

            return bytes;
        }

        switch (c->ssl->last) {

        case NGX_DONE:
            c->read->ready = 0;
            c->read->eof = 1;
            return 0;

        case NGX_ERROR:
            c->read->error = 1;

            /* fall through */

        case NGX_AGAIN:
            return c->ssl->last;
        }
    }
}