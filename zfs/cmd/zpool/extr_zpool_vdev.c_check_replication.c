#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint_t ;
struct TYPE_8__ {int zprl_parity; int zprl_children; int /*<<< orphan*/  zprl_type; } ;
typedef  TYPE_1__ replication_level_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_CHILDREN ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_TREE ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* get_replication (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gettext (char*) ; 
 scalar_t__ is_raidz_mirror (TYPE_1__*,TYPE_1__*,TYPE_1__**,TYPE_1__**) ; 
 scalar_t__ num_logs (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ nvlist_lookup_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ***,scalar_t__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_error (int /*<<< orphan*/ ,scalar_t__,scalar_t__,...) ; 
 int /*<<< orphan*/  verify (int) ; 

__attribute__((used)) static int
check_replication(nvlist_t *config, nvlist_t *newroot)
{
	nvlist_t **child;
	uint_t	children;
	replication_level_t *current = NULL, *new;
	replication_level_t *raidz, *mirror;
	int ret;

	/*
	 * If we have a current pool configuration, check to see if it's
	 * self-consistent.  If not, simply return success.
	 */
	if (config != NULL) {
		nvlist_t *nvroot;

		verify(nvlist_lookup_nvlist(config, ZPOOL_CONFIG_VDEV_TREE,
		    &nvroot) == 0);
		if ((current = get_replication(nvroot, B_FALSE)) == NULL)
			return (0);
	}
	/*
	 * for spares there may be no children, and therefore no
	 * replication level to check
	 */
	if ((nvlist_lookup_nvlist_array(newroot, ZPOOL_CONFIG_CHILDREN,
	    &child, &children) != 0) || (children == 0)) {
		free(current);
		return (0);
	}

	/*
	 * If all we have is logs then there's no replication level to check.
	 */
	if (num_logs(newroot) == children) {
		free(current);
		return (0);
	}

	/*
	 * Get the replication level of the new vdev spec, reporting any
	 * inconsistencies found.
	 */
	if ((new = get_replication(newroot, B_TRUE)) == NULL) {
		free(current);
		return (-1);
	}

	/*
	 * Check to see if the new vdev spec matches the replication level of
	 * the current pool.
	 */
	ret = 0;
	if (current != NULL) {
		if (is_raidz_mirror(current, new, &raidz, &mirror) ||
		    is_raidz_mirror(new, current, &raidz, &mirror)) {
			if (raidz->zprl_parity != mirror->zprl_children - 1) {
				vdev_error(gettext(
				    "mismatched replication level: pool and "
				    "new vdev with different redundancy, %s "
				    "and %s vdevs, %llu vs. %llu (%llu-way)\n"),
				    raidz->zprl_type,
				    mirror->zprl_type,
				    raidz->zprl_parity,
				    mirror->zprl_children - 1,
				    mirror->zprl_children);
				ret = -1;
			}
		} else if (strcmp(current->zprl_type, new->zprl_type) != 0) {
			vdev_error(gettext(
			    "mismatched replication level: pool uses %s "
			    "and new vdev is %s\n"),
			    current->zprl_type, new->zprl_type);
			ret = -1;
		} else if (current->zprl_parity != new->zprl_parity) {
			vdev_error(gettext(
			    "mismatched replication level: pool uses %llu "
			    "device parity and new vdev uses %llu\n"),
			    current->zprl_parity, new->zprl_parity);
			ret = -1;
		} else if (current->zprl_children != new->zprl_children) {
			vdev_error(gettext(
			    "mismatched replication level: pool uses %llu-way "
			    "%s and new vdev uses %llu-way %s\n"),
			    current->zprl_children, current->zprl_type,
			    new->zprl_children, new->zprl_type);
			ret = -1;
		}
	}

	free(new);
	if (current != NULL)
		free(current);

	return (ret);
}