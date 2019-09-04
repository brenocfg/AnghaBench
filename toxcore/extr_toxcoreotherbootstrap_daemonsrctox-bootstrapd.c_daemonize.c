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
typedef  int pid_t ;
typedef  scalar_t__ LOG_BACKEND ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ LOG_BACKEND_STDOUT ; 
 int /*<<< orphan*/  LOG_LEVEL_ERROR ; 
 int /*<<< orphan*/  LOG_LEVEL_INFO ; 
 int /*<<< orphan*/  LOG_LEVEL_WARNING ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 scalar_t__ chdir (char*) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int const) ; 
 scalar_t__ setsid () ; 
 int /*<<< orphan*/  write_log (int /*<<< orphan*/ ,char*,...) ; 

void daemonize(LOG_BACKEND log_backend, char *pid_file_path)
{
    // Check if the PID file exists
    FILE *pid_file;

    if ((pid_file = fopen(pid_file_path, "r"))) {
        write_log(LOG_LEVEL_WARNING, "Another instance of the daemon is already running, PID file %s exists.\n", pid_file_path);
        fclose(pid_file);
    }

    // Open the PID file for writing
    pid_file = fopen(pid_file_path, "a+");

    if (pid_file == NULL) {
        write_log(LOG_LEVEL_ERROR, "Couldn't open the PID file for writing: %s. Exiting.\n", pid_file_path);
        exit(1);
    }

    // Fork off from the parent process
    const pid_t pid = fork();

    if (pid > 0) {
        fprintf(pid_file, "%d", pid);
        fclose(pid_file);
        write_log(LOG_LEVEL_INFO, "Forked successfully: PID: %d.\n", pid);
        exit(0);
    } else {
        fclose(pid_file);
    }

    if (pid < 0) {
        write_log(LOG_LEVEL_ERROR, "Forking failed. Exiting.\n");
        exit(1);
    }

    // Create a new SID for the child process
    if (setsid() < 0) {
        write_log(LOG_LEVEL_ERROR, "SID creation failure. Exiting.\n");
        exit(1);
    }


    // Change the current working directory
    if ((chdir("/")) < 0) {
        write_log(LOG_LEVEL_ERROR, "Couldn't change working directory to '/'. Exiting.\n");
        exit(1);
    }

    // Go quiet
    if (log_backend != LOG_BACKEND_STDOUT) {
        close(STDOUT_FILENO);
        close(STDIN_FILENO);
        close(STDERR_FILENO);
    }
}