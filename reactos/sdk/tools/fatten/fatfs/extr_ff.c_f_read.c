#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_12__ {int csize; scalar_t__ winsect; scalar_t__* win; int /*<<< orphan*/  drv; scalar_t__ wflag; } ;
struct TYPE_11__ {int flag; scalar_t__ fsize; scalar_t__ fptr; scalar_t__ sclust; scalar_t__ dsect; scalar_t__* buf; TYPE_3__* fs; scalar_t__ clust; scalar_t__ cltbl; scalar_t__ err; } ;
typedef  scalar_t__ FRESULT ;
typedef  TYPE_1__ FIL ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ABORT (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int FA_READ ; 
 int FA__DIRTY ; 
 scalar_t__ FR_DENIED ; 
 int /*<<< orphan*/  FR_DISK_ERR ; 
 int /*<<< orphan*/  FR_INT_ERR ; 
 scalar_t__ FR_OK ; 
 int /*<<< orphan*/  LEAVE_FF (TYPE_3__*,scalar_t__) ; 
 scalar_t__ RES_OK ; 
 size_t SS (TYPE_3__*) ; 
 scalar_t__ clmt_clust (TYPE_1__*,int) ; 
 scalar_t__ clust2sect (TYPE_3__*,scalar_t__) ; 
 scalar_t__ disk_read (int /*<<< orphan*/ ,scalar_t__*,scalar_t__,int) ; 
 scalar_t__ disk_write (int /*<<< orphan*/ ,scalar_t__*,scalar_t__,int) ; 
 scalar_t__ get_fat (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  mem_cpy (scalar_t__*,scalar_t__*,scalar_t__) ; 
 scalar_t__ move_window (TYPE_3__*,scalar_t__) ; 
 scalar_t__ validate (TYPE_1__*) ; 

FRESULT f_read (
	FIL* fp, 		/* Pointer to the file object */
	void* buff,		/* Pointer to data buffer */
	UINT btr,		/* Number of bytes to read */
	UINT* br		/* Pointer to number of bytes read */
)
{
	FRESULT res;
	DWORD clst, sect, remain;
	UINT rcnt, cc;
	BYTE csect, *rbuff = (BYTE*)buff;


	*br = 0;	/* Clear read byte counter */

	res = validate(fp);							/* Check validity */
	if (res != FR_OK) LEAVE_FF(fp->fs, res);
	if (fp->err)								/* Check error */
		LEAVE_FF(fp->fs, (FRESULT)fp->err);
	if (!(fp->flag & FA_READ)) 					/* Check access mode */
		LEAVE_FF(fp->fs, FR_DENIED);
	remain = fp->fsize - fp->fptr;
	if (btr > remain) btr = (UINT)remain;		/* Truncate btr by remaining bytes */

	for ( ;  btr;								/* Repeat until all data read */
		rbuff += rcnt, fp->fptr += rcnt, *br += rcnt, btr -= rcnt) {
		if ((fp->fptr % SS(fp->fs)) == 0) {		/* On the sector boundary? */
			csect = (BYTE)(fp->fptr / SS(fp->fs) & (fp->fs->csize - 1));	/* Sector offset in the cluster */
			if (!csect) {						/* On the cluster boundary? */
				if (fp->fptr == 0) {			/* On the top of the file? */
					clst = fp->sclust;			/* Follow from the origin */
				} else {						/* Middle or end of the file */
#if _USE_FASTSEEK
					if (fp->cltbl)
						clst = clmt_clust(fp, fp->fptr);	/* Get cluster# from the CLMT */
					else
#endif
						clst = get_fat(fp->fs, fp->clust);	/* Follow cluster chain on the FAT */
				}
				if (clst < 2) ABORT(fp->fs, FR_INT_ERR);
				if (clst == 0xFFFFFFFF) ABORT(fp->fs, FR_DISK_ERR);
				fp->clust = clst;				/* Update current cluster */
			}
			sect = clust2sect(fp->fs, fp->clust);	/* Get current sector */
			if (!sect) ABORT(fp->fs, FR_INT_ERR);
			sect += csect;
			cc = btr / SS(fp->fs);				/* When remaining bytes >= sector size, */
			if (cc) {							/* Read maximum contiguous sectors directly */
				if (csect + cc > fp->fs->csize)	/* Clip at cluster boundary */
					cc = fp->fs->csize - csect;
				if (disk_read(fp->fs->drv, rbuff, sect, cc) != RES_OK)
					ABORT(fp->fs, FR_DISK_ERR);
#if !_FS_READONLY && _FS_MINIMIZE <= 2			/* Replace one of the read sectors with cached data if it contains a dirty sector */
#if _FS_TINY
				if (fp->fs->wflag && fp->fs->winsect - sect < cc)
					mem_cpy(rbuff + ((fp->fs->winsect - sect) * SS(fp->fs)), fp->fs->win, SS(fp->fs));
#else
				if ((fp->flag & FA__DIRTY) && fp->dsect - sect < cc)
					mem_cpy(rbuff + ((fp->dsect - sect) * SS(fp->fs)), fp->buf, SS(fp->fs));
#endif
#endif
				rcnt = SS(fp->fs) * cc;			/* Number of bytes transferred */
				continue;
			}
#if !_FS_TINY
			if (fp->dsect != sect) {			/* Load data sector if not in cache */
#if !_FS_READONLY
				if (fp->flag & FA__DIRTY) {		/* Write-back dirty sector cache */
					if (disk_write(fp->fs->drv, fp->buf, fp->dsect, 1) != RES_OK)
						ABORT(fp->fs, FR_DISK_ERR);
					fp->flag &= ~FA__DIRTY;
				}
#endif
				if (disk_read(fp->fs->drv, fp->buf, sect, 1) != RES_OK)	/* Fill sector cache */
					ABORT(fp->fs, FR_DISK_ERR);
			}
#endif
			fp->dsect = sect;
		}
		rcnt = SS(fp->fs) - ((UINT)fp->fptr % SS(fp->fs));	/* Get partial sector data from sector buffer */
		if (rcnt > btr) rcnt = btr;
#if _FS_TINY
		if (move_window(fp->fs, fp->dsect) != FR_OK)		/* Move sector window */
			ABORT(fp->fs, FR_DISK_ERR);
		mem_cpy(rbuff, &fp->fs->win[fp->fptr % SS(fp->fs)], rcnt);	/* Pick partial sector */
#else
		mem_cpy(rbuff, &fp->buf[fp->fptr % SS(fp->fs)], rcnt);	/* Pick partial sector */
#endif
	}

	LEAVE_FF(fp->fs, FR_OK);
}