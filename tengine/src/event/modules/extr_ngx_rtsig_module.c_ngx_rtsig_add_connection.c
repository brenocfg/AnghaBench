#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_10__ {scalar_t__ signo; } ;
typedef  TYPE_3__ ngx_rtsig_conf_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_11__ {TYPE_2__* write; TYPE_1__* read; int /*<<< orphan*/  log; int /*<<< orphan*/  fd; } ;
typedef  TYPE_4__ ngx_connection_t ;
struct TYPE_12__ {int /*<<< orphan*/  conf_ctx; } ;
struct TYPE_9__ {int active; } ;
struct TYPE_8__ {int active; scalar_t__ instance; scalar_t__ disabled; scalar_t__ accept; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_SETAUXFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  F_SETOWN ; 
 int /*<<< orphan*/  F_SETSIG ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 int /*<<< orphan*/  NGX_OK ; 
 int O_ASYNC ; 
 int O_NONBLOCK ; 
 int O_ONESIGFD ; 
 int O_RDWR ; 
 int fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_7__* ngx_cycle ; 
 int /*<<< orphan*/  ngx_errno ; 
 TYPE_3__* ngx_event_get_conf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int ngx_pid ; 
 int /*<<< orphan*/  ngx_rtsig_module ; 

__attribute__((used)) static ngx_int_t
ngx_rtsig_add_connection(ngx_connection_t *c)
{
    ngx_uint_t         signo;
    ngx_rtsig_conf_t  *rtscf;

    if (c->read->accept && c->read->disabled) {

        ngx_log_debug1(NGX_LOG_DEBUG_EVENT, c->log, 0,
                       "rtsig enable connection: fd:%d", c->fd);

        if (fcntl(c->fd, F_SETOWN, ngx_pid) == -1) {
            ngx_log_error(NGX_LOG_ALERT, c->log, ngx_errno,
                          "fcntl(F_SETOWN) failed");
            return NGX_ERROR;
        }

        c->read->active = 1;
        c->read->disabled = 0;
    }

    rtscf = ngx_event_get_conf(ngx_cycle->conf_ctx, ngx_rtsig_module);

    signo = rtscf->signo + c->read->instance;

    ngx_log_debug2(NGX_LOG_DEBUG_EVENT, c->log, 0,
                   "rtsig add connection: fd:%d signo:%ui", c->fd, signo);

    if (fcntl(c->fd, F_SETFL, O_RDWR|O_NONBLOCK|O_ASYNC) == -1) {
        ngx_log_error(NGX_LOG_ALERT, c->log, ngx_errno,
                      "fcntl(O_RDWR|O_NONBLOCK|O_ASYNC) failed");
        return NGX_ERROR;
    }

    if (fcntl(c->fd, F_SETSIG, (int) signo) == -1) {
        ngx_log_error(NGX_LOG_ALERT, c->log, ngx_errno,
                      "fcntl(F_SETSIG) failed");
        return NGX_ERROR;
    }

    if (fcntl(c->fd, F_SETOWN, ngx_pid) == -1) {
        ngx_log_error(NGX_LOG_ALERT, c->log, ngx_errno,
                      "fcntl(F_SETOWN) failed");
        return NGX_ERROR;
    }

#if (NGX_HAVE_ONESIGFD)
    if (fcntl(c->fd, F_SETAUXFL, O_ONESIGFD) == -1) {
        ngx_log_error(NGX_LOG_ALERT, c->log, ngx_errno,
                      "fcntl(F_SETAUXFL) failed");
        return NGX_ERROR;
    }
#endif

    c->read->active = 1;
    c->write->active = 1;

    return NGX_OK;
}