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
 int O_CREAT ; 
 int O_RDWR ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  filename ; 
 int /*<<< orphan*/  fsize ; 
 scalar_t__ ftruncate (int,int /*<<< orphan*/ ) ; 
 scalar_t__ ftruncflag ; 
 int open (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  parse_options (int,char**) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ truncate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
main(int argc, char *argv[])
{
	int fd;

	parse_options(argc, argv);

	if (ftruncflag) {
		fd = open(filename, O_RDWR|O_CREAT, 0666);
		if (fd < 0) {
			perror("open");
			return (1);
		}
		if (ftruncate(fd, fsize) < 0) {
			perror("ftruncate");
			return (1);
		}
		if (close(fd)) {
			perror("close");
			return (1);
		}
	} else {
		if (truncate(filename, fsize) < 0) {
			perror("truncate");
			return (1);
		}
	}
	return (0);
}