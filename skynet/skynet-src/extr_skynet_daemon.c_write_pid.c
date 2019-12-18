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
 int LOCK_EX ; 
 int LOCK_NB ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int flock (int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int fscanf (int /*<<< orphan*/ *,char*,int*) ; 
 int getpid () ; 
 int open (char const*,int,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
write_pid(const char *pidfile) {
	FILE *f;
	int pid = 0;
	int fd = open(pidfile, O_RDWR|O_CREAT, 0644);
	if (fd == -1) {
		fprintf(stderr, "Can't create pidfile [%s].\n", pidfile);
		return 0;
	}
	f = fdopen(fd, "w+");
	if (f == NULL) {
		fprintf(stderr, "Can't open pidfile [%s].\n", pidfile);
		return 0;
	}

	if (flock(fd, LOCK_EX|LOCK_NB) == -1) {
		int n = fscanf(f, "%d", &pid);
		fclose(f);
		if (n != 1) {
			fprintf(stderr, "Can't lock and read pidfile.\n");
		} else {
			fprintf(stderr, "Can't lock pidfile, lock is held by pid %d.\n", pid);
		}
		return 0;
	}

	pid = getpid();
	if (!fprintf(f,"%d\n", pid)) {
		fprintf(stderr, "Can't write pid.\n");
		close(fd);
		return 0;
	}
	fflush(f);

	return pid;
}