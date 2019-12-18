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
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_4__ {scalar_t__ verbose; int /*<<< orphan*/  poolname; scalar_t__ follow; int /*<<< orphan*/  scripted; } ;
typedef  TYPE_1__ ev_opts_t ;

/* Variables and functions */
 int /*<<< orphan*/  FM_FMRI_ZFS_POOL ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  ZEVENT_NONBLOCK ; 
 int /*<<< orphan*/  ZEVENT_NONE ; 
 int /*<<< orphan*/  ZFS_DEV ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_zfs ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpool_do_events_nvprint (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zpool_do_events_short (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int zpool_events_next (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
zpool_do_events_next(ev_opts_t *opts)
{
	nvlist_t *nvl;
	int zevent_fd, ret, dropped;
	char *pool;

	zevent_fd = open(ZFS_DEV, O_RDWR);
	VERIFY(zevent_fd >= 0);

	if (!opts->scripted)
		(void) printf(gettext("%-30s %s\n"), "TIME", "CLASS");

	while (1) {
		ret = zpool_events_next(g_zfs, &nvl, &dropped,
		    (opts->follow ? ZEVENT_NONE : ZEVENT_NONBLOCK), zevent_fd);
		if (ret || nvl == NULL)
			break;

		if (dropped > 0)
			(void) printf(gettext("dropped %d events\n"), dropped);

		if (strlen(opts->poolname) > 0 &&
		    nvlist_lookup_string(nvl, FM_FMRI_ZFS_POOL, &pool) == 0 &&
		    strcmp(opts->poolname, pool) != 0)
			continue;

		zpool_do_events_short(nvl, opts);

		if (opts->verbose) {
			zpool_do_events_nvprint(nvl, 8);
			printf(gettext("\n"));
		}
		(void) fflush(stdout);

		nvlist_free(nvl);
	}

	VERIFY(0 == close(zevent_fd));

	return (ret);
}