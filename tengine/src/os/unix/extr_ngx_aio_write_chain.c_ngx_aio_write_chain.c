#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ off_t ;
struct TYPE_11__ {scalar_t__ sent; int /*<<< orphan*/  log; TYPE_1__* write; } ;
typedef  TYPE_2__ ngx_connection_t ;
struct TYPE_12__ {TYPE_4__* buf; struct TYPE_12__* next; } ;
typedef  TYPE_3__ ngx_chain_t ;
struct TYPE_13__ {int /*<<< orphan*/ * pos; int /*<<< orphan*/ * last; } ;
struct TYPE_10__ {int /*<<< orphan*/  ready; } ;

/* Variables and functions */
 TYPE_3__* NGX_CHAIN_ERROR ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 scalar_t__ NGX_MAX_SIZE_T_VALUE ; 
 scalar_t__ ngx_aio_write (TYPE_2__*,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ ngx_buf_special (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ ngx_pagesize ; 

ngx_chain_t *
ngx_aio_write_chain(ngx_connection_t *c, ngx_chain_t *in, off_t limit)
{
    u_char       *buf, *prev;
    off_t         send, sent;
    size_t        len;
    ssize_t       n, size;
    ngx_chain_t  *cl;

    /* the maximum limit size is the maximum size_t value - the page size */

    if (limit == 0 || limit > (off_t) (NGX_MAX_SIZE_T_VALUE - ngx_pagesize)) {
        limit = NGX_MAX_SIZE_T_VALUE - ngx_pagesize;
    }

    send = 0;
    sent = 0;
    cl = in;

    while (cl) {

        if (cl->buf->pos == cl->buf->last) {
            cl = cl->next;
            continue;
        }

        /* we can post the single aio operation only */

        if (!c->write->ready) {
            return cl;
        }

        buf = cl->buf->pos;
        prev = buf;
        len = 0;

        /* coalesce the neighbouring bufs */

        while (cl && prev == cl->buf->pos && send < limit) {
            if (ngx_buf_special(cl->buf)) {
                continue;
            }

            size = cl->buf->last - cl->buf->pos;

            if (send + size > limit) {
                size = limit - send;
            }

            len += size;
            prev = cl->buf->pos + size;
            send += size;
            cl = cl->next;
        }

        n = ngx_aio_write(c, buf, len);

        ngx_log_debug1(NGX_LOG_DEBUG_EVENT, c->log, 0, "aio_write: %z", n);

        if (n == NGX_ERROR) {
            return NGX_CHAIN_ERROR;
        }

        if (n > 0) {
            sent += n;
            c->sent += n;
        }

        ngx_log_debug1(NGX_LOG_DEBUG_EVENT, c->log, 0,
                       "aio_write sent: %O", c->sent);

        for (cl = in; cl; cl = cl->next) {

            if (sent >= cl->buf->last - cl->buf->pos) {
                sent -= cl->buf->last - cl->buf->pos;
                cl->buf->pos = cl->buf->last;

                continue;
            }

            cl->buf->pos += sent;

            break;
        }
    }

    return cl;
}