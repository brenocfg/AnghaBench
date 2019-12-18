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
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGILL ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGTTIN ; 
 int /*<<< orphan*/  SIGTTOU ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  execvp (char*,char**) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int main(int argc, char *argv[]) {
	// Signals to ignore
	signal(SIGTTOU, SIG_IGN);  // This one should still be in SigIgn (Tini touches it to ignore it, and should restore it)
	signal(SIGSEGV, SIG_IGN);  // This one should still be in SigIgn (Tini shouldn't touch it)
	signal(SIGINT,  SIG_IGN);  // This one should still be in SigIgn (Tini should block it to forward it, and restore it)

	// Signals to block
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGTTIN);  // This one should still be in SigIgn (Tini touches it to ignore it, and should restore it)
	sigaddset(&set, SIGILL);   // This one should still be in SigIgn (Tini shouldn't touch it)
	sigaddset(&set, SIGTERM);  // This one should still be in SigIgn (Tini should block it to forward it, and restore it)
	sigprocmask(SIG_BLOCK, &set, NULL);

	// Run whatever we were asked to run
	execvp(argv[1], argv+1);
}