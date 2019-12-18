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
typedef  size_t zpool_status_t ;
struct TYPE_3__ {int /*<<< orphan*/  zpool_config; } ;
typedef  TYPE_1__ zpool_handle_t ;
typedef  int /*<<< orphan*/  zpool_errata_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 size_t NMSGID ; 
 size_t check_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char** zfs_msgid_table ; 

zpool_status_t
zpool_get_status(zpool_handle_t *zhp, char **msgid, zpool_errata_t *errata)
{
	zpool_status_t ret = check_status(zhp->zpool_config, B_FALSE, errata);
	if (msgid != NULL) {
		if (ret >= NMSGID)
			*msgid = NULL;
		else
			*msgid = zfs_msgid_table[ret];
	}
	return (ret);
}