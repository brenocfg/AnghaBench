#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pollfd {int dummy; } ;
struct TYPE_6__ {int overflow_events; scalar_t__ signo; } ;
typedef  TYPE_1__ ngx_rtsig_conf_t ;
typedef  int /*<<< orphan*/  ngx_msec_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_7__ {int /*<<< orphan*/  log; int /*<<< orphan*/  conf_ctx; } ;
typedef  TYPE_2__ ngx_cycle_t ;
struct TYPE_8__ {int /*<<< orphan*/  actions; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  NGX_OK ; 
 int NGX_USE_FD_EVENT ; 
 int NGX_USE_GREEDY_EVENT ; 
 int NGX_USE_RTSIG_EVENT ; 
 int SIGALRM ; 
 int SIGIO ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/ * ngx_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_errno ; 
 int /*<<< orphan*/  ngx_event_actions ; 
 int ngx_event_flags ; 
 TYPE_1__* ngx_event_get_conf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_io ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_os_io ; 
 int /*<<< orphan*/  ngx_rtsig_module ; 
 TYPE_3__ ngx_rtsig_module_ctx ; 
 int /*<<< orphan*/ * overflow_list ; 
 int /*<<< orphan*/  set ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_rtsig_init(ngx_cycle_t *cycle, ngx_msec_t timer)
{
    ngx_rtsig_conf_t  *rtscf;

    rtscf = ngx_event_get_conf(cycle->conf_ctx, ngx_rtsig_module);

    sigemptyset(&set);
    sigaddset(&set, (int) rtscf->signo);
    sigaddset(&set, (int) rtscf->signo + 1);
    sigaddset(&set, SIGIO);
    sigaddset(&set, SIGALRM);

    if (sigprocmask(SIG_BLOCK, &set, NULL) == -1) {
        ngx_log_error(NGX_LOG_EMERG, cycle->log, ngx_errno,
                      "sigprocmask() failed");
        return NGX_ERROR;
    }

    if (overflow_list) {
        ngx_free(overflow_list);
    }

    overflow_list = ngx_alloc(sizeof(struct pollfd) * rtscf->overflow_events,
                              cycle->log);
    if (overflow_list == NULL) {
        return NGX_ERROR;
    }

    ngx_io = ngx_os_io;

    ngx_event_actions = ngx_rtsig_module_ctx.actions;

    ngx_event_flags = NGX_USE_RTSIG_EVENT
                      |NGX_USE_GREEDY_EVENT
                      |NGX_USE_FD_EVENT;

    return NGX_OK;
}