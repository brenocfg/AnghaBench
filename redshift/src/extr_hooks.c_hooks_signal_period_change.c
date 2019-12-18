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
struct dirent {char* d_name; } ;
typedef  scalar_t__ pid_t ;
typedef  size_t period_t ;
typedef  int /*<<< orphan*/  hook_path ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ EACCES ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int MAX_HOOK_PATH ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int execl (char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/ * open_hooks_dir (char*) ; 
 int /*<<< orphan*/ * period_names ; 
 int /*<<< orphan*/  perror (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 

void
hooks_signal_period_change(period_t prev_period, period_t period)
{
	char hooksdir_path[MAX_HOOK_PATH];
	DIR *hooks_dir = open_hooks_dir(hooksdir_path);
	if (hooks_dir == NULL) return;

	struct dirent* ent;
	while ((ent = readdir(hooks_dir)) != NULL) {
		/* Skip hidden and special files (., ..) */
		if (ent->d_name[0] == '\0' || ent->d_name[0] == '.') continue;

		char *hook_name = ent->d_name;
		char hook_path[MAX_HOOK_PATH];
		snprintf(hook_path, sizeof(hook_path), "%s/%s",
			 hooksdir_path, hook_name);

#ifndef _WIN32
		/* Fork and exec the hook. We close stdout
		   so the hook cannot interfere with the normal
		   output. */
		pid_t pid = fork();
		if (pid == (pid_t)-1) {
			perror("fork");
			continue;
		} else if (pid == 0) { /* Child */
			close(STDOUT_FILENO);

			int r = execl(hook_path, hook_name,
				      "period-changed",
				      period_names[prev_period],
				      period_names[period], NULL);
			if (r < 0 && errno != EACCES) perror("execl");

			/* Only reached on error */
			_exit(EXIT_FAILURE);
		}
#endif
	}
}