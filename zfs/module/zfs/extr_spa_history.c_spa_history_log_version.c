#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  machine; int /*<<< orphan*/  version; int /*<<< orphan*/  release; int /*<<< orphan*/  nodename; } ;
typedef  TYPE_1__ utsname_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_META_GITREV ; 
 int /*<<< orphan*/  spa_history_log_internal (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_version (int /*<<< orphan*/ *) ; 
 TYPE_1__* utsname () ; 

void
spa_history_log_version(spa_t *spa, const char *operation, dmu_tx_t *tx)
{
	utsname_t *u = utsname();

	spa_history_log_internal(spa, operation, tx,
	    "pool version %llu; software version %s; uts %s %s %s %s",
	    (u_longlong_t)spa_version(spa), ZFS_META_GITREV,
	    u->nodename, u->release, u->version, u->machine);
}