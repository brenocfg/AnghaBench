#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int lfn_idx; int* dir; int index; int* fn; scalar_t__ lfn; int /*<<< orphan*/  sect; int /*<<< orphan*/  fs; } ;
typedef  scalar_t__ FRESULT ;
typedef  TYPE_1__ DIR ;
typedef  int BYTE ;

/* Variables and functions */
 int AM_LFN ; 
 int AM_MASK ; 
 int AM_VOL ; 
 int DDEM ; 
 size_t DIR_Attr ; 
 size_t DIR_Name ; 
 scalar_t__ FR_NO_FILE ; 
 scalar_t__ FR_OK ; 
 size_t LDIR_Chksum ; 
 int LLEF ; 
 size_t NSFLAG ; 
 int NS_LOSS ; 
 scalar_t__ cmp_lfn (scalar_t__,int*) ; 
 scalar_t__ dir_next (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ dir_sdi (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mem_cmp (int*,int*,int) ; 
 scalar_t__ move_window (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sum_sfn (int*) ; 

__attribute__((used)) static
FRESULT dir_find (	/* FR_OK(0):succeeded, !=0:error */
	DIR* dp			/* Pointer to the directory object linked to the file name */
)
{
	FRESULT res;
	BYTE c, *dir;
#if _USE_LFN
	BYTE a, ord, sum;
#endif

	res = dir_sdi(dp, 0);			/* Rewind directory object */
	if (res != FR_OK) return res;

#if _USE_LFN
	ord = sum = 0xFF; dp->lfn_idx = 0xFFFF;	/* Reset LFN sequence */
#endif
	do {
		res = move_window(dp->fs, dp->sect);
		if (res != FR_OK) break;
		dir = dp->dir;					/* Ptr to the directory entry of current index */
		c = dir[DIR_Name];
		if (c == 0) { res = FR_NO_FILE; break; }	/* Reached to end of table */
#if _USE_LFN	/* LFN configuration */
		a = dir[DIR_Attr] & AM_MASK;
		if (c == DDEM || ((a & AM_VOL) && a != AM_LFN)) {	/* An entry without valid data */
			ord = 0xFF; dp->lfn_idx = 0xFFFF;	/* Reset LFN sequence */
		} else {
			if (a == AM_LFN) {			/* An LFN entry is found */
				if (dp->lfn) {
					if (c & LLEF) {		/* Is it start of LFN sequence? */
						sum = dir[LDIR_Chksum];
						c &= ~LLEF; ord = c;	/* LFN start order */
						dp->lfn_idx = dp->index;	/* Start index of LFN */
					}
					/* Check validity of the LFN entry and compare it with given name */
					ord = (c == ord && sum == dir[LDIR_Chksum] && cmp_lfn(dp->lfn, dir)) ? ord - 1 : 0xFF;
				}
			} else {					/* An SFN entry is found */
				if (!ord && sum == sum_sfn(dir)) break;	/* LFN matched? */
				if (!(dp->fn[NSFLAG] & NS_LOSS) && !mem_cmp(dir, dp->fn, 11)) break;	/* SFN matched? */
				ord = 0xFF; dp->lfn_idx = 0xFFFF;	/* Reset LFN sequence */
			}
		}
#else		/* Non LFN configuration */
		if (!(dir[DIR_Attr] & AM_VOL) && !mem_cmp(dir, dp->fn, 11)) /* Is it a valid entry? */
			break;
#endif
		res = dir_next(dp, 0);		/* Next entry */
	} while (res == FR_OK);

	return res;
}