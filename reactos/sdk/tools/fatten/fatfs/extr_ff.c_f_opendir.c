#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int* dir; TYPE_1__* fs; scalar_t__ lockid; int /*<<< orphan*/  sclust; int /*<<< orphan*/  id; } ;
struct TYPE_11__ {int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  scalar_t__ FRESULT ;
typedef  TYPE_1__ FATFS ;
typedef  TYPE_2__ DIR ;

/* Variables and functions */
 int AM_DIR ; 
 int /*<<< orphan*/  DEFINE_NAMEBUF ; 
 size_t DIR_Attr ; 
 int /*<<< orphan*/  FREE_BUF () ; 
 scalar_t__ FR_INVALID_OBJECT ; 
 scalar_t__ FR_NO_FILE ; 
 scalar_t__ FR_NO_PATH ; 
 scalar_t__ FR_OK ; 
 scalar_t__ FR_TOO_MANY_OPEN_FILES ; 
 int /*<<< orphan*/  INIT_BUF (TYPE_2__) ; 
 int /*<<< orphan*/  LEAVE_FF (TYPE_1__*,scalar_t__) ; 
 scalar_t__ dir_sdi (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ find_volume (TYPE_1__**,int /*<<< orphan*/  const**,int /*<<< orphan*/ ) ; 
 scalar_t__ follow_path (TYPE_2__*,int /*<<< orphan*/  const*) ; 
 scalar_t__ inc_lock (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ld_clust (TYPE_1__*,int*) ; 

FRESULT f_opendir (
	DIR* dp,			/* Pointer to directory object to create */
	const TCHAR* path	/* Pointer to the directory path */
)
{
	FRESULT res;
	FATFS* fs;
	DEFINE_NAMEBUF;


	if (!dp) return FR_INVALID_OBJECT;

	/* Get logical drive number */
	res = find_volume(&fs, &path, 0);
	if (res == FR_OK) {
		dp->fs = fs;
		INIT_BUF(*dp);
		res = follow_path(dp, path);			/* Follow the path to the directory */
		FREE_BUF();
		if (res == FR_OK) {						/* Follow completed */
			if (dp->dir) {						/* It is not the origin directory itself */
				if (dp->dir[DIR_Attr] & AM_DIR)	/* The object is a sub directory */
					dp->sclust = ld_clust(fs, dp->dir);
				else							/* The object is a file */
					res = FR_NO_PATH;
			}
			if (res == FR_OK) {
				dp->id = fs->id;
				res = dir_sdi(dp, 0);			/* Rewind directory */
#if _FS_LOCK
				if (res == FR_OK) {
					if (dp->sclust) {
						dp->lockid = inc_lock(dp, 0);	/* Lock the sub directory */
						if (!dp->lockid)
							res = FR_TOO_MANY_OPEN_FILES;
					} else {
						dp->lockid = 0;	/* Root directory need not to be locked */
					}
				}
#endif
			}
		}
		if (res == FR_NO_FILE) res = FR_NO_PATH;
	}
	if (res != FR_OK) dp->fs = 0;		/* Invalidate the directory object if function faild */

	LEAVE_FF(fs, res);
}