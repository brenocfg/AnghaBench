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
typedef  scalar_t__ UINT ;
struct TYPE_5__ {scalar_t__* dir; int /*<<< orphan*/  sect; int /*<<< orphan*/  fs; } ;
typedef  scalar_t__ FRESULT ;
typedef  TYPE_1__ DIR ;

/* Variables and functions */
 scalar_t__ DDEM ; 
 scalar_t__ FR_DENIED ; 
 scalar_t__ FR_NO_FILE ; 
 scalar_t__ FR_OK ; 
 scalar_t__ dir_next (TYPE_1__*,int) ; 
 scalar_t__ dir_sdi (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ move_window (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
FRESULT dir_alloc (	/* FR_OK(0):succeeded, !=0:error */
	DIR* dp,		/* Pointer to the directory object */
	UINT nent		/* Number of contiguous entries to allocate (1-21) */
)
{
	FRESULT res;
	UINT n;


	res = dir_sdi(dp, 0);
	if (res == FR_OK) {
		n = 0;
		do {
			res = move_window(dp->fs, dp->sect);
			if (res != FR_OK) break;
			if (dp->dir[0] == DDEM || dp->dir[0] == 0) {	/* Is it a free entry? */
				if (++n == nent) break;	/* A block of contiguous free entries is found */
			} else {
				n = 0;					/* Not a blank entry. Restart to search */
			}
			res = dir_next(dp, 1);		/* Next entry with table stretch enabled */
		} while (res == FR_OK);
	}
	if (res == FR_NO_FILE) res = FR_DENIED;	/* No directory entry to allocate */
	return res;
}