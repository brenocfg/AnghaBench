#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  EDOM ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  ISP2 (scalar_t__) ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPA_FEATURE_LARGE_BLOCKS ; 
 scalar_t__ SPA_MAXBLOCKSIZE ; 
 scalar_t__ SPA_MINBLOCKSIZE ; 
 scalar_t__ SPA_OLD_MAXBLOCKSIZE ; 
 int /*<<< orphan*/  spa_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_feature_is_enabled (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int spa_open (char const*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_max_recordsize ; 

int
zvol_check_volblocksize(const char *name, uint64_t volblocksize)
{
	/* Record sizes above 128k need the feature to be enabled */
	if (volblocksize > SPA_OLD_MAXBLOCKSIZE) {
		spa_t *spa;
		int error;

		if ((error = spa_open(name, &spa, FTAG)) != 0)
			return (error);

		if (!spa_feature_is_enabled(spa, SPA_FEATURE_LARGE_BLOCKS)) {
			spa_close(spa, FTAG);
			return (SET_ERROR(ENOTSUP));
		}

		/*
		 * We don't allow setting the property above 1MB,
		 * unless the tunable has been changed.
		 */
		if (volblocksize > zfs_max_recordsize)
			return (SET_ERROR(EDOM));

		spa_close(spa, FTAG);
	}

	if (volblocksize < SPA_MINBLOCKSIZE ||
	    volblocksize > SPA_MAXBLOCKSIZE ||
	    !ISP2(volblocksize))
		return (SET_ERROR(EDOM));

	return (0);
}