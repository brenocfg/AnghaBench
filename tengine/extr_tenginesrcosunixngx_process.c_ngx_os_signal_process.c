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
struct TYPE_5__ {scalar_t__ signo; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ ngx_signal_t ;
typedef  int /*<<< orphan*/  ngx_pid_t ;
typedef  int ngx_int_t ;
struct TYPE_6__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_2__ ngx_cycle_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int kill (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ngx_errno ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ngx_strcmp (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* signals ; 

ngx_int_t
ngx_os_signal_process(ngx_cycle_t *cycle, char *name, ngx_pid_t pid)
{
    ngx_signal_t  *sig;

    for (sig = signals; sig->signo != 0; sig++) {
        if (ngx_strcmp(name, sig->name) == 0) {
            if (kill(pid, sig->signo) != -1) {
                return 0;
            }

            ngx_log_error(NGX_LOG_ALERT, cycle->log, ngx_errno,
                          "kill(%P, %d) failed", pid, sig->signo);
        }
    }

    return 1;
}