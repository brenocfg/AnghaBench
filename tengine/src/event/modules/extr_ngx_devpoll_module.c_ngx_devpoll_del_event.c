#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_5__ {scalar_t__ active; int /*<<< orphan*/  log; TYPE_2__* data; } ;
typedef  TYPE_1__ ngx_event_t ;
struct TYPE_6__ {TYPE_1__* read; TYPE_1__* write; int /*<<< orphan*/  fd; } ;
typedef  TYPE_2__ ngx_connection_t ;

/* Variables and functions */
 int NGX_CLOSE_EVENT ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  NGX_READ_EVENT ; 
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  POLLOUT ; 
 int /*<<< orphan*/  POLLREMOVE ; 
 int /*<<< orphan*/  ngx_devpoll_set_event (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_devpoll_del_event(ngx_event_t *ev, ngx_int_t event, ngx_uint_t flags)
{
    ngx_event_t       *e;
    ngx_connection_t  *c;

    c = ev->data;

#if (NGX_READ_EVENT != POLLIN)
    event = (event == NGX_READ_EVENT) ? POLLIN : POLLOUT;
#endif

    ngx_log_debug2(NGX_LOG_DEBUG_EVENT, ev->log, 0,
                   "devpoll del event: fd:%d ev:%04Xi", c->fd, event);

    if (ngx_devpoll_set_event(ev, POLLREMOVE, flags) == NGX_ERROR) {
        return NGX_ERROR;
    }

    ev->active = 0;

    if (flags & NGX_CLOSE_EVENT) {
        e = (event == POLLIN) ? c->write : c->read;

        if (e) {
            e->active = 0;
        }

        return NGX_OK;
    }

    /* restore the pair event if it exists */

    if (event == POLLIN) {
        e = c->write;
        event = POLLOUT;

    } else {
        e = c->read;
        event = POLLIN;
    }

    if (e && e->active) {
        return ngx_devpoll_set_event(e, event, 0);
    }

    return NGX_OK;
}