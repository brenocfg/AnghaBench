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
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int O_APPEND ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int /*<<< orphan*/  _SC_NPROCESSORS_ONLN ; 
 int errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  go ; 
 int open (char*,int,int) ; 
 size_t optind ; 
 int outfd ; 
 int /*<<< orphan*/  perror (char*) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 long sysconf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char **argv)
{
	pthread_t tid;
	int	ret = 0;
	long	ncpus = 0;
	int	i;

	if (argc != 2) {
		usage();
	}

	ncpus = sysconf(_SC_NPROCESSORS_ONLN);
	if (ncpus < 0) {
		(void) fprintf(stderr,
		    "Invalid return from sysconf(_SC_NPROCESSORS_ONLN)"
		    " : errno (decimal)=%d\n", errno);
		exit(1);
	}
	if (ncpus < 2) {
		(void) fprintf(stderr,
		    "Must execute this binary on a multi-processor system\n");
		exit(1);
	}

	outfd = open(argv[optind++], O_RDWR|O_CREAT|O_APPEND|O_TRUNC, 0777);
	if (outfd == -1) {
		(void) fprintf(stderr,
		    "zfs_threadsappend: "
		    "open(%s, O_RDWR|O_CREAT|O_APPEND|O_TRUNC, 0777)"
		    " failed\n", argv[optind]);
		perror("open");
		exit(1);
	}

	for (i = 0; i < 2; i++) {
		ret = pthread_create(&tid, NULL, go, (void *)&i);
		if (ret != 0) {
			(void) fprintf(stderr,
			    "zfs_threadsappend: thr_create(#%d) "
			    "failed error=%d\n", i+1, ret);
			exit(1);
		}
	}

	while (pthread_join(tid, NULL) == 0)
		continue;

	return (0);
}