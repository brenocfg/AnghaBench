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
typedef  scalar_t__ WCHAR ;
typedef  int UINT ;
struct TYPE_9__ {int wflag; } ;
struct TYPE_8__ {int* fn; int* dir; TYPE_2__* fs; int /*<<< orphan*/  sect; scalar_t__* lfn; scalar_t__ index; } ;
typedef  scalar_t__ FRESULT ;
typedef  TYPE_1__ DIR ;
typedef  int BYTE ;

/* Variables and functions */
 size_t DIR_NTres ; 
 scalar_t__ FR_DENIED ; 
 scalar_t__ FR_INVALID_NAME ; 
 scalar_t__ FR_NO_FILE ; 
 scalar_t__ FR_OK ; 
 size_t NSFLAG ; 
 int NS_BODY ; 
 int NS_DOT ; 
 int NS_EXT ; 
 int NS_LFN ; 
 int NS_LOSS ; 
 int /*<<< orphan*/  SZ_DIRE ; 
 scalar_t__ _FS_RPATH ; 
 scalar_t__ dir_alloc (TYPE_1__*,int) ; 
 scalar_t__ dir_find (TYPE_1__*) ; 
 scalar_t__ dir_next (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ dir_sdi (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  fit_lfn (scalar_t__*,int*,int,int) ; 
 int /*<<< orphan*/  gen_numname (int*,int*,scalar_t__*,int) ; 
 int /*<<< orphan*/  mem_cpy (int*,int*,int) ; 
 int /*<<< orphan*/  mem_set (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ move_window (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int sum_sfn (int*) ; 

__attribute__((used)) static
FRESULT dir_register (	/* FR_OK:succeeded, FR_DENIED:no free entry or too many SFN collision, FR_DISK_ERR:disk error */
	DIR* dp				/* Target directory with object name to be created */
)
{
	FRESULT res;
#if _USE_LFN	/* LFN configuration */
	UINT n, nent;
	BYTE sn[12], *fn, sum;
	WCHAR *lfn;


	fn = dp->fn; lfn = dp->lfn;
	mem_cpy(sn, fn, 12);

	if (_FS_RPATH && (sn[NSFLAG] & NS_DOT))		/* Cannot create dot entry */
		return FR_INVALID_NAME;

	if (sn[NSFLAG] & NS_LOSS) {			/* When LFN is out of 8.3 format, generate a numbered name */
		fn[NSFLAG] = 0; dp->lfn = 0;			/* Find only SFN */
		for (n = 1; n < 100; n++) {
			gen_numname(fn, sn, lfn, n);	/* Generate a numbered name */
			res = dir_find(dp);				/* Check if the name collides with existing SFN */
			if (res != FR_OK) break;
		}
		if (n == 100) return FR_DENIED;		/* Abort if too many collisions */
		if (res != FR_NO_FILE) return res;	/* Abort if the result is other than 'not collided' */
		fn[NSFLAG] = sn[NSFLAG]; dp->lfn = lfn;
	}

	if (sn[NSFLAG] & NS_LFN) {			/* When LFN is to be created, allocate entries for an SFN + LFNs. */
		for (n = 0; lfn[n]; n++) ;
		nent = (n + 25) / 13;
	} else {						/* Otherwise allocate an entry for an SFN  */
		nent = 1;
	}
	res = dir_alloc(dp, nent);		/* Allocate entries */

	if (res == FR_OK && --nent) {	/* Set LFN entry if needed */
		res = dir_sdi(dp, dp->index - nent);
		if (res == FR_OK) {
			sum = sum_sfn(dp->fn);	/* Checksum value of the SFN tied to the LFN */
			do {					/* Store LFN entries in bottom first */
				res = move_window(dp->fs, dp->sect);
				if (res != FR_OK) break;
				fit_lfn(dp->lfn, dp->dir, (BYTE)nent, sum);
				dp->fs->wflag = 1;
				res = dir_next(dp, 0);	/* Next entry */
			} while (res == FR_OK && --nent);
		}
	}
#else	/* Non LFN configuration */
	res = dir_alloc(dp, 1);		/* Allocate an entry for SFN */
#endif

	if (res == FR_OK) {				/* Set SFN entry */
		res = move_window(dp->fs, dp->sect);
		if (res == FR_OK) {
			mem_set(dp->dir, 0, SZ_DIRE);	/* Clean the entry */
			mem_cpy(dp->dir, dp->fn, 11);	/* Put SFN */
#if _USE_LFN
			dp->dir[DIR_NTres] = dp->fn[NSFLAG] & (NS_BODY | NS_EXT);	/* Put NT flag */
#endif
			dp->fs->wflag = 1;
		}
	}

	return res;
}