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
typedef  int UINT ;
struct TYPE_5__ {int n_fatent; int fs_type; int fatbase; int* win; } ;
typedef  TYPE_1__ FATFS ;
typedef  int DWORD ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  FR_OK ; 
#define  FS_FAT12 130 
#define  FS_FAT16 129 
#define  FS_FAT32 128 
 int LD_DWORD (int*) ; 
 int LD_WORD (int*) ; 
 int SS (TYPE_1__*) ; 
 int /*<<< orphan*/  move_window (TYPE_1__*,int) ; 

DWORD get_fat (	/* 0xFFFFFFFF:Disk error, 1:Internal error, 2..0x0FFFFFFF:Cluster status */
	FATFS* fs,	/* File system object */
	DWORD clst	/* FAT index number (cluster number) to get the value */
)
{
	UINT wc, bc;
	BYTE *p;
	DWORD val;


	if (clst < 2 || clst >= fs->n_fatent) {	/* Check if in valid range */
		val = 1;	/* Internal error */

	} else {
		val = 0xFFFFFFFF;	/* Default value falls on disk error */

		switch (fs->fs_type) {
		case FS_FAT12 :
			bc = (UINT)clst; bc += bc / 2;
			if (move_window(fs, fs->fatbase + (bc / SS(fs))) != FR_OK) break;
			wc = fs->win[bc++ % SS(fs)];
			if (move_window(fs, fs->fatbase + (bc / SS(fs))) != FR_OK) break;
			wc |= fs->win[bc % SS(fs)] << 8;
			val = clst & 1 ? wc >> 4 : (wc & 0xFFF);
			break;

		case FS_FAT16 :
			if (move_window(fs, fs->fatbase + (clst / (SS(fs) / 2))) != FR_OK) break;
			p = &fs->win[clst * 2 % SS(fs)];
			val = LD_WORD(p);
			break;

		case FS_FAT32 :
			if (move_window(fs, fs->fatbase + (clst / (SS(fs) / 4))) != FR_OK) break;
			p = &fs->win[clst * 4 % SS(fs)];
			val = LD_DWORD(p) & 0x0FFFFFFF;
			break;

		default:
			val = 1;	/* Internal error */
		}
	}

	return val;
}