#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int wflag; int /*<<< orphan*/  drv; } ;
struct TYPE_7__ {int flag; TYPE_3__* fs; int /*<<< orphan*/  sclust; int /*<<< orphan*/  fsize; int /*<<< orphan*/ * dir_ptr; int /*<<< orphan*/  dir_sect; int /*<<< orphan*/  dsect; int /*<<< orphan*/  buf; } ;
typedef  scalar_t__ FRESULT ;
typedef  TYPE_1__ FIL ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  AM_ARC ; 
 size_t DIR_Attr ; 
 int DIR_FileSize ; 
 int DIR_LstAccDate ; 
 int DIR_WrtTime ; 
 int FA__DIRTY ; 
 int FA__WRITTEN ; 
 scalar_t__ FR_DISK_ERR ; 
 scalar_t__ FR_OK ; 
 int /*<<< orphan*/  GET_FATTIME () ; 
 int /*<<< orphan*/  LEAVE_FF (TYPE_3__*,scalar_t__) ; 
 scalar_t__ RES_OK ; 
 int /*<<< orphan*/  ST_DWORD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ST_WORD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ disk_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ move_window (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st_clust (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sync_fs (TYPE_3__*) ; 
 scalar_t__ validate (TYPE_1__*) ; 

FRESULT f_sync (
	FIL* fp		/* Pointer to the file object */
)
{
	FRESULT res;
	DWORD tm;
	BYTE *dir;


	res = validate(fp);					/* Check validity of the object */
	if (res == FR_OK) {
		if (fp->flag & FA__WRITTEN) {	/* Is there any change to the file? */
#if !_FS_TINY
			if (fp->flag & FA__DIRTY) {	/* Write-back cached data if needed */
				if (disk_write(fp->fs->drv, fp->buf, fp->dsect, 1) != RES_OK)
					LEAVE_FF(fp->fs, FR_DISK_ERR);
				fp->flag &= ~FA__DIRTY;
			}
#endif
			/* Update the directory entry */
			res = move_window(fp->fs, fp->dir_sect);
			if (res == FR_OK) {
				dir = fp->dir_ptr;
				dir[DIR_Attr] |= AM_ARC;					/* Set archive bit */
				ST_DWORD(dir + DIR_FileSize, fp->fsize);	/* Update file size */
				st_clust(dir, fp->sclust);					/* Update start cluster */
				tm = GET_FATTIME();							/* Update modified time */
				ST_DWORD(dir + DIR_WrtTime, tm);
				ST_WORD(dir + DIR_LstAccDate, 0);
				fp->flag &= ~FA__WRITTEN;
				fp->fs->wflag = 1;
				res = sync_fs(fp->fs);
			}
		}
	}

	LEAVE_FF(fp->fs, res);
}