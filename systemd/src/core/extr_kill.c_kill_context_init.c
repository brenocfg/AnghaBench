#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int send_sigkill; int send_sighup; int /*<<< orphan*/  watchdog_signal; int /*<<< orphan*/  final_kill_signal; int /*<<< orphan*/  kill_signal; } ;
typedef  TYPE_1__ KillContext ;

/* Variables and functions */
 int /*<<< orphan*/  SIGABRT ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

void kill_context_init(KillContext *c) {
        assert(c);

        c->kill_signal = SIGTERM;
        /* restart_kill_signal is unset by default and we fall back to kill_signal */
        c->final_kill_signal = SIGKILL;
        c->send_sigkill = true;
        c->send_sighup = false;
        c->watchdog_signal = SIGABRT;
}