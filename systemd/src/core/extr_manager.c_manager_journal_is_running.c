#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
struct TYPE_3__ {scalar_t__ state; } ;
typedef  int /*<<< orphan*/  Manager ;

/* Variables and functions */
 int /*<<< orphan*/  IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MANAGER_IS_SYSTEM (int /*<<< orphan*/ *) ; 
 scalar_t__ MANAGER_IS_TEST_RUN (int /*<<< orphan*/ *) ; 
 TYPE_2__* SERVICE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SERVICE_RELOAD ; 
 int /*<<< orphan*/  SERVICE_RUNNING ; 
 TYPE_1__* SOCKET (int /*<<< orphan*/ *) ; 
 scalar_t__ SOCKET_RUNNING ; 
 int /*<<< orphan*/  SPECIAL_JOURNALD_SERVICE ; 
 int /*<<< orphan*/  SPECIAL_JOURNALD_SOCKET ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * manager_get_unit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool manager_journal_is_running(Manager *m) {
        Unit *u;

        assert(m);

        if (MANAGER_IS_TEST_RUN(m))
                return false;

        /* If we are the user manager we can safely assume that the journal is up */
        if (!MANAGER_IS_SYSTEM(m))
                return true;

        /* Check that the socket is not only up, but in RUNNING state */
        u = manager_get_unit(m, SPECIAL_JOURNALD_SOCKET);
        if (!u)
                return false;
        if (SOCKET(u)->state != SOCKET_RUNNING)
                return false;

        /* Similar, check if the daemon itself is fully up, too */
        u = manager_get_unit(m, SPECIAL_JOURNALD_SERVICE);
        if (!u)
                return false;
        if (!IN_SET(SERVICE(u)->state, SERVICE_RELOAD, SERVICE_RUNNING))
                return false;

        return true;
}