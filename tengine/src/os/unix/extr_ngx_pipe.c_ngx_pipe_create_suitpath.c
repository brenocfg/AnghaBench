#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  realpath ;
struct TYPE_6__ {int /*<<< orphan*/  time_now; int /*<<< orphan*/  last_suit_time; int /*<<< orphan*/  logname; int /*<<< orphan*/  suitpath; } ;
typedef  TYPE_1__ ngx_pipe_rollback_conf_t ;
struct TYPE_7__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_2__ ngx_cycle_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_errno ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ngx_pipe_create_subdirs (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_time () ; 
 scalar_t__ strftime (char*,int,int /*<<< orphan*/ ,struct tm*) ; 
 int symlink (int /*<<< orphan*/ ,char*) ; 
 int unlink (char*) ; 

__attribute__((used)) static void
ngx_pipe_create_suitpath(ngx_cycle_t *cycle, ngx_pipe_rollback_conf_t *rbcf)
{
    char        realpath[256];
    struct      tm *tm_now;
    int         result;
    time_t      t = ngx_time();

    tm_now = localtime(&t);
    if (tm_now == NULL) {
        ngx_log_error(NGX_LOG_EMERG, cycle->log, 0,
                      "get now time failed");
        return;
    }
    if (0 >= strftime(realpath, sizeof(realpath), rbcf->suitpath, tm_now)) {
        ngx_log_error(NGX_LOG_EMERG, cycle->log, 0,
                      "parse suitpath with time now failed");
        return;
    }

    ngx_pipe_create_subdirs(realpath, cycle);

    result = unlink(realpath);
    if (0 == result) {
        ngx_log_error(NGX_LOG_INFO, cycle->log, 0,
                      "unlink [%s] success", realpath);
    } else {
        ngx_log_error(NGX_LOG_EMERG, cycle->log, ngx_errno,
                      "unlink [%s] failed", realpath);
    }

    result = symlink(rbcf->logname, realpath);
    if (0 == result) {
        ngx_log_error(NGX_LOG_INFO, cycle->log, 0,
                      "symlink [%s] success", realpath);
    } else {
        ngx_log_error(NGX_LOG_EMERG, cycle->log, ngx_errno,
                      "symlink [%s] failed", realpath);
    }

    rbcf->last_suit_time = rbcf->time_now;
}