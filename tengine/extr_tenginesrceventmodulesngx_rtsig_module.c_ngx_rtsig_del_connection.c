#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_7__ {TYPE_2__* write; TYPE_1__* read; int /*<<< orphan*/  log; int /*<<< orphan*/  fd; } ;
typedef  TYPE_3__ ngx_connection_t ;
struct TYPE_6__ {scalar_t__ active; } ;
struct TYPE_5__ {int disabled; scalar_t__ active; scalar_t__ accept; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_SETFL ; 
 int NGX_CLOSE_EVENT ; 
 int NGX_DISABLE_EVENT ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 int /*<<< orphan*/  NGX_OK ; 
 int O_NONBLOCK ; 
 int O_RDWR ; 
 int fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_errno ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ngx_int_t
ngx_rtsig_del_connection(ngx_connection_t *c, ngx_uint_t flags)
{
    ngx_log_debug1(NGX_LOG_DEBUG_EVENT, c->log, 0,
                   "rtsig del connection: fd:%d", c->fd);

    if ((flags & NGX_DISABLE_EVENT) && c->read->accept) {

        ngx_log_debug1(NGX_LOG_DEBUG_EVENT, c->log, 0,
                       "rtsig disable connection: fd:%d", c->fd);

        c->read->active = 0;
        c->read->disabled = 1;
        return NGX_OK;
    }

    if (flags & NGX_CLOSE_EVENT) {
        c->read->active = 0;
        c->write->active = 0;
        return NGX_OK;
    }

    if (fcntl(c->fd, F_SETFL, O_RDWR|O_NONBLOCK) == -1) {
        ngx_log_error(NGX_LOG_ALERT, c->log, ngx_errno,
                      "fcntl(O_RDWR|O_NONBLOCK) failed");
        return NGX_ERROR;
    }

    c->read->active = 0;
    c->write->active = 0;

    return NGX_OK;
}