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
struct status_line {int buffer_size; scalar_t__ pid; int read_fd; int write_fd; void* write; void* read; int /*<<< orphan*/  buffer; int /*<<< orphan*/  cont_signal; int /*<<< orphan*/  stop_signal; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  SIGCONT ; 
 int /*<<< orphan*/  SIGSTOP ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  SWAY_ERROR ; 
 struct status_line* calloc (int,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  execvp (char* const,char* const*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* fdopen (int,char*) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  malloc (int) ; 
 scalar_t__ pipe (int*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 

struct status_line *status_line_init(char *cmd) {
	struct status_line *status = calloc(1, sizeof(struct status_line));
	status->stop_signal = SIGSTOP;
	status->cont_signal = SIGCONT;

	status->buffer_size = 8192;
	status->buffer = malloc(status->buffer_size);

	int pipe_read_fd[2];
	int pipe_write_fd[2];
	if (pipe(pipe_read_fd) != 0 || pipe(pipe_write_fd) != 0) {
		sway_log(SWAY_ERROR, "Unable to create pipes for status_command fork");
		exit(1);
	}

	status->pid = fork();
	if (status->pid == 0) {
		dup2(pipe_read_fd[1], STDOUT_FILENO);
		close(pipe_read_fd[0]);
		close(pipe_read_fd[1]);

		dup2(pipe_write_fd[0], STDIN_FILENO);
		close(pipe_write_fd[0]);
		close(pipe_write_fd[1]);

		char *const _cmd[] = { "sh", "-c", cmd, NULL, };
		execvp(_cmd[0], _cmd);
		exit(1);
	}

	close(pipe_read_fd[1]);
	status->read_fd = pipe_read_fd[0];
	fcntl(status->read_fd, F_SETFL, O_NONBLOCK);
	close(pipe_write_fd[0]);
	status->write_fd = pipe_write_fd[1];
	fcntl(status->write_fd, F_SETFL, O_NONBLOCK);

	status->read = fdopen(status->read_fd, "r");
	status->write = fdopen(status->write_fd, "w");
	return status;
}