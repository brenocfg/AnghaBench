#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* dir; int lfn_idx; int index; scalar_t__ sect; int /*<<< orphan*/  lfn; int /*<<< orphan*/  fs; } ;
typedef  scalar_t__ FRESULT ;
typedef  TYPE_1__ DIR ;
typedef  char BYTE ;

/* Variables and functions */
 char AM_ARC ; 
 char AM_LFN ; 
 char AM_MASK ; 
 char AM_VOL ; 
 char DDEM ; 
 size_t DIR_Attr ; 
 size_t DIR_Name ; 
 scalar_t__ FR_NO_FILE ; 
 scalar_t__ FR_OK ; 
 size_t LDIR_Chksum ; 
 char LLEF ; 
 scalar_t__ _FS_RPATH ; 
 scalar_t__ dir_next (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ move_window (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ pick_lfn (int /*<<< orphan*/ ,char*) ; 
 char sum_sfn (char*) ; 

__attribute__((used)) static
FRESULT dir_read (
	DIR* dp,		/* Pointer to the directory object */
	int vol			/* Filtered by 0:file/directory or 1:volume label */
)
{
	FRESULT res;
	BYTE a, c, *dir;
#if _USE_LFN
	BYTE ord = 0xFF, sum = 0xFF;
#endif

	res = FR_NO_FILE;
	while (dp->sect) {
		res = move_window(dp->fs, dp->sect);
		if (res != FR_OK) break;
		dir = dp->dir;					/* Ptr to the directory entry of current index */
		c = dir[DIR_Name];
		if (c == 0) { res = FR_NO_FILE; break; }	/* Reached to end of table */
		a = dir[DIR_Attr] & AM_MASK;
#if _USE_LFN	/* LFN configuration */
		if (c == DDEM || (!_FS_RPATH && c == '.') || (int)((a & ~AM_ARC) == AM_VOL) != vol) {	/* An entry without valid data */
			ord = 0xFF;
		} else {
			if (a == AM_LFN) {			/* An LFN entry is found */
				if (c & LLEF) {			/* Is it start of LFN sequence? */
					sum = dir[LDIR_Chksum];
					c &= ~LLEF; ord = c;
					dp->lfn_idx = dp->index;
				}
				/* Check LFN validity and capture it */
				ord = (c == ord && sum == dir[LDIR_Chksum] && pick_lfn(dp->lfn, dir)) ? ord - 1 : 0xFF;
			} else {					/* An SFN entry is found */
				if (ord || sum != sum_sfn(dir))	/* Is there a valid LFN? */
					dp->lfn_idx = 0xFFFF;		/* It has no LFN. */
				break;
			}
		}
#else		/* Non LFN configuration */
		if (c != DDEM && (_FS_RPATH || c != '.') && a != AM_LFN && (int)((a & ~AM_ARC) == AM_VOL) == vol)	/* Is it a valid entry? */
			break;
#endif
		res = dir_next(dp, 0);				/* Next entry */
		if (res != FR_OK) break;
	}

	if (res != FR_OK) dp->sect = 0;

	return res;
}