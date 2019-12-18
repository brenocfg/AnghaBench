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
struct stat {int st_mode; } ;
typedef  int /*<<< orphan*/  penv ;
typedef  int mode_t ;
typedef  int /*<<< orphan*/  fpath ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDWR ; 
 int S_ISGID ; 
 int S_ISUID ; 
 int /*<<< orphan*/  close (int) ; 
 int creat (char*,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* getenv (char*) ; 
 int mkdir (char*,int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int setuid (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int stat (char*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  umask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int write (int,char*,int) ; 

__attribute__((used)) static void
test_stat_mode(mode_t extra)
{
	struct stat st;
	int i, fd;
	char fpath[1024];
	char *penv[] = {"TESTDIR", "TESTFILE0"};
	char buf[] = "test";
	mode_t res;
	mode_t mode = 0777 | extra;

	/*
	 * Get the environment variable values.
	 */
	for (i = 0; i < sizeof (penv) / sizeof (char *); i++) {
		if ((penv[i] = getenv(penv[i])) == NULL) {
			fprintf(stderr, "getenv(penv[%d])\n", i);
			exit(1);
		}
	}

	umask(0);
	if (stat(penv[0], &st) == -1 && mkdir(penv[0], mode) == -1) {
		perror("mkdir");
		exit(2);
	}

	snprintf(fpath, sizeof (fpath), "%s/%s", penv[0], penv[1]);
	unlink(fpath);
	if (stat(fpath, &st) == 0) {
		fprintf(stderr, "%s exists\n", fpath);
		exit(3);
	}

	fd = creat(fpath, mode);
	if (fd == -1) {
		perror("creat");
		exit(4);
	}
	close(fd);

	if (setuid(65534) == -1) {
		perror("setuid");
		exit(5);
	}

	fd = open(fpath, O_RDWR);
	if (fd == -1) {
		perror("open");
		exit(6);
	}

	if (write(fd, buf, sizeof (buf)) == -1) {
		perror("write");
		exit(7);
	}
	close(fd);

	if (stat(fpath, &st) == -1) {
		perror("stat");
		exit(8);
	}
	unlink(fpath);

	/* Verify SUID/SGID are dropped */
	res = st.st_mode & (0777 | S_ISUID | S_ISGID);
	if (res != (mode & 0777)) {
		fprintf(stderr, "stat(2) %o\n", res);
		exit(9);
	}
}