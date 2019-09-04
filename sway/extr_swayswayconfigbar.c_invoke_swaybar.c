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
struct bar_config {scalar_t__ pid; char* swaybar_command; char* id; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  SWAY_ERROR ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  execvp (char* const,char* const*) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int pipe (int*) ; 
 int read (int,...) ; 
 int /*<<< orphan*/  setpgid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t snprintf (char*,size_t,char*,char*,char*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ write (int,...) ; 

__attribute__((used)) static void invoke_swaybar(struct bar_config *bar) {
	// Pipe to communicate errors
	int filedes[2];
	if (pipe(filedes) == -1) {
		sway_log(SWAY_ERROR, "Pipe setup failed! Cannot fork into bar");
		return;
	}

	bar->pid = fork();
	if (bar->pid == 0) {
		setpgid(0, 0);
		close(filedes[0]);
		sigset_t set;
		sigemptyset(&set);
		sigprocmask(SIG_SETMASK, &set, NULL);

		// run custom swaybar
		size_t len = snprintf(NULL, 0, "%s -b %s",
				bar->swaybar_command ? bar->swaybar_command : "swaybar",
				bar->id);
		char *command = malloc(len + 1);
		if (!command) {
			const char msg[] = "Unable to allocate swaybar command string";
			size_t msg_len = sizeof(msg);
			if (write(filedes[1], &msg_len, sizeof(size_t))) {};
			if (write(filedes[1], msg, msg_len)) {};
			close(filedes[1]);
			exit(1);
		}
		snprintf(command, len + 1, "%s -b %s",
				bar->swaybar_command ? bar->swaybar_command : "swaybar",
				bar->id);
		char *const cmd[] = { "sh", "-c", command, NULL, };
		close(filedes[1]);
		execvp(cmd[0], cmd);
		exit(1);
	}
	sway_log(SWAY_DEBUG, "Spawned swaybar %d", bar->pid);
	close(filedes[0]);
	size_t len;
	if (read(filedes[1], &len, sizeof(size_t)) == sizeof(size_t)) {
		char *buf = malloc(len);
		if(!buf) {
			sway_log(SWAY_ERROR, "Cannot allocate error string");
			return;
		}
		if (read(filedes[1], buf, len)) {
			sway_log(SWAY_ERROR, "%s", buf);
		}
		free(buf);
	}
	close(filedes[1]);
}