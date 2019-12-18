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
 int /*<<< orphan*/  O_RDONLY ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int bsize ; 
 int /*<<< orphan*/  close (int) ; 
 int count ; 
 char* execname ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  free (void*) ; 
 char* ifile ; 
 int lseek (int,int,int /*<<< orphan*/ ) ; 
 char* ofile ; 
 int open (char*,int,...) ; 
 int /*<<< orphan*/  parse_options (int,char**) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int posix_memalign (void**,int,int) ; 
 int read (int,void*,int) ; 
 int seek ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 
 int stride ; 
 int write (int,void*,int) ; 

int
main(int argc, char *argv[])
{
	int i;
	int ifd;
	int ofd;
	void *buf;
	int c;

	parse_options(argc, argv);

	ifd = open(ifile, O_RDONLY);
	if (ifd == -1) {
		(void) fprintf(stderr, "%s: %s: ", execname, ifile);
		perror("open");
		exit(2);
	}

	ofd = open(ofile, O_WRONLY | O_CREAT, 0666);
	if (ofd == -1) {
		(void) fprintf(stderr, "%s: %s: ", execname, ofile);
		perror("open");
		exit(2);
	}

	/*
	 * We use valloc because some character block devices expect a
	 * page-aligned buffer.
	 */
	int err = posix_memalign(&buf, 4096, bsize);
	if (err != 0) {
		(void) fprintf(stderr,
		    "%s: %s\n", execname, strerror(err));
		exit(2);
	}

	if (seek > 0) {
		if (lseek(ofd, seek * bsize, SEEK_CUR) == -1) {
			perror("output lseek");
			exit(2);
		}
	}

	for (i = 0; i < count; i++) {
		c = read(ifd, buf, bsize);
		if (c != bsize) {

			perror("read");
			exit(2);
		}
		if (c != bsize) {
			if (c < 0) {
				perror("read");
			} else {
				(void) fprintf(stderr,
				    "%s: unexpected short read, read %d "
				    "bytes, expected %d\n", execname,
				    c, bsize);
			}
			exit(2);
		}

		c = write(ofd, buf, bsize);
		if (c != bsize) {
			if (c < 0) {
				perror("write");
			} else {
				(void) fprintf(stderr,
				    "%s: unexpected short write, wrote %d "
				    "bytes, expected %d\n", execname,
				    c, bsize);
			}
			exit(2);
		}

		if (stride > 1) {
			if (lseek(ifd, (stride - 1) * bsize, SEEK_CUR) == -1) {
				perror("input lseek");
				exit(2);
			}
			if (lseek(ofd, (stride - 1) * bsize, SEEK_CUR) == -1) {
				perror("output lseek");
				exit(2);
			}
		}
	}
	free(buf);

	(void) close(ofd);
	(void) close(ifd);

	return (0);
}