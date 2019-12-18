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
struct io {int pid; int pipe; void* error; } ;
typedef  enum io_type { ____Placeholder_io_type } io_type ;

/* Variables and functions */
 int IO_AP ; 
 int IO_FG ; 
 int IO_RD ; 
 int IO_RD_FORWARD_STDIN ; 
 int IO_RD_WITH_STDERR ; 
 int IO_RP ; 
 int IO_WR ; 
 int /*<<< orphan*/  O_RDWR ; 
 int STDERR_FILENO ; 
 int STDIN_FILENO ; 
 int STDOUT_FILENO ; 
 int /*<<< orphan*/  _exit (void*) ; 
 int chdir (char const*) ; 
 int /*<<< orphan*/  close (int) ; 
 int dup (int) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 void* errno ; 
 int /*<<< orphan*/  execvp (char const*,char* const*) ; 
 int fork () ; 
 int /*<<< orphan*/  io_init (struct io*) ; 
 int io_open (struct io*,char*,char const*,char const*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int open_trace (int,char const**) ; 
 scalar_t__ pipe (int*) ; 
 int /*<<< orphan*/  putenv (char* const) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 

bool
io_exec(struct io *io, enum io_type type, const char *dir, char * const env[], const char *argv[], int custom)
{
	int pipefds[2] = { -1, -1 };
	bool read_from_stdin = type == IO_RD && (custom & IO_RD_FORWARD_STDIN);
	bool read_with_stderr = type == IO_RD && (custom & IO_RD_WITH_STDERR);

	io_init(io);

	if (dir && !strcmp(dir, argv[0]))
		return io_open(io, "%s%s", dir, argv[1]);

	if ((type == IO_RD || type == IO_RP || type == IO_WR) && pipe(pipefds) < 0) {
		io->error = errno;
		return false;
	} else if (type == IO_AP) {
		pipefds[1] = custom;
	}

	if ((io->pid = fork())) {
		if (io->pid == -1)
			io->error = errno;
		if (pipefds[!(type == IO_WR)] != -1)
			close(pipefds[!(type == IO_WR)]);
		if (io->pid != -1) {
			io->pipe = pipefds[!!(type == IO_WR)];
			return true;
		}

	} else {
		if (type != IO_FG) {
			int devnull = open("/dev/null", O_RDWR);
			int readfd  = type == IO_WR ? pipefds[0]
				    : type == IO_RP ? custom
				    : devnull;
			int writefd = (type == IO_RD || type == IO_RP || type == IO_AP)
				    ? pipefds[1] : devnull;
			int errorfd = open_trace(devnull, argv);

			/* Inject stdin given on the command line. */
			if (read_from_stdin)
				readfd = dup(STDIN_FILENO);

			dup2(readfd,  STDIN_FILENO);
			dup2(writefd, STDOUT_FILENO);
			if (read_with_stderr)
				dup2(writefd, STDERR_FILENO);
			else
				dup2(errorfd, STDERR_FILENO);

			if (devnull != errorfd)
				close(errorfd);
			close(devnull);
			if (pipefds[0] != -1)
				close(pipefds[0]);
			if (pipefds[1] != -1)
				close(pipefds[1]);
		}

		if (dir && *dir && chdir(dir) == -1)
			_exit(errno);

		if (env) {
			int i;

			for (i = 0; env[i]; i++)
				if (*env[i])
					putenv(env[i]);
		}

		execvp(argv[0], (char *const*) argv);

		close(STDOUT_FILENO);
		_exit(errno);
	}

	if (pipefds[!!(type == IO_WR)] != -1)
		close(pipefds[!!(type == IO_WR)]);
	return false;
}