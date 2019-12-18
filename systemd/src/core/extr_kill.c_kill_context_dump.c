#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  send_sighup; int /*<<< orphan*/  send_sigkill; int /*<<< orphan*/  final_kill_signal; int /*<<< orphan*/  kill_signal; int /*<<< orphan*/  kill_mode; } ;
typedef  TYPE_1__ KillContext ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*,char*,char const*,char*,char const*,char*,char const*,char*,char const*,char*,char const*,char*) ; 
 char* kill_mode_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restart_kill_signal (TYPE_1__*) ; 
 char* signal_to_string (int /*<<< orphan*/ ) ; 
 char* strempty (char const*) ; 
 char* yes_no (int /*<<< orphan*/ ) ; 

void kill_context_dump(KillContext *c, FILE *f, const char *prefix) {
        assert(c);

        prefix = strempty(prefix);

        fprintf(f,
                "%sKillMode: %s\n"
                "%sKillSignal: SIG%s\n"
                "%sRestartKillSignal: SIG%s\n"
                "%sFinalKillSignal: SIG%s\n"
                "%sSendSIGKILL: %s\n"
                "%sSendSIGHUP: %s\n",
                prefix, kill_mode_to_string(c->kill_mode),
                prefix, signal_to_string(c->kill_signal),
                prefix, signal_to_string(restart_kill_signal(c)),
                prefix, signal_to_string(c->final_kill_signal),
                prefix, yes_no(c->send_sigkill),
                prefix, yes_no(c->send_sighup));
}