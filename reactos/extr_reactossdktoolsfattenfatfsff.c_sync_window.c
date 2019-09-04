#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_3__ {scalar_t__ winsect; scalar_t__ fatbase; scalar_t__ fsize; int n_fats; int /*<<< orphan*/  win; int /*<<< orphan*/  drv; scalar_t__ wflag; } ;
typedef  int /*<<< orphan*/  FRESULT ;
typedef  TYPE_1__ FATFS ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FR_DISK_ERR ; 
 int /*<<< orphan*/  FR_OK ; 
 scalar_t__ RES_OK ; 
 scalar_t__ disk_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static
FRESULT sync_window (	/* FR_OK:succeeded, !=0:error */
	FATFS* fs		/* File system object */
)
{
	DWORD wsect;
	UINT nf;
	FRESULT res = FR_OK;


	if (fs->wflag) {	/* Write back the sector if it is dirty */
		wsect = fs->winsect;	/* Current sector number */
		if (disk_write(fs->drv, fs->win, wsect, 1) != RES_OK) {
			res = FR_DISK_ERR;
		} else {
			fs->wflag = 0;
			if (wsect - fs->fatbase < fs->fsize) {		/* Is it in the FAT area? */
				for (nf = fs->n_fats; nf >= 2; nf--) {	/* Reflect the change to all FAT copies */
					wsect += fs->fsize;
					disk_write(fs->drv, fs->win, wsect, 1);
				}
			}
		}
	}
	return res;
}