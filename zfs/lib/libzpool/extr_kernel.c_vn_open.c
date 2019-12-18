#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int v_fd; int v_dump_fd; int /*<<< orphan*/  v_path; int /*<<< orphan*/  v_size; } ;
typedef  TYPE_1__ vnode_t ;
struct stat64 {int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int FCREAT ; 
 int /*<<< orphan*/  FD_CLOEXEC ; 
 int FREAD ; 
 int /*<<< orphan*/  F_SETFD ; 
 int MAXPATHLEN ; 
 int O_CREAT ; 
 int O_DIRECT ; 
 int O_WRONLY ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UMEM_NOFAIL ; 
 char* basename (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fstat64_blk (int,struct stat64*) ; 
 int open64 (char*,int,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  spa_strdup (char*) ; 
 int stat64 (char*,struct stat64*) ; 
 int umask (int) ; 
 int /*<<< orphan*/  umem_free (char*,int) ; 
 void* umem_zalloc (int,int /*<<< orphan*/ ) ; 
 char* vn_dumpdir ; 

int
vn_open(char *path, int x1, int flags, int mode, vnode_t **vpp, int x2, int x3)
{
	int fd = -1;
	int dump_fd = -1;
	vnode_t *vp;
	int old_umask = 0;
	struct stat64 st;
	int err;

	if (!(flags & FCREAT) && stat64(path, &st) == -1) {
		err = errno;
		return (err);
	}

	if (!(flags & FCREAT) && S_ISBLK(st.st_mode))
		flags |= O_DIRECT;

	if (flags & FCREAT)
		old_umask = umask(0);

	/*
	 * The construct 'flags - FREAD' conveniently maps combinations of
	 * FREAD and FWRITE to the corresponding O_RDONLY, O_WRONLY, and O_RDWR.
	 */
	fd = open64(path, flags - FREAD, mode);
	if (fd == -1) {
		err = errno;
		return (err);
	}

	if (flags & FCREAT)
		(void) umask(old_umask);

	if (vn_dumpdir != NULL) {
		char *dumppath = umem_zalloc(MAXPATHLEN, UMEM_NOFAIL);
		(void) snprintf(dumppath, MAXPATHLEN,
		    "%s/%s", vn_dumpdir, basename(path));
		dump_fd = open64(dumppath, O_CREAT | O_WRONLY, 0666);
		umem_free(dumppath, MAXPATHLEN);
		if (dump_fd == -1) {
			err = errno;
			close(fd);
			return (err);
		}
	} else {
		dump_fd = -1;
	}

	if (fstat64_blk(fd, &st) == -1) {
		err = errno;
		close(fd);
		if (dump_fd != -1)
			close(dump_fd);
		return (err);
	}

	(void) fcntl(fd, F_SETFD, FD_CLOEXEC);

	*vpp = vp = umem_zalloc(sizeof (vnode_t), UMEM_NOFAIL);

	vp->v_fd = fd;
	vp->v_size = st.st_size;
	vp->v_path = spa_strdup(path);
	vp->v_dump_fd = dump_fd;

	return (0);
}