#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_uint_t ;
typedef  scalar_t__ ngx_socket_t ;
typedef  int ngx_int_t ;
struct TYPE_16__ {scalar_t__ timer_set; int /*<<< orphan*/  ready; scalar_t__ active; int /*<<< orphan*/  delayed; scalar_t__ error; scalar_t__ eof; } ;
typedef  TYPE_4__ ngx_event_t ;
struct TYPE_17__ {scalar_t__ output_ctx; int /*<<< orphan*/  send_timeout; int /*<<< orphan*/  send_lowat; TYPE_3__* downstream; int /*<<< orphan*/  read_timeout; TYPE_2__* upstream; scalar_t__ upstream_blocked; scalar_t__ read; TYPE_1__* log; } ;
typedef  TYPE_5__ ngx_event_pipe_t ;
struct TYPE_15__ {scalar_t__ fd; scalar_t__ data; TYPE_4__* write; } ;
struct TYPE_14__ {scalar_t__ fd; TYPE_4__* read; } ;
struct TYPE_13__ {char* action; } ;

/* Variables and functions */
 int NGX_ABORT ; 
 int NGX_BUSY ; 
 int /*<<< orphan*/  NGX_CLOSE_EVENT ; 
 int NGX_OK ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_del_timer (TYPE_4__*) ; 
 int ngx_event_pipe_read_upstream (TYPE_5__*) ; 
 int ngx_event_pipe_write_to_downstream (TYPE_5__*) ; 
 int ngx_handle_read_event (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int ngx_handle_write_event (TYPE_4__*,int /*<<< orphan*/ ) ; 

ngx_int_t
ngx_event_pipe(ngx_event_pipe_t *p, ngx_int_t do_write)
{
    ngx_int_t     rc;
    ngx_uint_t    flags;
    ngx_event_t  *rev, *wev;

    for ( ;; ) {
        if (do_write) {
            p->log->action = "sending to client";

            rc = ngx_event_pipe_write_to_downstream(p);

            if (rc == NGX_ABORT) {
                return NGX_ABORT;
            }

            if (rc == NGX_BUSY) {
                return NGX_OK;
            }
        }

        p->read = 0;
        p->upstream_blocked = 0;

        p->log->action = "reading upstream";

        if (ngx_event_pipe_read_upstream(p) == NGX_ABORT) {
            return NGX_ABORT;
        }

        if (!p->read && !p->upstream_blocked) {
            break;
        }

        do_write = 1;
    }

    if (p->upstream->fd != (ngx_socket_t) -1) {
        rev = p->upstream->read;

        flags = (rev->eof || rev->error) ? NGX_CLOSE_EVENT : 0;

        if (ngx_handle_read_event(rev, flags) != NGX_OK) {
            return NGX_ABORT;
        }

        if (!rev->delayed) {
            if (rev->active && !rev->ready) {
                ngx_add_timer(rev, p->read_timeout);

            } else if (rev->timer_set) {
                ngx_del_timer(rev);
            }
        }
    }

    if (p->downstream->fd != (ngx_socket_t) -1
        && p->downstream->data == p->output_ctx)
    {
        wev = p->downstream->write;
        if (ngx_handle_write_event(wev, p->send_lowat) != NGX_OK) {
            return NGX_ABORT;
        }

        if (!wev->delayed) {
            if (wev->active && !wev->ready) {
                ngx_add_timer(wev, p->send_timeout);

            } else if (wev->timer_set) {
                ngx_del_timer(wev);
            }
        }
    }

    return NGX_OK;
}