#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * zn_handle; } ;
typedef  TYPE_1__ zfs_node_t ;
typedef  int /*<<< orphan*/  zfs_handle_t ;
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_PROP_CREATETXG ; 
 scalar_t__ strchr (char const*,char) ; 
 int strcmp (char const*,char const*) ; 
 char* zfs_get_name (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_prop_get_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_compare(const void *larg, const void *rarg, void *unused)
{
	zfs_handle_t *l = ((zfs_node_t *)larg)->zn_handle;
	zfs_handle_t *r = ((zfs_node_t *)rarg)->zn_handle;
	const char *lname = zfs_get_name(l);
	const char *rname = zfs_get_name(r);
	char *lat, *rat;
	uint64_t lcreate, rcreate;
	int ret;

	lat = (char *)strchr(lname, '@');
	rat = (char *)strchr(rname, '@');

	if (lat != NULL)
		*lat = '\0';
	if (rat != NULL)
		*rat = '\0';

	ret = strcmp(lname, rname);
	if (ret == 0 && (lat != NULL || rat != NULL)) {
		/*
		 * If we're comparing a dataset to one of its snapshots, we
		 * always make the full dataset first.
		 */
		if (lat == NULL) {
			ret = -1;
		} else if (rat == NULL) {
			ret = 1;
		} else {
			/*
			 * If we have two snapshots from the same dataset, then
			 * we want to sort them according to creation time.  We
			 * use the hidden CREATETXG property to get an absolute
			 * ordering of snapshots.
			 */
			lcreate = zfs_prop_get_int(l, ZFS_PROP_CREATETXG);
			rcreate = zfs_prop_get_int(r, ZFS_PROP_CREATETXG);

			/*
			 * Both lcreate and rcreate being 0 means we don't have
			 * properties and we should compare full name.
			 */
			if (lcreate == 0 && rcreate == 0)
				ret = strcmp(lat + 1, rat + 1);
			else if (lcreate < rcreate)
				ret = -1;
			else if (lcreate > rcreate)
				ret = 1;
		}
	}

	if (lat != NULL)
		*lat = '@';
	if (rat != NULL)
		*rat = '@';

	return (ret);
}