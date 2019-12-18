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
typedef  int WCHAR ;
typedef  size_t UINT ;
struct TYPE_9__ {int wflag; } ;
struct TYPE_8__ {int* dir; TYPE_2__* fs; scalar_t__ sclust; } ;
typedef  char TCHAR ;
typedef  scalar_t__ FRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_1__ DIR ;
typedef  int BYTE ;

/* Variables and functions */
 int AM_VOL ; 
 int DDEM ; 
 size_t DIR_Attr ; 
 int DIR_CrtTime ; 
 int DIR_WrtTime ; 
 int* ExCvt ; 
 scalar_t__ FR_INVALID_NAME ; 
 scalar_t__ FR_NO_FILE ; 
 scalar_t__ FR_OK ; 
 int /*<<< orphan*/  GET_FATTIME () ; 
 scalar_t__ IsDBCS1 (int) ; 
 scalar_t__ IsDBCS2 (char const) ; 
 scalar_t__ IsLower (int) ; 
 int /*<<< orphan*/  LEAVE_FF (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  ST_DWORD (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZ_DIRE ; 
 int /*<<< orphan*/  _DF1S ; 
 scalar_t__ chk_chr (char*,int) ; 
 scalar_t__ dir_alloc (TYPE_1__*,int) ; 
 scalar_t__ dir_read (TYPE_1__*,int) ; 
 scalar_t__ dir_sdi (TYPE_1__*,int /*<<< orphan*/ ) ; 
 char const ff_convert (int,int) ; 
 int ff_wtoupper (char const) ; 
 scalar_t__ find_volume (TYPE_2__**,char const**,int) ; 
 int /*<<< orphan*/  mem_cpy (int*,int*,int) ; 
 int /*<<< orphan*/  mem_set (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sync_fs (TYPE_2__*) ; 

FRESULT f_setlabel (
	const TCHAR* label	/* Pointer to the volume label to set */
)
{
	FRESULT res;
	DIR dj;
	BYTE vn[11];
	UINT i, j, sl;
	WCHAR w;
	DWORD tm;


	/* Get logical drive number */
	res = find_volume(&dj.fs, &label, 1);
	if (res) LEAVE_FF(dj.fs, res);

	/* Create a volume label in directory form */
	vn[0] = 0;
	for (sl = 0; label[sl]; sl++) ;				/* Get name length */
	for ( ; sl && label[sl - 1] == ' '; sl--) ;	/* Remove trailing spaces */
	if (sl) {	/* Create volume label in directory form */
		i = j = 0;
		do {
#if _USE_LFN && _LFN_UNICODE
			w = ff_convert(ff_wtoupper(label[i++]), 0);
#else
			w = (BYTE)label[i++];
			if (IsDBCS1(w))
				w = (j < 10 && i < sl && IsDBCS2(label[i])) ? w << 8 | (BYTE)label[i++] : 0;
#if _USE_LFN
			w = ff_convert(ff_wtoupper(ff_convert(w, 1)), 0);
#else
			if (IsLower(w)) w -= 0x20;			/* To upper ASCII characters */
#ifdef _EXCVT
			if (w >= 0x80) w = ExCvt[w - 0x80];	/* To upper extended characters (SBCS cfg) */
#else
			if (!_DF1S && w >= 0x80) w = 0;		/* Reject extended characters (ASCII cfg) */
#endif
#endif
#endif
			if (!w || chk_chr("\"*+,.:;<=>\?[]|\x7F", w) || j >= (UINT)((w >= 0x100) ? 10 : 11)) /* Reject invalid characters for volume label */
				LEAVE_FF(dj.fs, FR_INVALID_NAME);
			if (w >= 0x100) vn[j++] = (BYTE)(w >> 8);
			vn[j++] = (BYTE)w;
		} while (i < sl);
		while (j < 11) vn[j++] = ' ';	/* Fill remaining name field */
		if (vn[0] == DDEM) LEAVE_FF(dj.fs, FR_INVALID_NAME);	/* Reject illegal name (heading DDEM) */
	}

	/* Set volume label */
	dj.sclust = 0;					/* Open root directory */
	res = dir_sdi(&dj, 0);
	if (res == FR_OK) {
		res = dir_read(&dj, 1);		/* Get an entry with AM_VOL */
		if (res == FR_OK) {			/* A volume label is found */
			if (vn[0]) {
				mem_cpy(dj.dir, vn, 11);	/* Change the volume label name */
				tm = GET_FATTIME();
				ST_DWORD(dj.dir + DIR_CrtTime, tm);
				ST_DWORD(dj.dir + DIR_WrtTime, tm);
			} else {
				dj.dir[0] = DDEM;			/* Remove the volume label */
			}
			dj.fs->wflag = 1;
			res = sync_fs(dj.fs);
		} else {					/* No volume label is found or error */
			if (res == FR_NO_FILE) {
				res = FR_OK;
				if (vn[0]) {				/* Create volume label as new */
					res = dir_alloc(&dj, 1);	/* Allocate an entry for volume label */
					if (res == FR_OK) {
						mem_set(dj.dir, 0, SZ_DIRE);	/* Set volume label */
						mem_cpy(dj.dir, vn, 11);
						dj.dir[DIR_Attr] = AM_VOL;
						tm = GET_FATTIME();
						ST_DWORD(dj.dir + DIR_CrtTime, tm);
						ST_DWORD(dj.dir + DIR_WrtTime, tm);
						dj.fs->wflag = 1;
						res = sync_fs(dj.fs);
					}
				}
			}
		}
	}

	LEAVE_FF(dj.fs, res);
}