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

/* Variables and functions */
 int MAXPATHLEN ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int open (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,unsigned int) ; 
 int sscanf (char*,char*,unsigned int*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (char*,int) ; 

int
main(int argc, char **argv)
{
	unsigned int numfiles = 0;
	unsigned int first_file = 0;
	unsigned int i;
	char buf[MAXPATHLEN];

	if (argc < 3 || argc > 4)
		usage("Invalid number of arguments", -1);

	if (sscanf(argv[2], "%u", &numfiles) != 1)
		usage("Invalid maximum file", -2);

	if (argc == 4 && sscanf(argv[3], "%u", &first_file) != 1)
		usage("Invalid first file", -3);

	for (i = first_file; i < first_file + numfiles; i++) {
		int fd;
		(void) snprintf(buf, MAXPATHLEN, "%s%u", argv[1], i);
		if ((fd = open(buf, O_CREAT | O_EXCL, O_RDWR)) == -1) {
			(void) fprintf(stderr, "Failed to create %s %s\n", buf,
			    strerror(errno));
			return (-4);
		}
		(void) close(fd);
	}
	return (0);
}