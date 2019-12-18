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
typedef  int /*<<< orphan*/  zfs_handle_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/ * cb_prevsnap; int /*<<< orphan*/ * cb_firstsnap; int /*<<< orphan*/  cb_snapused; scalar_t__ cb_dryrun; scalar_t__ cb_parsable; scalar_t__ cb_verbose; int /*<<< orphan*/  cb_nvl; } ;
typedef  TYPE_1__ destroy_cbdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 char* gettext (char*) ; 
 int lzc_snaprange_space (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  nomem () ; 
 scalar_t__ nvlist_exists (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 void* strdup (char const*) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 char* zfs_get_name (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
destroy_print_cb(zfs_handle_t *zhp, void *arg)
{
	destroy_cbdata_t *cb = arg;
	const char *name = zfs_get_name(zhp);
	int err = 0;

	if (nvlist_exists(cb->cb_nvl, name)) {
		if (cb->cb_firstsnap == NULL)
			cb->cb_firstsnap = strdup(name);
		if (cb->cb_prevsnap != NULL)
			free(cb->cb_prevsnap);
		/* this snap continues the current range */
		cb->cb_prevsnap = strdup(name);
		if (cb->cb_firstsnap == NULL || cb->cb_prevsnap == NULL)
			nomem();
		if (cb->cb_verbose) {
			if (cb->cb_parsable) {
				(void) printf("destroy\t%s\n", name);
			} else if (cb->cb_dryrun) {
				(void) printf(gettext("would destroy %s\n"),
				    name);
			} else {
				(void) printf(gettext("will destroy %s\n"),
				    name);
			}
		}
	} else if (cb->cb_firstsnap != NULL) {
		/* end of this range */
		uint64_t used = 0;
		err = lzc_snaprange_space(cb->cb_firstsnap,
		    cb->cb_prevsnap, &used);
		cb->cb_snapused += used;
		free(cb->cb_firstsnap);
		cb->cb_firstsnap = NULL;
		free(cb->cb_prevsnap);
		cb->cb_prevsnap = NULL;
	}
	zfs_close(zhp);
	return (err);
}