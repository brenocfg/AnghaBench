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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  SWAY_ERROR ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int S_IXUSR ; 
 int /*<<< orphan*/  chmod (char*,int) ; 
 int /*<<< orphan*/  execl (char*,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  mkstemp (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  sway_log_errno (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool terminal_execute(char *terminal, char *command) {
	char fname[] = "/tmp/swaynagXXXXXX";
	FILE *tmp= fdopen(mkstemp(fname), "w");
	if (!tmp) {
		sway_log(SWAY_ERROR, "Failed to create temp script");
		return false;
	}
	sway_log(SWAY_DEBUG, "Created temp script: %s", fname);
	fprintf(tmp, "#!/bin/sh\nrm %s\n%s", fname, command);
	fclose(tmp);
	chmod(fname, S_IRUSR | S_IWUSR | S_IXUSR);
	char *cmd = malloc(sizeof(char) * (strlen(terminal) + strlen(" -e ") + strlen(fname) + 1));
	sprintf(cmd, "%s -e %s", terminal, fname);
	execl("/bin/sh", "/bin/sh", "-c", cmd, NULL);
	sway_log_errno(SWAY_ERROR, "Failed to run command, execl() returned.");
	free(cmd);
	return false;
}