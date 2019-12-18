#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int n_fatent; int free_clust; int fsi_flag; int csize; int /*<<< orphan*/  drv; } ;
typedef  scalar_t__ FRESULT ;
typedef  TYPE_1__ FATFS ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_TRIM ; 
 scalar_t__ FR_DISK_ERR ; 
 scalar_t__ FR_INT_ERR ; 
 scalar_t__ FR_OK ; 
 int clust2sect (TYPE_1__*,int) ; 
 int /*<<< orphan*/  disk_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int get_fat (TYPE_1__*,int) ; 
 scalar_t__ put_fat (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
FRESULT remove_chain (	/* FR_OK(0):succeeded, !=0:error */
	FATFS* fs,			/* File system object */
	DWORD clst			/* Cluster# to remove a chain from */
)
{
	FRESULT res;
	DWORD nxt;
#if _USE_TRIM
	DWORD scl = clst, ecl = clst, rt[2];
#endif

	if (clst < 2 || clst >= fs->n_fatent) {	/* Check if in valid range */
		res = FR_INT_ERR;

	} else {
		res = FR_OK;
		while (clst < fs->n_fatent) {			/* Not a last link? */
			nxt = get_fat(fs, clst);			/* Get cluster status */
			if (nxt == 0) break;				/* Empty cluster? */
			if (nxt == 1) { res = FR_INT_ERR; break; }	/* Internal error? */
			if (nxt == 0xFFFFFFFF) { res = FR_DISK_ERR; break; }	/* Disk error? */
			res = put_fat(fs, clst, 0);			/* Mark the cluster "empty" */
			if (res != FR_OK) break;
			if (fs->free_clust != 0xFFFFFFFF) {	/* Update FSINFO */
				fs->free_clust++;
				fs->fsi_flag |= 1;
			}
#if _USE_TRIM
			if (ecl + 1 == nxt) {	/* Is next cluster contiguous? */
				ecl = nxt;
			} else {				/* End of contiguous clusters */ 
				rt[0] = clust2sect(fs, scl);					/* Start sector */
				rt[1] = clust2sect(fs, ecl) + fs->csize - 1;	/* End sector */
				disk_ioctl(fs->drv, CTRL_TRIM, rt);				/* Erase the block */
				scl = ecl = nxt;
			}
#endif
			clst = nxt;	/* Next cluster */
		}
	}

	return res;
}