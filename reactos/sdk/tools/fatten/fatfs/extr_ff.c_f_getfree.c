#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_8__ {int free_clust; int n_fatent; scalar_t__ fs_type; int fatbase; int fsi_flag; scalar_t__* win; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  scalar_t__ FRESULT ;
typedef  TYPE_1__ FATFS ;
typedef  int DWORD ;
typedef  scalar_t__ BYTE ;

/* Variables and functions */
 scalar_t__ FR_DISK_ERR ; 
 scalar_t__ FR_INT_ERR ; 
 scalar_t__ FR_OK ; 
 scalar_t__ FS_FAT12 ; 
 scalar_t__ FS_FAT16 ; 
 int LD_DWORD (scalar_t__*) ; 
 scalar_t__ LD_WORD (scalar_t__*) ; 
 int /*<<< orphan*/  LEAVE_FF (TYPE_1__*,scalar_t__) ; 
 scalar_t__ SS (TYPE_1__*) ; 
 scalar_t__ find_volume (TYPE_1__**,int /*<<< orphan*/  const**,int /*<<< orphan*/ ) ; 
 int get_fat (TYPE_1__*,int) ; 
 scalar_t__ move_window (TYPE_1__*,int /*<<< orphan*/ ) ; 

FRESULT f_getfree (
	const TCHAR* path,	/* Path name of the logical drive number */
	DWORD* nclst,		/* Pointer to a variable to return number of free clusters */
	FATFS** fatfs		/* Pointer to return pointer to corresponding file system object */
)
{
	FRESULT res;
	FATFS *fs;
	DWORD nfree, clst, sect, stat;
	UINT i;
	BYTE fat, *p;


	/* Get logical drive number */
	res = find_volume(fatfs, &path, 0);
	fs = *fatfs;
	if (res == FR_OK) {
		/* If free_clust is valid, return it without full cluster scan */
		if (fs->free_clust <= fs->n_fatent - 2) {
			*nclst = fs->free_clust;
		} else {
			/* Get number of free clusters */
			fat = fs->fs_type;
			nfree = 0;
			if (fat == FS_FAT12) {	/* Sector unalighed entries: Search FAT via regular routine. */
				clst = 2;
				do {
					stat = get_fat(fs, clst);
					if (stat == 0xFFFFFFFF) { res = FR_DISK_ERR; break; }
					if (stat == 1) { res = FR_INT_ERR; break; }
					if (stat == 0) nfree++;
				} while (++clst < fs->n_fatent);
			} else {				/* Sector alighed entries: Accelerate the FAT search. */
				clst = fs->n_fatent; sect = fs->fatbase;
				i = 0; p = 0;
				do {
					if (!i) {
						res = move_window(fs, sect++);
						if (res != FR_OK) break;
						p = fs->win;
						i = SS(fs);
					}
					if (fat == FS_FAT16) {
						if (LD_WORD(p) == 0) nfree++;
						p += 2; i -= 2;
					} else {
						if ((LD_DWORD(p) & 0x0FFFFFFF) == 0) nfree++;
						p += 4; i -= 4;
					}
				} while (--clst);
			}
			fs->free_clust = nfree;	/* free_clust is valid */
			fs->fsi_flag |= 1;		/* FSInfo is to be updated */
			*nclst = nfree;			/* Return the free clusters */
		}
	}
	LEAVE_FF(fs, res);
}