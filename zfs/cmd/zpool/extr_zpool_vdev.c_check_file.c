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
typedef  int pool_state_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
#define  POOL_STATE_ACTIVE 131 
#define  POOL_STATE_EXPORTED 130 
#define  POOL_STATE_POTENTIALLY_ACTIVE 129 
#define  POOL_STATE_SPARE 128 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  g_zfs ; 
 char* gettext (char*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_error (char*,char const*,char const*,...) ; 
 scalar_t__ zpool_in_use (int /*<<< orphan*/ ,int,int*,char**,scalar_t__*) ; 

int
check_file(const char *file, boolean_t force, boolean_t isspare)
{
	char  *name;
	int fd;
	int ret = 0;
	pool_state_t state;
	boolean_t inuse;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (0);

	if (zpool_in_use(g_zfs, fd, &state, &name, &inuse) == 0 && inuse) {
		const char *desc;

		switch (state) {
		case POOL_STATE_ACTIVE:
			desc = gettext("active");
			break;

		case POOL_STATE_EXPORTED:
			desc = gettext("exported");
			break;

		case POOL_STATE_POTENTIALLY_ACTIVE:
			desc = gettext("potentially active");
			break;

		default:
			desc = gettext("unknown");
			break;
		}

		/*
		 * Allow hot spares to be shared between pools.
		 */
		if (state == POOL_STATE_SPARE && isspare) {
			free(name);
			(void) close(fd);
			return (0);
		}

		if (state == POOL_STATE_ACTIVE ||
		    state == POOL_STATE_SPARE || !force) {
			switch (state) {
			case POOL_STATE_SPARE:
				vdev_error(gettext("%s is reserved as a hot "
				    "spare for pool %s\n"), file, name);
				break;
			default:
				vdev_error(gettext("%s is part of %s pool "
				    "'%s'\n"), file, desc, name);
				break;
			}
			ret = -1;
		}

		free(name);
	}

	(void) close(fd);
	return (ret);
}