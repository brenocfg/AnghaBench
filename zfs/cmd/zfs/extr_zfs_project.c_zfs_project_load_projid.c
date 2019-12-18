#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  fsx_projid; } ;
typedef  TYPE_1__ zfsxattr_t ;
struct TYPE_6__ {int /*<<< orphan*/  zpc_expected_projid; } ;
typedef  TYPE_2__ zfs_project_control_t ;

/* Variables and functions */
 int O_NOCTTY ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  ZFS_IOC_FSGETXATTR ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 char* gettext (char*) ; 
 int ioctl (int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int open (char const*,int) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_project_load_projid(const char *name, zfs_project_control_t *zpc)
{
	zfsxattr_t fsx;
	int ret, fd;

	fd = open(name, O_RDONLY | O_NOCTTY);
	if (fd < 0) {
		(void) fprintf(stderr, gettext("failed to open %s: %s\n"),
		    name, strerror(errno));
		return (fd);
	}

	ret = ioctl(fd, ZFS_IOC_FSGETXATTR, &fsx);
	if (ret)
		(void) fprintf(stderr,
		    gettext("failed to get xattr for %s: %s\n"),
		    name, strerror(errno));
	else
		zpc->zpc_expected_projid = fsx.fsx_projid;

	close(fd);
	return (ret);
}