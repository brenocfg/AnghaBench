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
struct TYPE_3__ {char* member_0; scalar_t__ zc_guid; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_IOC_CLEAR_FAULT ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*) ; 
 int /*<<< orphan*/  g_zfs ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int
cancel_handler(int id)
{
	zfs_cmd_t zc = {"\0"};

	zc.zc_guid = (uint64_t)id;

	if (zfs_ioctl(g_zfs, ZFS_IOC_CLEAR_FAULT, &zc) != 0) {
		(void) fprintf(stderr, "failed to remove handler %d: %s\n",
		    id, strerror(errno));
		return (1);
	}

	(void) printf("removed handler %d\n", id);

	return (0);
}