#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  fs; scalar_t__ sect; } ;
typedef  scalar_t__ FRESULT ;
typedef  int /*<<< orphan*/  FILINFO ;
typedef  TYPE_1__ DIR ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_NAMEBUF ; 
 int /*<<< orphan*/  FREE_BUF () ; 
 scalar_t__ FR_NO_FILE ; 
 scalar_t__ FR_OK ; 
 int /*<<< orphan*/  INIT_BUF (TYPE_1__) ; 
 int /*<<< orphan*/  LEAVE_FF (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ dir_next (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ dir_read (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ dir_sdi (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_fileinfo (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ validate (TYPE_1__*) ; 

FRESULT f_readdir (
	DIR* dp,			/* Pointer to the open directory object */
	FILINFO* fno		/* Pointer to file information to return */
)
{
	FRESULT res;
	DEFINE_NAMEBUF;


	res = validate(dp);						/* Check validity of the object */
	if (res == FR_OK) {
		if (!fno) {
			res = dir_sdi(dp, 0);			/* Rewind the directory object */
		} else {
			INIT_BUF(*dp);
			res = dir_read(dp, 0);			/* Read an item */
			if (res == FR_NO_FILE) {		/* Reached end of directory */
				dp->sect = 0;
				res = FR_OK;
			}
			if (res == FR_OK) {				/* A valid entry is found */
				get_fileinfo(dp, fno);		/* Get the object information */
				res = dir_next(dp, 0);		/* Increment index for next */
				if (res == FR_NO_FILE) {
					dp->sect = 0;
					res = FR_OK;
				}
			}
			FREE_BUF();
		}
	}

	LEAVE_FF(dp->fs, res);
}