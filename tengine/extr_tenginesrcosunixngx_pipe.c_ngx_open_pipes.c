#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_11__ {int /*<<< orphan*/  log; int /*<<< orphan*/  conf_ctx; } ;
typedef  TYPE_3__ ngx_cycle_t ;
struct TYPE_12__ {int /*<<< orphan*/  user; } ;
typedef  TYPE_4__ ngx_core_conf_t ;
struct TYPE_9__ {int /*<<< orphan*/ * data; scalar_t__ len; } ;
struct TYPE_13__ {scalar_t__ generation; TYPE_2__* open_fd; int /*<<< orphan*/  cmd; int /*<<< orphan*/ * pfd; int /*<<< orphan*/  user; TYPE_1__ backup; int /*<<< orphan*/  configured; } ;
struct TYPE_10__ {TYPE_1__ name; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  FD_CLOEXEC ; 
 int /*<<< orphan*/  F_SETFD ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_CORE ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 scalar_t__ NGX_OK ; 
 int fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_core_module ; 
 int /*<<< orphan*/  ngx_errno ; 
 scalar_t__ ngx_get_conf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ngx_last_pipe ; 
 int /*<<< orphan*/  ngx_log_debug4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int ngx_nonblocking (int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_open_pipe (TYPE_3__*,TYPE_5__*) ; 
 scalar_t__ ngx_pipe_generation ; 
 TYPE_5__* ngx_pipes ; 

ngx_int_t
ngx_open_pipes(ngx_cycle_t *cycle)
{
    ngx_int_t          stat;
    ngx_uint_t         i;
    ngx_core_conf_t   *ccf;

    ccf = (ngx_core_conf_t *) ngx_get_conf(cycle->conf_ctx, ngx_core_module);

    for (i = 0; i < ngx_last_pipe; i++) {

        if (!ngx_pipes[i].configured) {
            continue;
        }

        if (ngx_pipes[i].generation != ngx_pipe_generation) {
            continue;
        }

        ngx_pipes[i].backup = ngx_pipes[i].open_fd->name;
        ngx_pipes[i].user = ccf->user;

        stat = ngx_open_pipe(cycle, &ngx_pipes[i]);

        ngx_log_debug4(NGX_LOG_DEBUG_CORE, cycle->log, 0,
                       "pipe: %ui(%d, %d) \"%s\"",
                       i, ngx_pipes[i].pfd[0],
                       ngx_pipes[i].pfd[1], ngx_pipes[i].cmd);

        if (stat == NGX_ERROR) {
            ngx_log_error(NGX_LOG_EMERG, cycle->log, ngx_errno,
                          "open pipe \"%s\" failed",
                          ngx_pipes[i].cmd);
            return NGX_ERROR;
        }

        if (fcntl(ngx_pipes[i].open_fd->fd, F_SETFD, FD_CLOEXEC) == -1) {
            ngx_log_error(NGX_LOG_EMERG, cycle->log, ngx_errno,
                          "fcntl(FD_CLOEXEC) \"%s\" failed",
                          ngx_pipes[i].cmd);
            return NGX_ERROR;
        }

        if (ngx_nonblocking(ngx_pipes[i].open_fd->fd) == -1) {
            ngx_log_error(NGX_LOG_EMERG, cycle->log, ngx_errno,
                          "nonblock \"%s\" failed",
                          ngx_pipes[i].cmd);
            return NGX_ERROR;
        }

        ngx_pipes[i].open_fd->name.len = 0;
        ngx_pipes[i].open_fd->name.data = NULL;
    }

    return NGX_OK;
}