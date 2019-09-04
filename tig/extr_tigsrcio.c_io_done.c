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
struct io {scalar_t__ pid; int pipe; int /*<<< orphan*/  status; scalar_t__ error; int /*<<< orphan*/  buf; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 int /*<<< orphan*/  WIFSIGNALED (int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_init (struct io*) ; 
 scalar_t__ waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 

bool
io_done(struct io *io)
{
	pid_t pid = io->pid;

	if (io->pipe != -1)
		close(io->pipe);
	free(io->buf);
	io_init(io);

	while (pid > 0) {
		int status = 0;
		pid_t waiting = waitpid(pid, &status, 0);

		if (waiting < 0) {
			if (errno == EINTR)
				continue;
			io->error = errno;
			return false;
		}

		io->status = WIFEXITED(status) ? WEXITSTATUS(status) : 0;

		return waiting == pid &&
		       !WIFSIGNALED(status) &&
		       !io->status;
	}

	return true;
}