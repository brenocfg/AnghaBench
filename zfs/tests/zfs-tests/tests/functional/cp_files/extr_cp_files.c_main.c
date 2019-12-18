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
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int O_CREAT ; 
 int /*<<< orphan*/  O_DIRECTORY ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int openat (int,char*,int,int) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 

int
main(int argc, char *argv[])
{
	int tfd;
	DIR *sdir;
	struct dirent *dirent;

	if (argc != 3) {
		fprintf(stderr, "Usage: %s SRC DST\n", argv[0]);
		exit(1);
	}

	sdir = opendir(argv[1]);
	if (sdir == NULL) {
		fprintf(stderr, "Failed to open %s: %s\n",
		    argv[1], strerror(errno));
		exit(2);
	}

	tfd = open(argv[2], O_DIRECTORY);
	if (tfd < 0) {
		fprintf(stderr, "Failed to open %s: %s\n",
		    argv[2], strerror(errno));
		closedir(sdir);
		exit(3);
	}

	while ((dirent = readdir(sdir)) != NULL) {
		if (dirent->d_name[0] == '.' &&
		    (dirent->d_name[1] == '.' || dirent->d_name[1] == '\0'))
			continue;

		int fd = openat(tfd, dirent->d_name, O_CREAT|O_WRONLY, 0666);
		if (fd < 0) {
			fprintf(stderr, "Failed to create %s/%s: %s\n",
			    argv[2], dirent->d_name, strerror(errno));
			closedir(sdir);
			close(tfd);
			exit(4);
		}
		close(fd);
	}

	closedir(sdir);
	close(tfd);

	return (0);
}