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
typedef  int /*<<< orphan*/  ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_5__ {size_t index; int /*<<< orphan*/  log; scalar_t__ active; TYPE_2__* data; } ;
typedef  TYPE_1__ ngx_event_t ;
struct TYPE_6__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_2__ ngx_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  FD_CLR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t NGX_INVALID_INDEX ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  NGX_READ_EVENT ; 
 int /*<<< orphan*/  NGX_WRITE_EVENT ; 
 TYPE_1__** event_index ; 
 int /*<<< orphan*/  master_read_fd_set ; 
 int /*<<< orphan*/  master_write_fd_set ; 
 int /*<<< orphan*/  max_read ; 
 int /*<<< orphan*/  max_write ; 
 size_t nevents ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_select_del_event(ngx_event_t *ev, ngx_int_t event, ngx_uint_t flags)
{
    ngx_event_t       *e;
    ngx_connection_t  *c;

    c = ev->data;

    ev->active = 0;

    if (ev->index == NGX_INVALID_INDEX) {
        return NGX_OK;
    }

    ngx_log_debug2(NGX_LOG_DEBUG_EVENT, ev->log, 0,
                   "select del event fd:%d ev:%i", c->fd, event);

    if (event == NGX_READ_EVENT) {
        FD_CLR(c->fd, &master_read_fd_set);
        max_read--;

    } else if (event == NGX_WRITE_EVENT) {
        FD_CLR(c->fd, &master_write_fd_set);
        max_write--;
    }

    if (ev->index < --nevents) {
        e = event_index[nevents];
        event_index[ev->index] = e;
        e->index = ev->index;
    }

    ev->index = NGX_INVALID_INDEX;

    return NGX_OK;
}