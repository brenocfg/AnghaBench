#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zpool_handle_t ;
typedef  size_t uint_t ;
struct TYPE_4__ {int /*<<< orphan*/  dryrun; } ;
typedef  TYPE_1__ splitflags_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZPOOL_CONFIG_CHILDREN ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_PATH ; 
 int /*<<< orphan*/ * construct_spec (int /*<<< orphan*/ *,int,char**) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* gettext (char*) ; 
 char* is_grouping (char*,int*,int*) ; 
 scalar_t__ make_disks (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ***,size_t*) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  verify (int) ; 
 scalar_t__ zpool_vdev_split (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_1__) ; 

nvlist_t *
split_mirror_vdev(zpool_handle_t *zhp, char *newname, nvlist_t *props,
    splitflags_t flags, int argc, char **argv)
{
	nvlist_t *newroot = NULL, **child;
	uint_t c, children;

	if (argc > 0) {
		if ((newroot = construct_spec(props, argc, argv)) == NULL) {
			(void) fprintf(stderr, gettext("Unable to build a "
			    "pool from the specified devices\n"));
			return (NULL);
		}

		if (!flags.dryrun && make_disks(zhp, newroot) != 0) {
			nvlist_free(newroot);
			return (NULL);
		}

		/* avoid any tricks in the spec */
		verify(nvlist_lookup_nvlist_array(newroot,
		    ZPOOL_CONFIG_CHILDREN, &child, &children) == 0);
		for (c = 0; c < children; c++) {
			char *path;
			const char *type;
			int min, max;

			verify(nvlist_lookup_string(child[c],
			    ZPOOL_CONFIG_PATH, &path) == 0);
			if ((type = is_grouping(path, &min, &max)) != NULL) {
				(void) fprintf(stderr, gettext("Cannot use "
				    "'%s' as a device for splitting\n"), type);
				nvlist_free(newroot);
				return (NULL);
			}
		}
	}

	if (zpool_vdev_split(zhp, newname, &newroot, props, flags) != 0) {
		nvlist_free(newroot);
		return (NULL);
	}

	return (newroot);
}