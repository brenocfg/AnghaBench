#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int wflag; int /*<<< orphan*/  id; void* winsect; scalar_t__ last_clust; } ;
struct TYPE_15__ {int* dir; TYPE_3__* fs; } ;
struct TYPE_14__ {int* dir_ptr; int flag; TYPE_3__* fs; int /*<<< orphan*/  id; scalar_t__ cltbl; scalar_t__ dsect; scalar_t__ fptr; int /*<<< orphan*/  fsize; void* sclust; scalar_t__ err; int /*<<< orphan*/  lockid; void* dir_sect; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  scalar_t__ FRESULT ;
typedef  TYPE_1__ FIL ;
typedef  void* DWORD ;
typedef  TYPE_2__ DIR ;
typedef  int BYTE ;

/* Variables and functions */
 int AM_DIR ; 
 int AM_RDO ; 
 int /*<<< orphan*/  DEFINE_NAMEBUF ; 
 size_t DIR_Attr ; 
 int DIR_CrtTime ; 
 int DIR_FileSize ; 
 int DIR_WrtTime ; 
 int FA_CREATE_ALWAYS ; 
 int FA_CREATE_NEW ; 
 int FA_OPEN_ALWAYS ; 
 int FA_READ ; 
 int FA_WRITE ; 
 int FA__WRITTEN ; 
 int /*<<< orphan*/  FREE_BUF () ; 
 scalar_t__ FR_DENIED ; 
 scalar_t__ FR_EXIST ; 
 scalar_t__ FR_INT_ERR ; 
 scalar_t__ FR_INVALID_NAME ; 
 scalar_t__ FR_INVALID_OBJECT ; 
 scalar_t__ FR_NO_FILE ; 
 scalar_t__ FR_OK ; 
 scalar_t__ FR_TOO_MANY_OPEN_FILES ; 
 void* GET_FATTIME () ; 
 int /*<<< orphan*/  INIT_BUF (TYPE_2__) ; 
 int /*<<< orphan*/  LD_DWORD (int*) ; 
 int /*<<< orphan*/  LEAVE_FF (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  ST_DWORD (int*,void*) ; 
 scalar_t__ chk_lock (TYPE_2__*,int) ; 
 scalar_t__ dir_register (TYPE_2__*) ; 
 scalar_t__ enq_lock () ; 
 scalar_t__ find_volume (TYPE_3__**,int /*<<< orphan*/  const**,int) ; 
 scalar_t__ follow_path (TYPE_2__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  inc_lock (TYPE_2__*,int) ; 
 void* ld_clust (TYPE_3__*,int*) ; 
 scalar_t__ move_window (TYPE_3__*,void*) ; 
 scalar_t__ remove_chain (TYPE_3__*,void*) ; 
 int /*<<< orphan*/  st_clust (int*,int /*<<< orphan*/ ) ; 

FRESULT f_open (
	FIL* fp,			/* Pointer to the blank file object */
	const TCHAR* path,	/* Pointer to the file name */
	BYTE mode			/* Access mode and file open mode flags */
)
{
	FRESULT res;
	DIR dj;
	BYTE *dir;
	DEFINE_NAMEBUF;
#if !_FS_READONLY
	DWORD dw, cl;
#endif


	if (!fp) return FR_INVALID_OBJECT;
	fp->fs = 0;			/* Clear file object */

	/* Get logical drive number */
#if !_FS_READONLY
	mode &= FA_READ | FA_WRITE | FA_CREATE_ALWAYS | FA_OPEN_ALWAYS | FA_CREATE_NEW;
	res = find_volume(&dj.fs, &path, (BYTE)(mode & ~FA_READ));
#else
	mode &= FA_READ;
	res = find_volume(&dj.fs, &path, 0);
#endif
	if (res == FR_OK) {
		INIT_BUF(dj);
		res = follow_path(&dj, path);	/* Follow the file path */
		dir = dj.dir;
#if !_FS_READONLY	/* R/W configuration */
		if (res == FR_OK) {
			if (!dir)	/* Default directory itself */
				res = FR_INVALID_NAME;
#if _FS_LOCK
			else
				res = chk_lock(&dj, (mode & ~FA_READ) ? 1 : 0);
#endif
		}
		/* Create or Open a file */
		if (mode & (FA_CREATE_ALWAYS | FA_OPEN_ALWAYS | FA_CREATE_NEW)) {
			if (res != FR_OK) {					/* No file, create new */
				if (res == FR_NO_FILE)			/* There is no file to open, create a new entry */
#if _FS_LOCK
					res = enq_lock() ? dir_register(&dj) : FR_TOO_MANY_OPEN_FILES;
#else
					res = dir_register(&dj);
#endif
				mode |= FA_CREATE_ALWAYS;		/* File is created */
				dir = dj.dir;					/* New entry */
			}
			else {								/* Any object is already existing */
				if (dir[DIR_Attr] & (AM_RDO | AM_DIR)) {	/* Cannot overwrite it (R/O or DIR) */
					res = FR_DENIED;
				} else {
					if (mode & FA_CREATE_NEW)	/* Cannot create as new file */
						res = FR_EXIST;
				}
			}
			if (res == FR_OK && (mode & FA_CREATE_ALWAYS)) {	/* Truncate it if overwrite mode */
				dw = GET_FATTIME();
				ST_DWORD(dir + DIR_CrtTime, dw);/* Set created time */
				ST_DWORD(dir + DIR_WrtTime, dw);/* Set modified time */
				dir[DIR_Attr] = 0;				/* Reset attribute */
				ST_DWORD(dir + DIR_FileSize, 0);/* Reset file size */
				cl = ld_clust(dj.fs, dir);		/* Get cluster chain */
				st_clust(dir, 0);				/* Reset cluster */
				dj.fs->wflag = 1;
				if (cl) {						/* Remove the cluster chain if exist */
					dw = dj.fs->winsect;
					res = remove_chain(dj.fs, cl);
					if (res == FR_OK) {
						dj.fs->last_clust = cl - 1;	/* Reuse the cluster hole */
						res = move_window(dj.fs, dw);
					}
				}
			}
		}
		else {	/* Open an existing file */
			if (res == FR_OK) {					/* Following succeeded */
				if (dir[DIR_Attr] & AM_DIR) {	/* It is a directory */
					res = FR_NO_FILE;
				} else {
					if ((mode & FA_WRITE) && (dir[DIR_Attr] & AM_RDO)) /* R/O violation */
						res = FR_DENIED;
				}
			}
		}
		if (res == FR_OK) {
			if (mode & FA_CREATE_ALWAYS)		/* Set file change flag if created or overwritten */
				mode |= FA__WRITTEN;
			fp->dir_sect = dj.fs->winsect;		/* Pointer to the directory entry */
			fp->dir_ptr = dir;
#if _FS_LOCK
			fp->lockid = inc_lock(&dj, (mode & ~FA_READ) ? 1 : 0);
			if (!fp->lockid) res = FR_INT_ERR;
#endif
		}

#else				/* R/O configuration */
		if (res == FR_OK) {					/* Follow succeeded */
			dir = dj.dir;
			if (!dir) {						/* Current directory itself */
				res = FR_INVALID_NAME;
			} else {
				if (dir[DIR_Attr] & AM_DIR)	/* It is a directory */
					res = FR_NO_FILE;
			}
		}
#endif
		FREE_BUF();

		if (res == FR_OK) {
			fp->flag = mode;					/* File access mode */
			fp->err = 0;						/* Clear error flag */
			fp->sclust = ld_clust(dj.fs, dir);	/* File start cluster */
			fp->fsize = LD_DWORD(dir + DIR_FileSize);	/* File size */
			fp->fptr = 0;						/* File pointer */
			fp->dsect = 0;
#if _USE_FASTSEEK
			fp->cltbl = 0;						/* Normal seek mode */
#endif
			fp->fs = dj.fs;	 					/* Validate file object */
			fp->id = fp->fs->id;
		}
	}

	LEAVE_FF(dj.fs, res);
}