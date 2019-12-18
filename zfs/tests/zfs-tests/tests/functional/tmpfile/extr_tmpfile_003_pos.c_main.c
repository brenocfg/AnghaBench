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
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  penv ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 int /*<<< orphan*/  AT_SYMLINK_FOLLOW ; 
 int O_EXCL ; 
 int O_RDWR ; 
 int O_TMPFILE ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* getenv (char*) ; 
 scalar_t__ linkat (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

int
main(int argc, char *argv[])
{
	int i, fd;
	char spath[1024], dpath[1024];
	char *penv[] = {"TESTDIR", "TESTFILE0"};
	struct stat sbuf;

	(void) fprintf(stdout, "Verify O_EXCL tmpfile cannot be linked.\n");

	/*
	 * Get the environment variable values.
	 */
	for (i = 0; i < sizeof (penv) / sizeof (char *); i++) {
		if ((penv[i] = getenv(penv[i])) == NULL) {
			(void) fprintf(stderr, "getenv(penv[%d])\n", i);
			exit(1);
		}
	}

	fd = open(penv[0], O_RDWR|O_TMPFILE|O_EXCL, 0666);
	if (fd < 0) {
		perror("open");
		exit(2);
	}

	snprintf(spath, 1024, "/proc/self/fd/%d", fd);
	snprintf(dpath, 1024, "%s/%s", penv[0], penv[1]);
	if (linkat(AT_FDCWD, spath, AT_FDCWD, dpath, AT_SYMLINK_FOLLOW) == 0) {
		fprintf(stderr, "linkat returns successfully\n");
		close(fd);
		exit(3);
	}

	if (stat(dpath, &sbuf) == 0) {
		fprintf(stderr, "stat returns successfully\n");
		close(fd);
		exit(4);
	}
	close(fd);

	return (0);
}