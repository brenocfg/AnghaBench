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

/* Variables and functions */
 int O_CREAT ; 
 int O_EXCL ; 
 int O_WRONLY ; 
 int atexit (int /*<<< orphan*/  (*) ()) ; 
 int close (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int getpid () ; 
 int open (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * pidfile ; 
 int /*<<< orphan*/  remove_pidfile () ; 
 int sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ write (int,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
setup_pidfile()
{
	int f, error, pid;
	char pid_str[21];

	if (pidfile == NULL)
		return 0;

	pid = getpid();

	error = sprintf(pid_str, "%d", pid);
	if (error < 0)
		goto fail;

	f = open(pidfile, O_CREAT|O_EXCL|O_WRONLY, 0644);
	if (f < 0)
		goto fail;

	error = atexit(remove_pidfile);
	if (error < 0) {
		close(f);
		remove_pidfile();
		goto fail;
	}

	if (0 > (write(f, (void*)pid_str, strlen(pid_str)))) {
		close(f);
		goto fail;
	}

	error = close(f);
	if (error < 0)
		goto fail;

	return 0;

fail:
	fprintf(stderr, "Failed to set up pidfile\n");
	return -1;
}