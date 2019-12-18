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
typedef  int /*<<< orphan*/  pdfapp_t ;

/* Variables and functions */
 int /*<<< orphan*/  execlp (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  waitpid (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void winopenuri(pdfapp_t *app, char *buf)
{
	char *browser = getenv("BROWSER");
	pid_t pid;
	if (!browser)
	{
#ifdef __APPLE__
		browser = "open";
#else
		browser = "xdg-open";
#endif
	}
	/* Fork once to start a child process that we wait on. This
	 * child process forks again and immediately exits. The
	 * grandchild process continues in the background. The purpose
	 * of this strange two-step is to avoid zombie processes. See
	 * bug 695701 for an explanation. */
	pid = fork();
	if (pid == 0)
	{
		if (fork() == 0)
		{
			execlp(browser, browser, buf, (char*)0);
			fprintf(stderr, "cannot exec '%s'\n", browser);
		}
		exit(0);
	}
	waitpid(pid, NULL, 0);
}