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
struct TYPE_4__ {int winsect; int /*<<< orphan*/ * win; scalar_t__ wflag; } ;
typedef  TYPE_1__ FATFS ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BYTE ;

/* Variables and functions */
 size_t BS_55AA ; 
 size_t BS_FilSysType ; 
 size_t BS_FilSysType32 ; 
 scalar_t__ FR_OK ; 
 int LD_DWORD (int /*<<< orphan*/ *) ; 
 int LD_WORD (int /*<<< orphan*/ *) ; 
 scalar_t__ move_window (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
BYTE check_fs (	/* 0:Valid FAT-BS, 1:Valid BS but not FAT, 2:Not a BS, 3:Disk error */
	FATFS* fs,	/* File system object */
	DWORD sect	/* Sector# (lba) to check if it is an FAT boot record or not */
)
{
	fs->wflag = 0; fs->winsect = 0xFFFFFFFF;	/* Invaidate window */
	if (move_window(fs, sect) != FR_OK)			/* Load boot record */
		return 3;

	if (LD_WORD(&fs->win[BS_55AA]) != 0xAA55)	/* Check boot record signature (always placed at offset 510 even if the sector size is >512) */
		return 2;

	if ((LD_DWORD(&fs->win[BS_FilSysType]) & 0xFFFFFF) == 0x544146)		/* Check "FAT" string */
		return 0;
	if ((LD_DWORD(&fs->win[BS_FilSysType32]) & 0xFFFFFF) == 0x544146)	/* Check "FAT" string */
		return 0;

	return 1;
}