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
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZPOOL_HIST_CMD ; 
 int /*<<< orphan*/  fnvlist_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 int spa_history_log_nvl (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
spa_history_log(spa_t *spa, const char *msg)
{
	int err;
	nvlist_t *nvl = fnvlist_alloc();

	fnvlist_add_string(nvl, ZPOOL_HIST_CMD, msg);
	err = spa_history_log_nvl(spa, nvl);
	fnvlist_free(nvl);
	return (err);
}