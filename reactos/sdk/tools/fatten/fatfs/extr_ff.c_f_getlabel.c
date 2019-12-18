#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int WCHAR ;
typedef  int UINT ;
struct TYPE_8__ {scalar_t__ fs_type; int /*<<< orphan*/ * win; int /*<<< orphan*/  volbase; } ;
struct TYPE_7__ {char* dir; TYPE_2__* fs; scalar_t__ sclust; } ;
typedef  char TCHAR ;
typedef  scalar_t__ FRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_1__ DIR ;

/* Variables and functions */
 int BS_VolID ; 
 int BS_VolID32 ; 
 scalar_t__ FR_NO_FILE ; 
 scalar_t__ FR_OK ; 
 scalar_t__ FS_FAT32 ; 
 scalar_t__ IsDBCS1 (int) ; 
 scalar_t__ IsDBCS2 (char) ; 
 int /*<<< orphan*/  LD_DWORD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LEAVE_FF (TYPE_2__*,scalar_t__) ; 
 scalar_t__ dir_read (TYPE_1__*,int) ; 
 scalar_t__ dir_sdi (TYPE_1__*,int /*<<< orphan*/ ) ; 
 char ff_convert (int,int) ; 
 scalar_t__ find_volume (TYPE_2__**,char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mem_cpy (char*,int*,int) ; 
 scalar_t__ move_window (TYPE_2__*,int /*<<< orphan*/ ) ; 

FRESULT f_getlabel (
	const TCHAR* path,	/* Path name of the logical drive number */
	TCHAR* label,		/* Pointer to a buffer to return the volume label */
	DWORD* vsn			/* Pointer to a variable to return the volume serial number */
)
{
	FRESULT res;
	DIR dj;
	UINT i, j;
#if _USE_LFN && _LFN_UNICODE
	WCHAR w;
#endif


	/* Get logical drive number */
	res = find_volume(&dj.fs, &path, 0);

	/* Get volume label */
	if (res == FR_OK && label) {
		dj.sclust = 0;					/* Open root directory */
		res = dir_sdi(&dj, 0);
		if (res == FR_OK) {
			res = dir_read(&dj, 1);		/* Get an entry with AM_VOL */
			if (res == FR_OK) {			/* A volume label is exist */
#if _USE_LFN && _LFN_UNICODE
				i = j = 0;
				do {
					w = (i < 11) ? dj.dir[i++] : ' ';
					if (IsDBCS1(w) && i < 11 && IsDBCS2(dj.dir[i]))
						w = w << 8 | dj.dir[i++];
					label[j++] = ff_convert(w, 1);	/* OEM -> Unicode */
				} while (j < 11);
#else
				mem_cpy(label, dj.dir, 11);
#endif
				j = 11;
				do {
					label[j] = 0;
					if (!j) break;
				} while (label[--j] == ' ');
			}
			if (res == FR_NO_FILE) {	/* No label, return nul string */
				label[0] = 0;
				res = FR_OK;
			}
		}
	}

	/* Get volume serial number */
	if (res == FR_OK && vsn) {
		res = move_window(dj.fs, dj.fs->volbase);
		if (res == FR_OK) {
			i = dj.fs->fs_type == FS_FAT32 ? BS_VolID32 : BS_VolID;
			*vsn = LD_DWORD(&dj.fs->win[i]);
		}
	}

	LEAVE_FF(dj.fs, res);
}