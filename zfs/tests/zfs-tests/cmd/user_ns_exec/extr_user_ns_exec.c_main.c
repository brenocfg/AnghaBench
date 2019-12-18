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

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int WEXITSTATUS (int) ; 
 int child_main (int,char**,int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  kill (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int read (int,char*,int) ; 
 scalar_t__ set_idmap (scalar_t__,char*) ; 
 scalar_t__ socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 
 int write (int,char*,int) ; 

int
main(int argc, char *argv[])
{
	char sync_buf;
	int result, wstatus;
	int syncfd[2];
	pid_t child;

	if (argc < 2 || strlen(argv[1]) == 0) {
		(void) printf("\tUsage: %s <commands> ...\n", argv[0]);
		return (1);
	}

	if (socketpair(AF_UNIX, SOCK_STREAM, 0, syncfd) != 0) {
		perror("socketpair");
		return (1);
	}

	child = fork();
	if (child == (pid_t)-1) {
		perror("fork");
		return (1);
	}

	if (child == 0) {
		close(syncfd[0]);
		return (child_main(argc, argv, syncfd[1]));
	}

	close(syncfd[1]);

	result = 0;
	/* wait for the child to have unshared its namespaces */
	if (read(syncfd[0], &sync_buf, 1) != 1) {
		perror("read");
		kill(child, SIGKILL);
		result = 1;
		goto reap;
	}

	/* write uid mapping */
	if (set_idmap(child, "uid_map") != 0 ||
	    set_idmap(child, "gid_map") != 0) {
		result = 1;
		kill(child, SIGKILL);
		goto reap;
	}

	/* tell the child to proceed */
	if (write(syncfd[0], "1", 1) != 1) {
		perror("write");
		kill(child, SIGKILL);
		result = 1;
		goto reap;
	}
	close(syncfd[0]);

reap:
	while (waitpid(child, &wstatus, 0) != child)
		kill(child, SIGKILL);
	if (result == 0)
		result = WEXITSTATUS(wstatus);

	return (result);
}