#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_10__ {int /*<<< orphan*/  log; TYPE_2__* read; } ;
typedef  TYPE_3__ ngx_connection_t ;
struct TYPE_11__ {struct TYPE_11__* next; TYPE_1__* buf; } ;
typedef  TYPE_4__ ngx_chain_t ;
struct TYPE_9__ {int pending_eof; int ready; scalar_t__ eof; } ;
struct TYPE_8__ {int /*<<< orphan*/ * end; int /*<<< orphan*/ * last; } ;

/* Variables and functions */
 int NGX_AGAIN ; 
 int NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 int ngx_aio_read (TYPE_3__*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

ssize_t
ngx_aio_read_chain(ngx_connection_t *c, ngx_chain_t *cl, off_t limit)
{
    int           n;
    u_char       *buf, *prev;
    size_t        size;
    ssize_t       total;

    if (c->read->pending_eof) {
        c->read->ready = 0;
        return 0;
    }

    total = 0;

    while (cl) {

        /* we can post the single aio operation only */

        if (!c->read->ready) {
            return total ? total : NGX_AGAIN;
        }

        buf = cl->buf->last;
        prev = cl->buf->last;
        size = 0;

        /* coalesce the neighbouring bufs */

        while (cl && prev == cl->buf->last) {
            size += cl->buf->end - cl->buf->last;
            prev = cl->buf->end;
            cl = cl->next;
        }

        n = ngx_aio_read(c, buf, size);

        ngx_log_debug1(NGX_LOG_DEBUG_EVENT, c->log, 0, "aio_read: %d", n);

        if (n == NGX_AGAIN) {
            return total ? total : NGX_AGAIN;
        }

        if (n == NGX_ERROR) {
            return NGX_ERROR;
        }

        if (n == 0) {
            c->read->pending_eof = 1;
            if (total) {
                c->read->eof = 0;
                c->read->ready = 1;
            }
            return total;
        }

        if (n > 0) {
            total += n;
        }

        ngx_log_debug1(NGX_LOG_DEBUG_EVENT, c->log, 0,
                       "aio_read total: %d", total);
    }

    return total ? total : NGX_AGAIN;
}