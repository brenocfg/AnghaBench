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
struct stat {int st_nlink; } ;
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int O_APPEND ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  cleaner ; 
 int /*<<< orphan*/  exit (int) ; 
 char* filebase ; 
 int /*<<< orphan*/  mover ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  pthread_setconcurrency (int) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int stat (char*,struct stat*) ; 
 int /*<<< orphan*/  writer ; 

int
main(int argc, char **argv)
{
	int fd;
	pthread_t tid;

	if (argc == 1) {
		(void) printf("Usage: %s <filebase>\n", argv[0]);
		exit(-1);
	}

	filebase = argv[1];
	fd = open(filebase, O_APPEND | O_RDWR | O_CREAT, 0644);
	if (fd < 0) {
		perror("creating test file");
		exit(-1);
	}

	(void) pthread_setconcurrency(4);	/* 3 threads + main */
	(void) pthread_create(&tid, NULL, mover, NULL);
	(void) pthread_create(&tid, NULL, cleaner, NULL);
	(void) pthread_create(&tid, NULL, writer, (void *) &fd);

	for (;;) {
		int ret;
		struct stat st;

		ret = stat(filebase, &st);
		if (ret == 0 && (st.st_nlink > 2 || st.st_nlink < 1)) {
			(void) printf("st.st_nlink = %d, exiting\n", \
			    (int)st.st_nlink);
			exit(0);
		}
		(void) sleep(1);
	}

	return (0);
}