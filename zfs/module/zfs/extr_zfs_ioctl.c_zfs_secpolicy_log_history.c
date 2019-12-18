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
typedef  int /*<<< orphan*/  zfs_cmd_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  EPERM ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tsd_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_allow_log_key ; 

__attribute__((used)) static int
zfs_secpolicy_log_history(zfs_cmd_t *zc, nvlist_t *innvl, cred_t *cr)
{
	/*
	 * Even root must have a proper TSD so that we know what pool
	 * to log to.
	 */
	if (tsd_get(zfs_allow_log_key) == NULL)
		return (SET_ERROR(EPERM));
	return (0);
}