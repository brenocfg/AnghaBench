#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ cdir; } ;
struct TYPE_15__ {int* fn; int* dir; TYPE_2__* fs; scalar_t__ sclust; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  scalar_t__ FRESULT ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_1__ DIR ;
typedef  int BYTE ;

/* Variables and functions */
 int AM_DIR ; 
 int AM_RDO ; 
 int /*<<< orphan*/  DEFINE_NAMEBUF ; 
 size_t DIR_Attr ; 
 int /*<<< orphan*/  FREE_BUF () ; 
 scalar_t__ FR_DENIED ; 
 scalar_t__ FR_INVALID_NAME ; 
 scalar_t__ FR_NO_FILE ; 
 scalar_t__ FR_OK ; 
 int /*<<< orphan*/  INIT_BUF (TYPE_1__) ; 
 int /*<<< orphan*/  LEAVE_FF (TYPE_2__*,scalar_t__) ; 
 size_t NSFLAG ; 
 int NS_DOT ; 
 scalar_t__ _FS_RPATH ; 
 scalar_t__ chk_lock (TYPE_1__*,int) ; 
 scalar_t__ dir_read (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ dir_remove (TYPE_1__*) ; 
 scalar_t__ dir_sdi (TYPE_1__*,int) ; 
 scalar_t__ find_volume (TYPE_2__**,int /*<<< orphan*/  const**,int) ; 
 scalar_t__ follow_path (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 scalar_t__ ld_clust (TYPE_2__*,int*) ; 
 int /*<<< orphan*/  mem_cpy (TYPE_1__*,TYPE_1__*,int) ; 
 scalar_t__ remove_chain (TYPE_2__*,scalar_t__) ; 
 scalar_t__ sync_fs (TYPE_2__*) ; 

FRESULT f_unlink (
	const TCHAR* path		/* Pointer to the file or directory path */
)
{
	FRESULT res;
	DIR dj, sdj;
	BYTE *dir;
	DWORD dclst = 0;
	DEFINE_NAMEBUF;


	/* Get logical drive number */
	res = find_volume(&dj.fs, &path, 1);
	if (res == FR_OK) {
		INIT_BUF(dj);
		res = follow_path(&dj, path);		/* Follow the file path */
		if (_FS_RPATH && res == FR_OK && (dj.fn[NSFLAG] & NS_DOT))
			res = FR_INVALID_NAME;			/* Cannot remove dot entry */
#if _FS_LOCK
		if (res == FR_OK) res = chk_lock(&dj, 2);	/* Cannot remove open object */
#endif
		if (res == FR_OK) {					/* The object is accessible */
			dir = dj.dir;
			if (!dir) {
				res = FR_INVALID_NAME;		/* Cannot remove the origin directory */
			} else {
				if (dir[DIR_Attr] & AM_RDO)
					res = FR_DENIED;		/* Cannot remove R/O object */
			}
			if (res == FR_OK) {
				dclst = ld_clust(dj.fs, dir);
				if (dclst && (dir[DIR_Attr] & AM_DIR)) {	/* Is it a sub-directory ? */
#if _FS_RPATH
					if (dclst == dj.fs->cdir) {		 		/* Is it the current directory? */
						res = FR_DENIED;
					} else
#endif
					{
						mem_cpy(&sdj, &dj, sizeof (DIR));	/* Open the sub-directory */
						sdj.sclust = dclst;
						res = dir_sdi(&sdj, 2);
						if (res == FR_OK) {
							res = dir_read(&sdj, 0);			/* Read an item (excluding dot entries) */
							if (res == FR_OK) res = FR_DENIED;	/* Not empty? (cannot remove) */
							if (res == FR_NO_FILE) res = FR_OK;	/* Empty? (can remove) */
						}
					}
				}
			}
			if (res == FR_OK) {
				res = dir_remove(&dj);		/* Remove the directory entry */
				if (res == FR_OK && dclst)	/* Remove the cluster chain if exist */
					res = remove_chain(dj.fs, dclst);
				if (res == FR_OK) res = sync_fs(dj.fs);
			}
		}
		FREE_BUF();
	}

	LEAVE_FF(dj.fs, res);
}