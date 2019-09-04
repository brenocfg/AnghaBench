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
struct stat {size_t st_size; } ;
struct chmcFile {int /*<<< orphan*/  fd; } ;
typedef  size_t off_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (char*,char const*) ; 
 int CHMC_NOERR ; 
 int O_BINARY ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int open (char const*,int) ; 
 int read (int,void*,size_t) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,void*,int) ; 

int chmc_appendfile(struct chmcFile *chm, const char *filename, void *buf,
                size_t size )
{
	struct stat statbuf;
	int in;
	off_t todo, toread;
	int rx;

	if (stat(filename, &statbuf) < 0)
		return errno;

	in = open(filename, O_RDONLY | O_BINARY);
	if (in >= 0) {
		todo = statbuf.st_size;

		while (todo) {
			toread = size;
			if (toread > todo)
				toread = todo;

			rx = read(in, buf, toread);
			if (rx > 0) {
				write(chm->fd, buf, rx);
				todo -= rx;
			}
		}

		close(in);
	}
	else
		BUG_ON("open %s\n", filename);

	return CHMC_NOERR;
}