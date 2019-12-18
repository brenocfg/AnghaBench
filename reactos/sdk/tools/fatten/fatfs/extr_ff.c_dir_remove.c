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
typedef  scalar_t__ UINT ;
struct TYPE_7__ {int wflag; } ;
struct TYPE_6__ {scalar_t__ index; int lfn_idx; TYPE_2__* fs; void** dir; int /*<<< orphan*/  sect; } ;
typedef  scalar_t__ FRESULT ;
typedef  TYPE_1__ DIR ;

/* Variables and functions */
 void* DDEM ; 
 scalar_t__ FR_INT_ERR ; 
 scalar_t__ FR_NO_FILE ; 
 scalar_t__ FR_OK ; 
 int /*<<< orphan*/  SZ_DIRE ; 
 scalar_t__ dir_next (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ dir_sdi (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  mem_set (void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ move_window (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
FRESULT dir_remove (	/* FR_OK:Succeeded, FR_DISK_ERR:A disk error */
	DIR* dp				/* Directory object pointing the entry to be removed */
)
{
	FRESULT res;
#if _USE_LFN	/* LFN configuration */
	UINT i;

	i = dp->index;	/* SFN index */
	res = dir_sdi(dp, (dp->lfn_idx == 0xFFFF) ? i : dp->lfn_idx);	/* Goto the SFN or top of the LFN entries */
	if (res == FR_OK) {
		do {
			res = move_window(dp->fs, dp->sect);
			if (res != FR_OK) break;
			mem_set(dp->dir, 0, SZ_DIRE);	/* Clear and mark the entry "deleted" */
			*dp->dir = DDEM;
			dp->fs->wflag = 1;
			if (dp->index >= i) break;	/* When reached SFN, all entries of the object has been deleted. */
			res = dir_next(dp, 0);		/* Next entry */
		} while (res == FR_OK);
		if (res == FR_NO_FILE) res = FR_INT_ERR;
	}

#else			/* Non LFN configuration */
	res = dir_sdi(dp, dp->index);
	if (res == FR_OK) {
		res = move_window(dp->fs, dp->sect);
		if (res == FR_OK) {
			mem_set(dp->dir, 0, SZ_DIRE);	/* Clear and mark the entry "deleted" */
			*dp->dir = DDEM;
			dp->fs->wflag = 1;
		}
	}
#endif

	return res;
}