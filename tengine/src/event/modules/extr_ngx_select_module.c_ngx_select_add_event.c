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
struct TYPE_5__ {size_t index; int active; scalar_t__ write; int /*<<< orphan*/  log; TYPE_2__* data; } ;
typedef  TYPE_1__ ngx_event_t ;
struct TYPE_6__ {int fd; } ;
typedef  TYPE_2__ ngx_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 size_t NGX_INVALID_INDEX ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  NGX_READ_EVENT ; 
 int /*<<< orphan*/  NGX_WRITE_EVENT ; 
 TYPE_1__** event_index ; 
 int /*<<< orphan*/  master_read_fd_set ; 
 int /*<<< orphan*/  master_write_fd_set ; 
 int max_fd ; 
 size_t nevents ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static ngx_int_t
ngx_select_add_event(ngx_event_t *ev, ngx_int_t event, ngx_uint_t flags)
{
    ngx_connection_t  *c;

    c = ev->data;

    ngx_log_debug2(NGX_LOG_DEBUG_EVENT, ev->log, 0,
                   "select add event fd:%d ev:%i", c->fd, event);

    if (ev->index != NGX_INVALID_INDEX) {
        ngx_log_error(NGX_LOG_ALERT, ev->log, 0,
                      "select event fd:%d ev:%i is already set", c->fd, event);
        return NGX_OK;
    }

    if ((event == NGX_READ_EVENT && ev->write)
        || (event == NGX_WRITE_EVENT && !ev->write))
    {
        ngx_log_error(NGX_LOG_ALERT, ev->log, 0,
                      "invalid select %s event fd:%d ev:%i",
                      ev->write ? "write" : "read", c->fd, event);
        return NGX_ERROR;
    }

    if (event == NGX_READ_EVENT) {
        FD_SET(c->fd, &master_read_fd_set);

    } else if (event == NGX_WRITE_EVENT) {
        FD_SET(c->fd, &master_write_fd_set);
    }

    if (max_fd != -1 && max_fd < c->fd) {
        max_fd = c->fd;
    }

    ev->active = 1;

    event_index[nevents] = ev;
    ev->index = nevents;
    nevents++;

    return NGX_OK;
}