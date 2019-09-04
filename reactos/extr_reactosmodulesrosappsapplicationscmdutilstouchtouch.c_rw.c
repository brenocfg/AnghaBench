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
typedef  int /*<<< orphan*/  u_char ;
struct stat {scalar_t__ st_size; int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  DEFFILEMODE ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ _chmod (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ _chsize (int,int /*<<< orphan*/ ) ; 
 scalar_t__ _close (int) ; 
 int _lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _read (int,int /*<<< orphan*/ *,int) ; 
 int _write (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 
 int /*<<< orphan*/  warnx (char*,char*,int /*<<< orphan*/ ) ; 

int
rw(char *fname, struct stat *sbp, int force)
{
	int fd, needed_chmod, rval;
	u_char byte;

	/* Try regular files and directories. */
	if (!S_ISREG(sbp->st_mode) && !S_ISDIR(sbp->st_mode)) {
		warnx("%s: %s", fname, strerror(0));
		return (1);
	}

	needed_chmod = rval = 0;
	if ((fd = _open(fname, O_RDWR, 0)) == -1) {
		if (!force || _chmod(fname, DEFFILEMODE))
			goto err;
		if ((fd = _open(fname, O_RDWR, 0)) == -1)
			goto err;
		needed_chmod = 1;
	}

	if (sbp->st_size != 0) {
		if (_read(fd, &byte, sizeof(byte)) != sizeof(byte))
			goto err;
		if (_lseek(fd, (off_t)0, SEEK_SET) == -1)
			goto err;
		if (_write(fd, &byte, sizeof(byte)) != sizeof(byte))
			goto err;
	} else {
		if (_write(fd, &byte, sizeof(byte)) != sizeof(byte)) {
err:			rval = 1;
			warn("%s", fname);
/*		} else if (ftruncate(fd, (off_t)0)) {*/
		} else if (_chsize(fd, (off_t)0)) {
			rval = 1;
			warn("%s: file modified", fname);
		}
	}

	if (_close(fd) && rval != 1) {
		rval = 1;
		warn("%s", fname);
	}
	if (needed_chmod && _chmod(fname, sbp->st_mode) && rval != 1) {
		rval = 1;
		warn("%s: permissions modified", fname);
	}
	return (rval);
}