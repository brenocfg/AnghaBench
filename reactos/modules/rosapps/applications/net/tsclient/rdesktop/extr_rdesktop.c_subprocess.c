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
typedef  int /*<<< orphan*/  str_handle_lines_t ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  RDPCLIENT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int /*<<< orphan*/  execvp (char* const,char* const*) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ pipe (int*) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  str_handle_lines (int /*<<< orphan*/ *,char*,char**,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  xfree (char*) ; 

BOOL
subprocess(RDPCLIENT * This, char *const argv[], str_handle_lines_t linehandler, void *data)
{
	pid_t child;
	int fd[2];
	int n = 1;
	char output[256];
	char *rest = NULL;

	if (pipe(fd) < 0)
	{
		perror("pipe");
		return False;
	}

	if ((child = fork()) < 0)
	{
		perror("fork");
		return False;
	}

	/* Child */
	if (child == 0)
	{
		/* Close read end */
		close(fd[0]);

		/* Redirect stdout and stderr to pipe */
		dup2(fd[1], 1);
		dup2(fd[1], 2);

		/* Execute */
		execvp(argv[0], argv);
		perror("Error executing child");
		_exit(128);
	}

	/* Parent. Close write end. */
	close(fd[1]);
	while (n > 0)
	{
		n = read(fd[0], output, 255);
		output[n] = '\0';
		str_handle_lines(This, output, &rest, linehandler, data);
	}
	xfree(rest);

	return True;
}