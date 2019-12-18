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
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fail (char*,int) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,long) ; 
 int /*<<< orphan*/  setsid () ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
daemonize(void)
{
	pid_t	pid;

	if ((pid = fork()) < 0) {
		fail("fork", 1);
	} else if (pid != 0) {
		(void) fprintf(stdout, "%ld\n", (long)pid);
		exit(0);
	}

	(void) setsid();
	(void) close(0);
	(void) close(1);
	(void) close(2);
}