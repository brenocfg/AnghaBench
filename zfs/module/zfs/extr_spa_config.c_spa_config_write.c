#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vnode_t ;
struct TYPE_4__ {char* scd_path; } ;
typedef  TYPE_1__ spa_config_dirent_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  CRCREAT ; 
 int ENOENT ; 
 int FCREAT ; 
 int FOFFMAX ; 
 int /*<<< orphan*/  FSYNC ; 
 int FTRUNC ; 
 int FWRITE ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  MAXPATHLEN ; 
 int /*<<< orphan*/  RLIM64_INFINITY ; 
 int /*<<< orphan*/  RMFILE ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  UIO_WRITE ; 
 int /*<<< orphan*/  VOP_CLOSE (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int VOP_FSYNC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* fnvlist_pack (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  fnvlist_pack_free (char*,size_t) ; 
 int /*<<< orphan*/  kcred ; 
 int /*<<< orphan*/  kmem_free (char*,int /*<<< orphan*/ ) ; 
 char* kmem_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 
 int spa_config_remove (TYPE_1__*) ; 
 int vn_open (char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vn_rdwr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vn_remove (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vn_rename (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
spa_config_write(spa_config_dirent_t *dp, nvlist_t *nvl)
{
	size_t buflen;
	char *buf;
	vnode_t *vp;
	int oflags = FWRITE | FTRUNC | FCREAT | FOFFMAX;
	char *temp;
	int err;

	/*
	 * If the nvlist is empty (NULL), then remove the old cachefile.
	 */
	if (nvl == NULL) {
		err = spa_config_remove(dp);
		if (err == ENOENT)
			err = 0;

		return (err);
	}

	/*
	 * Pack the configuration into a buffer.
	 */
	buf = fnvlist_pack(nvl, &buflen);
	temp = kmem_zalloc(MAXPATHLEN, KM_SLEEP);

#if defined(__linux__) && defined(_KERNEL)
	/*
	 * Write the configuration to disk.  Due to the complexity involved
	 * in performing a rename and remove from within the kernel the file
	 * is instead truncated and overwritten in place.  This way we always
	 * have a consistent view of the data or a zero length file.
	 */
	err = vn_open(dp->scd_path, UIO_SYSSPACE, oflags, 0644, &vp, 0, 0);
	if (err == 0) {
		err = vn_rdwr(UIO_WRITE, vp, buf, buflen, 0,
		    UIO_SYSSPACE, 0, RLIM64_INFINITY, kcred, NULL);
		if (err == 0)
			err = VOP_FSYNC(vp, FSYNC, kcred, NULL);

		(void) VOP_CLOSE(vp, oflags, 1, 0, kcred, NULL);
		if (err)
			(void) spa_config_remove(dp);
	}
#else
	/*
	 * Write the configuration to disk.  We need to do the traditional
	 * 'write to temporary file, sync, move over original' to make sure we
	 * always have a consistent view of the data.
	 */
	(void) snprintf(temp, MAXPATHLEN, "%s.tmp", dp->scd_path);

	err = vn_open(temp, UIO_SYSSPACE, oflags, 0644, &vp, CRCREAT, 0);
	if (err == 0) {
		err = vn_rdwr(UIO_WRITE, vp, buf, buflen, 0, UIO_SYSSPACE,
		    0, RLIM64_INFINITY, kcred, NULL);
		if (err == 0)
			err = VOP_FSYNC(vp, FSYNC, kcred, NULL);
		if (err == 0)
			err = vn_rename(temp, dp->scd_path, UIO_SYSSPACE);
		(void) VOP_CLOSE(vp, oflags, 1, 0, kcred, NULL);
	}

	(void) vn_remove(temp, UIO_SYSSPACE, RMFILE);
#endif

	fnvlist_pack_free(buf, buflen);
	kmem_free(temp, MAXPATHLEN);
	return (err);
}