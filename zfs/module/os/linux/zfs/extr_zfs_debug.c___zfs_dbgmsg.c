#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int zdm_size; int /*<<< orphan*/  zdm_msg; int /*<<< orphan*/  zdm_timestamp; } ;
typedef  TYPE_1__ zfs_dbgmsg_t ;
struct TYPE_7__ {int /*<<< orphan*/  pl_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gethrestime_sec () ; 
 TYPE_1__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  procfs_list_add (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  zfs_dbgmsg_maxsize ; 
 int /*<<< orphan*/  zfs_dbgmsg_purge (int /*<<< orphan*/ ) ; 
 int zfs_dbgmsg_size ; 
 TYPE_2__ zfs_dbgmsgs ; 

void
__zfs_dbgmsg(char *buf)
{
	int size = sizeof (zfs_dbgmsg_t) + strlen(buf);
	zfs_dbgmsg_t *zdm = kmem_zalloc(size, KM_SLEEP);
	zdm->zdm_size = size;
	zdm->zdm_timestamp = gethrestime_sec();
	strcpy(zdm->zdm_msg, buf);

	mutex_enter(&zfs_dbgmsgs.pl_lock);
	procfs_list_add(&zfs_dbgmsgs, zdm);
	zfs_dbgmsg_size += size;
	zfs_dbgmsg_purge(MAX(zfs_dbgmsg_maxsize, 0));
	mutex_exit(&zfs_dbgmsgs.pl_lock);
}