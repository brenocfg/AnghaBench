#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int WORD ;
typedef  int UINT ;
struct TYPE_9__ {int fs_type; int* win; int fsize; int n_fats; int csize; int n_rootdir; int n_fatent; int volbase; int fatbase; int database; int dirbase; int last_clust; int free_clust; int fsi_flag; scalar_t__ cdir; scalar_t__ id; int /*<<< orphan*/  drv; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  scalar_t__ FRESULT ;
typedef  TYPE_1__ FATFS ;
typedef  int DWORD ;
typedef  int DSTATUS ;
typedef  int BYTE ;

/* Variables and functions */
 int BPB_BytsPerSec ; 
 int BPB_FATSz16 ; 
 int BPB_FATSz32 ; 
 int BPB_FSInfo ; 
 size_t BPB_NumFATs ; 
 int BPB_RootClus ; 
 int BPB_RootEntCnt ; 
 int BPB_RsvdSecCnt ; 
 size_t BPB_SecPerClus ; 
 int BPB_TotSec16 ; 
 int BPB_TotSec32 ; 
 int BS_55AA ; 
 int /*<<< orphan*/  ENTER_FF (TYPE_1__*) ; 
 scalar_t__ FR_DISK_ERR ; 
 scalar_t__ FR_INVALID_DRIVE ; 
 scalar_t__ FR_NOT_ENABLED ; 
 scalar_t__ FR_NOT_READY ; 
 scalar_t__ FR_NO_FILESYSTEM ; 
 scalar_t__ FR_OK ; 
 scalar_t__ FR_WRITE_PROTECTED ; 
 int FSI_Free_Count ; 
 int FSI_LeadSig ; 
 int FSI_Nxt_Free ; 
 int FSI_StrucSig ; 
 int FS_FAT12 ; 
 int FS_FAT16 ; 
 int FS_FAT32 ; 
 TYPE_1__** FatFs ; 
 scalar_t__ Fsid ; 
 int /*<<< orphan*/  GET_SECTOR_SIZE ; 
 int /*<<< orphan*/  LD2PD (int) ; 
 int LD2PT (int) ; 
 int LD_DWORD (int*) ; 
 int LD_WORD (int*) ; 
 int MBR_Table ; 
 int MIN_FAT16 ; 
 int MIN_FAT32 ; 
 scalar_t__ RES_OK ; 
 int SS (TYPE_1__*) ; 
 int STA_NOINIT ; 
 int STA_PROTECT ; 
 int SZ_DIRE ; 
 int SZ_PTE ; 
 int /*<<< orphan*/  _FS_READONLY ; 
 int _MAX_SS ; 
 int _MIN_SS ; 
 int check_fs (TYPE_1__*,int) ; 
 int /*<<< orphan*/  clear_lock (TYPE_1__*) ; 
 int disk_initialize (int /*<<< orphan*/ ) ; 
 scalar_t__ disk_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int disk_status (int /*<<< orphan*/ ) ; 
 int get_ldnumber (int /*<<< orphan*/  const**) ; 
 scalar_t__ move_window (TYPE_1__*,int) ; 

__attribute__((used)) static
FRESULT find_volume (	/* FR_OK(0): successful, !=0: any error occurred */
	FATFS** rfs,		/* Pointer to pointer to the found file system object */
	const TCHAR** path,	/* Pointer to pointer to the path name (drive number) */
	BYTE wmode			/* !=0: Check write protection for write access */
)
{
	BYTE fmt, *pt;
	int vol;
	DSTATUS stat;
	DWORD bsect, fasize, tsect, sysect, nclst, szbfat, br[4];
	WORD nrsv;
	FATFS *fs;
	UINT i;


	/* Get logical drive number from the path name */
	*rfs = 0;
	vol = get_ldnumber(path);
	if (vol < 0) return FR_INVALID_DRIVE;

	/* Check if the file system object is valid or not */
	fs = FatFs[vol];					/* Get pointer to the file system object */
	if (!fs) return FR_NOT_ENABLED;		/* Is the file system object available? */

	ENTER_FF(fs);						/* Lock the volume */
	*rfs = fs;							/* Return pointer to the file system object */

	if (fs->fs_type) {					/* If the volume has been mounted */
		stat = disk_status(fs->drv);
		if (!(stat & STA_NOINIT)) {		/* and the physical drive is kept initialized */
			if (!_FS_READONLY && wmode && (stat & STA_PROTECT))	/* Check write protection if needed */
				return FR_WRITE_PROTECTED;
			return FR_OK;				/* The file system object is valid */
		}
	}

	/* The file system object is not valid. */
	/* Following code attempts to mount the volume. (analyze BPB and initialize the fs object) */

	fs->fs_type = 0;					/* Clear the file system object */
	fs->drv = LD2PD(vol);				/* Bind the logical drive and a physical drive */
	stat = disk_initialize(fs->drv);	/* Initialize the physical drive */
	if (stat & STA_NOINIT)				/* Check if the initialization succeeded */
		return FR_NOT_READY;			/* Failed to initialize due to no medium or hard error */
	if (!_FS_READONLY && wmode && (stat & STA_PROTECT))	/* Check disk write protection if needed */
		return FR_WRITE_PROTECTED;
#if _MAX_SS != _MIN_SS						/* Get sector size (multiple sector size cfg only) */
	if (disk_ioctl(fs->drv, GET_SECTOR_SIZE, &SS(fs)) != RES_OK
		|| SS(fs) < _MIN_SS || SS(fs) > _MAX_SS) return FR_DISK_ERR;
#endif
	/* Find an FAT partition on the drive. Supports only generic partitioning, FDISK and SFD. */
	bsect = 0;
	fmt = check_fs(fs, bsect);					/* Load sector 0 and check if it is an FAT boot sector as SFD */
	if (fmt == 1 || (!fmt && (LD2PT(vol)))) {	/* Not an FAT boot sector or forced partition number */
		for (i = 0; i < 4; i++) {			/* Get partition offset */
			pt = fs->win + MBR_Table + i * SZ_PTE;
			br[i] = pt[4] ? LD_DWORD(&pt[8]) : 0;
		}
		i = LD2PT(vol);						/* Partition number: 0:auto, 1-4:forced */
		if (i) i--;
		do {								/* Find an FAT volume */
			bsect = br[i];
			fmt = bsect ? check_fs(fs, bsect) : 2;	/* Check the partition */
		} while (!LD2PT(vol) && fmt && ++i < 4);
	}
	if (fmt == 3) return FR_DISK_ERR;		/* An error occured in the disk I/O layer */
	if (fmt) return FR_NO_FILESYSTEM;		/* No FAT volume is found */

	/* An FAT volume is found. Following code initializes the file system object */

	if (LD_WORD(fs->win + BPB_BytsPerSec) != SS(fs))	/* (BPB_BytsPerSec must be equal to the physical sector size) */
		return FR_NO_FILESYSTEM;

	fasize = LD_WORD(fs->win + BPB_FATSz16);			/* Number of sectors per FAT */
	if (!fasize) fasize = LD_DWORD(fs->win + BPB_FATSz32);
	fs->fsize = fasize;

	fs->n_fats = fs->win[BPB_NumFATs];					/* Number of FAT copies */
	if (fs->n_fats != 1 && fs->n_fats != 2)				/* (Must be 1 or 2) */
		return FR_NO_FILESYSTEM;
	fasize *= fs->n_fats;								/* Number of sectors for FAT area */

	fs->csize = fs->win[BPB_SecPerClus];				/* Number of sectors per cluster */
	if (!fs->csize || (fs->csize & (fs->csize - 1)))	/* (Must be power of 2) */
		return FR_NO_FILESYSTEM;

	fs->n_rootdir = LD_WORD(fs->win + BPB_RootEntCnt);	/* Number of root directory entries */
	if (fs->n_rootdir % (SS(fs) / SZ_DIRE))				/* (Must be sector aligned) */
		return FR_NO_FILESYSTEM;

	tsect = LD_WORD(fs->win + BPB_TotSec16);			/* Number of sectors on the volume */
	if (!tsect) tsect = LD_DWORD(fs->win + BPB_TotSec32);

	nrsv = LD_WORD(fs->win + BPB_RsvdSecCnt);			/* Number of reserved sectors */
	if (!nrsv) return FR_NO_FILESYSTEM;					/* (Must not be 0) */

	/* Determine the FAT sub type */
	sysect = nrsv + fasize + fs->n_rootdir / (SS(fs) / SZ_DIRE);	/* RSV + FAT + DIR */
	if (tsect < sysect) return FR_NO_FILESYSTEM;		/* (Invalid volume size) */
	nclst = (tsect - sysect) / fs->csize;				/* Number of clusters */
	if (!nclst) return FR_NO_FILESYSTEM;				/* (Invalid volume size) */
	fmt = FS_FAT12;
	if (nclst >= MIN_FAT16) fmt = FS_FAT16;
	if (nclst >= MIN_FAT32) fmt = FS_FAT32;

	/* Boundaries and Limits */
	fs->n_fatent = nclst + 2;							/* Number of FAT entries */
	fs->volbase = bsect;								/* Volume start sector */
	fs->fatbase = bsect + nrsv; 						/* FAT start sector */
	fs->database = bsect + sysect;						/* Data start sector */
	if (fmt == FS_FAT32) {
		if (fs->n_rootdir) return FR_NO_FILESYSTEM;		/* (BPB_RootEntCnt must be 0) */
		fs->dirbase = LD_DWORD(fs->win + BPB_RootClus);	/* Root directory start cluster */
		szbfat = fs->n_fatent * 4;						/* (Needed FAT size) */
	} else {
		if (!fs->n_rootdir)	return FR_NO_FILESYSTEM;	/* (BPB_RootEntCnt must not be 0) */
		fs->dirbase = fs->fatbase + fasize;				/* Root directory start sector */
		szbfat = (fmt == FS_FAT16) ?					/* (Needed FAT size) */
			fs->n_fatent * 2 : fs->n_fatent * 3 / 2 + (fs->n_fatent & 1);
	}
	if (fs->fsize < (szbfat + (SS(fs) - 1)) / SS(fs))	/* (BPB_FATSz must not be less than the size needed) */
		return FR_NO_FILESYSTEM;

#if !_FS_READONLY
	/* Initialize cluster allocation information */
	fs->last_clust = fs->free_clust = 0xFFFFFFFF;

	/* Get fsinfo if available */
	fs->fsi_flag = 0x80;
#if (_FS_NOFSINFO & 3) != 3
	if (fmt == FS_FAT32				/* Enable FSINFO only if FAT32 and BPB_FSInfo == 1 */
		&& LD_WORD(fs->win + BPB_FSInfo) == 1
		&& move_window(fs, bsect + 1) == FR_OK)
	{
		fs->fsi_flag = 0;
		if (LD_WORD(fs->win + BS_55AA) == 0xAA55	/* Load FSINFO data if available */
			&& LD_DWORD(fs->win + FSI_LeadSig) == 0x41615252
			&& LD_DWORD(fs->win + FSI_StrucSig) == 0x61417272)
		{
#if (_FS_NOFSINFO & 1) == 0
			fs->free_clust = LD_DWORD(fs->win + FSI_Free_Count);
#endif
#if (_FS_NOFSINFO & 2) == 0
			fs->last_clust = LD_DWORD(fs->win + FSI_Nxt_Free);
#endif
		}
	}
#endif
#endif
	fs->fs_type = fmt;	/* FAT sub-type */
	fs->id = ++Fsid;	/* File system mount ID */
#if _FS_RPATH
	fs->cdir = 0;		/* Set current directory to root */
#endif
#if _FS_LOCK			/* Clear file lock semaphores */
	clear_lock(fs);
#endif

	return FR_OK;
}