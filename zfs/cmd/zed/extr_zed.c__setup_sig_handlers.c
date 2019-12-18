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
struct sigaction {int /*<<< orphan*/  sa_handler; int /*<<< orphan*/  sa_flags; int /*<<< orphan*/  sa_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  SA_RESTART ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  _exit_handler ; 
 int /*<<< orphan*/  _hup_handler ; 
 scalar_t__ sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 scalar_t__ sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zed_log_die (char*) ; 

__attribute__((used)) static void
_setup_sig_handlers(void)
{
	struct sigaction sa;

	if (sigemptyset(&sa.sa_mask) < 0)
		zed_log_die("Failed to initialize sigset");

	sa.sa_flags = SA_RESTART;
	sa.sa_handler = SIG_IGN;

	if (sigaction(SIGPIPE, &sa, NULL) < 0)
		zed_log_die("Failed to ignore SIGPIPE");

	sa.sa_handler = _exit_handler;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		zed_log_die("Failed to register SIGINT handler");

	if (sigaction(SIGTERM, &sa, NULL) < 0)
		zed_log_die("Failed to register SIGTERM handler");

	sa.sa_handler = _hup_handler;
	if (sigaction(SIGHUP, &sa, NULL) < 0)
		zed_log_die("Failed to register SIGHUP handler");
}