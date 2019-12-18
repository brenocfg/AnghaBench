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
typedef  int zfs_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEXT_DOMAIN ; 
#define  ZFS_TYPE_BOOKMARK 132 
#define  ZFS_TYPE_FILESYSTEM 131 
#define  ZFS_TYPE_POOL 130 
#define  ZFS_TYPE_SNAPSHOT 129 
#define  ZFS_TYPE_VOLUME 128 
 int /*<<< orphan*/  assert (int) ; 
 char const* dgettext (int /*<<< orphan*/ ,char*) ; 

const char *
zfs_type_to_name(zfs_type_t type)
{
	switch (type) {
	case ZFS_TYPE_FILESYSTEM:
		return (dgettext(TEXT_DOMAIN, "filesystem"));
	case ZFS_TYPE_SNAPSHOT:
		return (dgettext(TEXT_DOMAIN, "snapshot"));
	case ZFS_TYPE_VOLUME:
		return (dgettext(TEXT_DOMAIN, "volume"));
	case ZFS_TYPE_POOL:
		return (dgettext(TEXT_DOMAIN, "pool"));
	case ZFS_TYPE_BOOKMARK:
		return (dgettext(TEXT_DOMAIN, "bookmark"));
	default:
		assert(!"unhandled zfs_type_t");
	}

	return (NULL);
}