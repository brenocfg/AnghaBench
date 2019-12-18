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
struct TYPE_6__ {char* zdm_msg; } ;
typedef  TYPE_1__ zfs_dbgmsg_t ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_7__ {int /*<<< orphan*/  pl_lock; int /*<<< orphan*/  pl_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  STDOUT_FILENO ; 
 TYPE_1__* list_head (int /*<<< orphan*/ *) ; 
 TYPE_1__* list_next (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char const*,int) ; 
 TYPE_2__ zfs_dbgmsgs ; 

void
zfs_dbgmsg_print(const char *tag)
{
	ssize_t ret __attribute__((unused));

	/*
	 * We use write() in this function instead of printf()
	 * so it is safe to call from a signal handler.
	 */
	ret = write(STDOUT_FILENO, "ZFS_DBGMSG(", 11);
	ret = write(STDOUT_FILENO, tag, strlen(tag));
	ret = write(STDOUT_FILENO, ") START:\n", 9);

	mutex_enter(&zfs_dbgmsgs.pl_lock);
	for (zfs_dbgmsg_t *zdm = list_head(&zfs_dbgmsgs.pl_list); zdm != NULL;
	    zdm = list_next(&zfs_dbgmsgs.pl_list, zdm)) {
		ret = write(STDOUT_FILENO, zdm->zdm_msg,
		    strlen(zdm->zdm_msg));
		ret = write(STDOUT_FILENO, "\n", 1);
	}

	ret = write(STDOUT_FILENO, "ZFS_DBGMSG(", 11);
	ret = write(STDOUT_FILENO, tag, strlen(tag));
	ret = write(STDOUT_FILENO, ") END\n", 6);

	mutex_exit(&zfs_dbgmsgs.pl_lock);
}