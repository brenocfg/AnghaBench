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
struct TYPE_4__ {int /*<<< orphan*/ * fs; scalar_t__ lockid; } ;
typedef  scalar_t__ FRESULT ;
typedef  int /*<<< orphan*/  FATFS ;
typedef  TYPE_1__ DIR ;

/* Variables and functions */
 scalar_t__ FR_OK ; 
 scalar_t__ dec_lock (scalar_t__) ; 
 int /*<<< orphan*/  unlock_fs (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ validate (TYPE_1__*) ; 

FRESULT f_closedir (
	DIR *dp		/* Pointer to the directory object to be closed */
)
{
	FRESULT res;


	res = validate(dp);
	if (res == FR_OK) {
#if _FS_REENTRANT
		FATFS *fs = dp->fs;
#endif
#if _FS_LOCK
		if (dp->lockid)				/* Decrement sub-directory open counter */
			res = dec_lock(dp->lockid);
		if (res == FR_OK)
#endif
			dp->fs = 0;				/* Invalidate directory object */
#if _FS_REENTRANT
		unlock_fs(fs, FR_OK);		/* Unlock volume */
#endif
	}
	return res;
}