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
typedef  int /*<<< orphan*/  zpool_handle_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_2__ {char* fi_uname; char* fi_guid; } ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int SPA_FEATURES ; 
 int /*<<< orphan*/  ZFS_FEATURE_ENABLED ; 
 int asprintf (char**,char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  nvlist_exists (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 TYPE_1__* spa_feature_table ; 
 int /*<<< orphan*/  verify (int) ; 
 int /*<<< orphan*/ * zpool_get_features (int /*<<< orphan*/ *) ; 
 char* zpool_get_name (int /*<<< orphan*/ *) ; 
 int zpool_set_prop (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
upgrade_enable_all(zpool_handle_t *zhp, int *countp)
{
	int i, ret, count;
	boolean_t firstff = B_TRUE;
	nvlist_t *enabled = zpool_get_features(zhp);

	count = 0;
	for (i = 0; i < SPA_FEATURES; i++) {
		const char *fname = spa_feature_table[i].fi_uname;
		const char *fguid = spa_feature_table[i].fi_guid;
		if (!nvlist_exists(enabled, fguid)) {
			char *propname;
			verify(-1 != asprintf(&propname, "feature@%s", fname));
			ret = zpool_set_prop(zhp, propname,
			    ZFS_FEATURE_ENABLED);
			if (ret != 0) {
				free(propname);
				return (ret);
			}
			count++;

			if (firstff) {
				(void) printf(gettext("Enabled the "
				    "following features on '%s':\n"),
				    zpool_get_name(zhp));
				firstff = B_FALSE;
			}
			(void) printf(gettext("  %s\n"), fname);
			free(propname);
		}
	}

	if (countp != NULL)
		*countp = count;
	return (0);
}