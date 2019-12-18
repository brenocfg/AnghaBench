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
typedef  long int64_t ;

/* Variables and functions */
 int BIGBUFFERSIZE ; 
 unsigned char DATA ; 
 int /*<<< orphan*/  O_RDONLY ; 
 unsigned char atoi (char*) ; 
 unsigned char* bigbuffer ; 
 int errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 long read (int,unsigned char**,int) ; 

int
main(int argc, char **argv)
{
	int		bigfd;
	long		i, n;
	unsigned char	fillchar = DATA;
	int		bigbuffersize = BIGBUFFERSIZE;
	int64_t		read_count = 0;

	/*
	 * Validate arguments
	 */
	if (argc < 2) {
		(void) printf("Usage: %s filename [pattern]\n",
		    argv[0]);
		exit(1);
	}

	if (argv[2]) {
		fillchar = atoi(argv[2]);
	}

	/*
	 * Read the file contents and check every character
	 * against the supplied pattern. Abort if the
	 * pattern check fails.
	 */
	if ((bigfd = open(argv[1], O_RDONLY)) == -1) {
		(void) printf("open %s failed %d\n", argv[1], errno);
		exit(1);
	}

	do {
		if ((n = read(bigfd, &bigbuffer, bigbuffersize)) == -1) {
			(void) printf("read failed (%ld), %d\n", n, errno);
			exit(errno);
		}

		for (i = 0; i < n; i++) {
			if (bigbuffer[i] != fillchar) {
				(void) printf("error %s: 0x%x != 0x%x)\n",
				    argv[1], bigbuffer[i], fillchar);
				exit(1);
			}
		}

		read_count += n;
	} while (n == bigbuffersize);

	return (0);
}