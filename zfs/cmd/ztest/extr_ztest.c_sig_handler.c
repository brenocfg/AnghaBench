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
struct sigaction {scalar_t__ sa_flags; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; } ;

/* Variables and functions */
 int BACKTRACE_SZ ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int backtrace (void**,int) ; 
 int /*<<< orphan*/  backtrace_symbols_fd (void**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_debug_buffer () ; 
 int /*<<< orphan*/  raise (int) ; 
 int /*<<< orphan*/  sigaction (int,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sig_handler(int signo)
{
	struct sigaction action;
#ifdef __GLIBC__ /* backtrace() is a GNU extension */
	int nptrs;
	void *buffer[BACKTRACE_SZ];

	nptrs = backtrace(buffer, BACKTRACE_SZ);
	backtrace_symbols_fd(buffer, nptrs, STDERR_FILENO);
#endif
	dump_debug_buffer();

	/*
	 * Restore default action and re-raise signal so SIGSEGV and
	 * SIGABRT can trigger a core dump.
	 */
	action.sa_handler = SIG_DFL;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	(void) sigaction(signo, &action, NULL);
	raise(signo);
}