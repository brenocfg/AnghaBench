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
typedef  int /*<<< orphan*/  namecheck_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  NAME_ERR_DISKLIKE ; 
 int /*<<< orphan*/  NAME_ERR_INVALCHAR ; 
 int /*<<< orphan*/  NAME_ERR_NOLETTER ; 
 int /*<<< orphan*/  NAME_ERR_RESERVED ; 
 int /*<<< orphan*/  NAME_ERR_TOOLONG ; 
 char const* ORIGIN_DIR_NAME ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  valid_char (char const) ; 

int
pool_namecheck(const char *pool, namecheck_err_t *why, char *what)
{
	const char *c;

	/*
	 * Make sure the name is not too long.
	 * If we're creating a pool with version >= SPA_VERSION_DSL_SCRUB (v11)
	 * we need to account for additional space needed by the origin ds which
	 * will also be snapshotted: "poolname"+"/"+"$ORIGIN"+"@"+"$ORIGIN".
	 * Play it safe and enforce this limit even if the pool version is < 11
	 * so it can be upgraded without issues.
	 */
	if (strlen(pool) >= (ZFS_MAX_DATASET_NAME_LEN - 2 -
	    strlen(ORIGIN_DIR_NAME) * 2)) {
		if (why)
			*why = NAME_ERR_TOOLONG;
		return (-1);
	}

	c = pool;
	while (*c != '\0') {
		if (!valid_char(*c)) {
			if (why) {
				*why = NAME_ERR_INVALCHAR;
				*what = *c;
			}
			return (-1);
		}
		c++;
	}

	if (!(*pool >= 'a' && *pool <= 'z') &&
	    !(*pool >= 'A' && *pool <= 'Z')) {
		if (why)
			*why = NAME_ERR_NOLETTER;
		return (-1);
	}

	if (strcmp(pool, "mirror") == 0 || strcmp(pool, "raidz") == 0) {
		if (why)
			*why = NAME_ERR_RESERVED;
		return (-1);
	}

	if (pool[0] == 'c' && (pool[1] >= '0' && pool[1] <= '9')) {
		if (why)
			*why = NAME_ERR_DISKLIKE;
		return (-1);
	}

	return (0);
}