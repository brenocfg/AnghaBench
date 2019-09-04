#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct signal {scalar_t__ signo; int /*<<< orphan*/  signame; int /*<<< orphan*/  flags; int /*<<< orphan*/  handler; } ;
struct sigaction {int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_flags; int /*<<< orphan*/  sa_handler; } ;
typedef  int /*<<< orphan*/  sa ;
typedef  scalar_t__ rstatus_t ;

/* Variables and functions */
 scalar_t__ NC_ERROR ; 
 scalar_t__ NC_OK ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  log_error (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sigaction*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sigaction (scalar_t__,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 struct signal* signals ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

rstatus_t
signal_init(void)
{
    struct signal *sig;

    for (sig = signals; sig->signo != 0; sig++) {
        rstatus_t status;
        struct sigaction sa;

        memset(&sa, 0, sizeof(sa));
        sa.sa_handler = sig->handler;
        sa.sa_flags = sig->flags;
        sigemptyset(&sa.sa_mask);

        status = sigaction(sig->signo, &sa, NULL);
        if (status < 0) {
            log_error("sigaction(%s) failed: %s", sig->signame,
                      strerror(errno));
            return NC_ERROR;
        }
    }

    return NC_OK;
}