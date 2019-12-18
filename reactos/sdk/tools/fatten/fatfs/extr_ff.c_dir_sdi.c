#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WORD ;
typedef  int UINT ;
struct TYPE_7__ {int n_fatent; scalar_t__ fs_type; int dirbase; int n_rootdir; int csize; scalar_t__ win; } ;
struct TYPE_6__ {int sclust; int clust; int sect; TYPE_2__* fs; scalar_t__ dir; scalar_t__ index; } ;
typedef  int /*<<< orphan*/  FRESULT ;
typedef  int DWORD ;
typedef  TYPE_1__ DIR ;

/* Variables and functions */
 int /*<<< orphan*/  FR_DISK_ERR ; 
 int /*<<< orphan*/  FR_INT_ERR ; 
 int /*<<< orphan*/  FR_OK ; 
 scalar_t__ FS_FAT32 ; 
 int SS (TYPE_2__*) ; 
 int SZ_DIRE ; 
 int clust2sect (TYPE_2__*,int) ; 
 int get_fat (TYPE_2__*,int) ; 

__attribute__((used)) static
FRESULT dir_sdi (	/* FR_OK(0):succeeded, !=0:error */
	DIR* dp,		/* Pointer to directory object */
	UINT idx		/* Index of directory table */
)
{
	DWORD clst, sect;
	UINT ic;


	dp->index = (WORD)idx;	/* Current index */
	clst = dp->sclust;		/* Table start cluster (0:root) */
	if (clst == 1 || clst >= dp->fs->n_fatent)	/* Check start cluster range */
		return FR_INT_ERR;
	if (!clst && dp->fs->fs_type == FS_FAT32)	/* Replace cluster# 0 with root cluster# if in FAT32 */
		clst = dp->fs->dirbase;

	if (clst == 0) {	/* Static table (root-directory in FAT12/16) */
		if (idx >= dp->fs->n_rootdir)	/* Is index out of range? */
			return FR_INT_ERR;
		sect = dp->fs->dirbase;
	}
	else {				/* Dynamic table (root-directory in FAT32 or sub-directory) */
		ic = SS(dp->fs) / SZ_DIRE * dp->fs->csize;	/* Entries per cluster */
		while (idx >= ic) {	/* Follow cluster chain */
			clst = get_fat(dp->fs, clst);				/* Get next cluster */
			if (clst == 0xFFFFFFFF) return FR_DISK_ERR;	/* Disk error */
			if (clst < 2 || clst >= dp->fs->n_fatent)	/* Reached to end of table or internal error */
				return FR_INT_ERR;
			idx -= ic;
		}
		sect = clust2sect(dp->fs, clst);
	}
	dp->clust = clst;	/* Current cluster# */
	if (!sect) return FR_INT_ERR;
	dp->sect = sect + idx / (SS(dp->fs) / SZ_DIRE);					/* Sector# of the directory entry */
	dp->dir = dp->fs->win + (idx % (SS(dp->fs) / SZ_DIRE)) * SZ_DIRE;	/* Ptr to the entry in the sector */

	return FR_OK;
}