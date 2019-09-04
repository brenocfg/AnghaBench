#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int WORD ;
typedef  int UINT ;
struct TYPE_9__ {int n_rootdir; int csize; int n_fatent; int wflag; scalar_t__ win; void* winsect; } ;
struct TYPE_8__ {int index; int clust; TYPE_2__* fs; scalar_t__ dir; void* sect; } ;
typedef  int /*<<< orphan*/  FRESULT ;
typedef  int DWORD ;
typedef  TYPE_1__ DIR ;

/* Variables and functions */
 int /*<<< orphan*/  FR_DENIED ; 
 int /*<<< orphan*/  FR_DISK_ERR ; 
 int /*<<< orphan*/  FR_INT_ERR ; 
 int /*<<< orphan*/  FR_NO_FILE ; 
 int /*<<< orphan*/  FR_OK ; 
 int SS (TYPE_2__*) ; 
 int SZ_DIRE ; 
 void* clust2sect (TYPE_2__*,int) ; 
 int create_chain (TYPE_2__*,int) ; 
 int get_fat (TYPE_2__*,int) ; 
 int /*<<< orphan*/  mem_set (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sync_window (TYPE_2__*) ; 

__attribute__((used)) static
FRESULT dir_next (	/* FR_OK(0):succeeded, FR_NO_FILE:End of table, FR_DENIED:Could not stretch */
	DIR* dp,		/* Pointer to the directory object */
	int stretch		/* 0: Do not stretch table, 1: Stretch table if needed */
)
{
	DWORD clst;
	UINT i;
#if !_FS_READONLY
	UINT c;
#endif


	i = dp->index + 1;
	if (!(i & 0xFFFF) || !dp->sect)	/* Report EOT when index has reached 65535 */
		return FR_NO_FILE;

	if (!(i % (SS(dp->fs) / SZ_DIRE))) {	/* Sector changed? */
		dp->sect++;					/* Next sector */

		if (!dp->clust) {		/* Static table */
			if (i >= dp->fs->n_rootdir)	/* Report EOT if it reached end of static table */
				return FR_NO_FILE;
		}
		else {					/* Dynamic table */
			if (((i / (SS(dp->fs) / SZ_DIRE)) & (dp->fs->csize - 1)) == 0) {	/* Cluster changed? */
				clst = get_fat(dp->fs, dp->clust);				/* Get next cluster */
				if (clst <= 1) return FR_INT_ERR;
				if (clst == 0xFFFFFFFF) return FR_DISK_ERR;
				if (clst >= dp->fs->n_fatent) {					/* If it reached end of dynamic table, */
#if !_FS_READONLY
					if (!stretch) return FR_NO_FILE;			/* If do not stretch, report EOT */
					clst = create_chain(dp->fs, dp->clust);		/* Stretch cluster chain */
					if (clst == 0) return FR_DENIED;			/* No free cluster */
					if (clst == 1) return FR_INT_ERR;
					if (clst == 0xFFFFFFFF) return FR_DISK_ERR;
					/* Clean-up stretched table */
					if (sync_window(dp->fs)) return FR_DISK_ERR;/* Flush disk access window */
					mem_set(dp->fs->win, 0, SS(dp->fs));		/* Clear window buffer */
					dp->fs->winsect = clust2sect(dp->fs, clst);	/* Cluster start sector */
					for (c = 0; c < dp->fs->csize; c++) {		/* Fill the new cluster with 0 */
						dp->fs->wflag = 1;
						if (sync_window(dp->fs)) return FR_DISK_ERR;
						dp->fs->winsect++;
					}
					dp->fs->winsect -= c;						/* Rewind window offset */
#else
					if (!stretch) return FR_NO_FILE;			/* If do not stretch, report EOT (this is to suppress warning) */
					return FR_NO_FILE;							/* Report EOT */
#endif
				}
				dp->clust = clst;				/* Initialize data for new cluster */
				dp->sect = clust2sect(dp->fs, clst);
			}
		}
	}

	dp->index = (WORD)i;	/* Current index */
	dp->dir = dp->fs->win + (i % (SS(dp->fs) / SZ_DIRE)) * SZ_DIRE;	/* Current entry in the window */

	return FR_OK;
}