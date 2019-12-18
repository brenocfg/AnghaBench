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
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 scalar_t__ EISDIR ; 
 scalar_t__ EOPNOTSUPP ; 
 int O_TMPFILE ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 

int
main(int argc, char *argv[])
{
	int fd;
	struct stat buf;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s dir\n", argv[0]);
		return (2);
	}
	if (stat(argv[1], &buf) < 0) {
		perror("stat");
		return (2);
	}
	if (!S_ISDIR(buf.st_mode)) {
		fprintf(stderr, "\"%s\" is not a directory\n", argv[1]);
		return (2);
	}

	fd = open(argv[1], O_TMPFILE | O_WRONLY, 0666);
	if (fd < 0) {
		if (errno == EISDIR) {
			fprintf(stderr,
			    "The kernel doesn't support O_TMPFILE\n");
			return (1);
		} else if (errno == EOPNOTSUPP) {
			fprintf(stderr,
			    "The filesystem doesn't support O_TMPFILE\n");
			return (2);
		}
		perror("open");
	} else {
		close(fd);
	}
	return (0);
}