#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  sobj; scalar_t__ fs_type; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/  FRESULT ;
typedef  TYPE_1__ FATFS ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  FR_INT_ERR ; 
 int /*<<< orphan*/  FR_INVALID_DRIVE ; 
 int /*<<< orphan*/  FR_OK ; 
 TYPE_1__** FatFs ; 
 int /*<<< orphan*/  LEAVE_FF (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  ff_cre_syncobj (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_del_syncobj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_volume (TYPE_1__**,int /*<<< orphan*/  const**,int /*<<< orphan*/ ) ; 
 int get_ldnumber (int /*<<< orphan*/  const**) ; 

FRESULT f_mount (
	FATFS* fs,			/* Pointer to the file system object (NULL:unmount)*/
	const TCHAR* path,	/* Logical drive number to be mounted/unmounted */
	BYTE opt			/* 0:Do not mount (delayed mount), 1:Mount immediately */
)
{
	FATFS *cfs;
	int vol;
	FRESULT res;
	const TCHAR *rp = path;


	vol = get_ldnumber(&rp);
	if (vol < 0) return FR_INVALID_DRIVE;
	cfs = FatFs[vol];					/* Pointer to fs object */

	if (cfs) {
#if _FS_LOCK
		clear_lock(cfs);
#endif
#if _FS_REENTRANT						/* Discard sync object of the current volume */
		if (!ff_del_syncobj(cfs->sobj)) return FR_INT_ERR;
#endif
		cfs->fs_type = 0;				/* Clear old fs object */
	}

	if (fs) {
		fs->fs_type = 0;				/* Clear new fs object */
#if _FS_REENTRANT						/* Create sync object for the new volume */
		if (!ff_cre_syncobj((BYTE)vol, &fs->sobj)) return FR_INT_ERR;
#endif
	}
	FatFs[vol] = fs;					/* Register new fs object */

	if (!fs || opt != 1) return FR_OK;	/* Do not mount now, it will be mounted later */

	res = find_volume(&fs, &path, 0);	/* Force mounted the volume */
	LEAVE_FF(fs, res);
}