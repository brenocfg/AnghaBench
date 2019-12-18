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
struct TYPE_4__ {int /*<<< orphan*/  state; int /*<<< orphan*/  deserialized_state; } ;
struct TYPE_3__ {scalar_t__ deserialized_state; scalar_t__ state; } ;
typedef  int /*<<< orphan*/  Manager ;

/* Variables and functions */
 int /*<<< orphan*/  IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MANAGER_IS_TEST_RUN (int /*<<< orphan*/ *) ; 
 TYPE_2__* SERVICE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SERVICE_RELOAD ; 
 int /*<<< orphan*/  SERVICE_RUNNING ; 
 TYPE_1__* SOCKET (int /*<<< orphan*/ *) ; 
 scalar_t__ SOCKET_RUNNING ; 
 int /*<<< orphan*/  SPECIAL_DBUS_SERVICE ; 
 int /*<<< orphan*/  SPECIAL_DBUS_SOCKET ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * manager_get_unit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool manager_dbus_is_running(Manager *m, bool deserialized) {
        Unit *u;

        assert(m);

        /* This checks whether the dbus instance we are supposed to expose our APIs on is up. We check both the socket
         * and the service unit. If the 'deserialized' parameter is true we'll check the deserialized state of the unit
         * rather than the current one. */

        if (MANAGER_IS_TEST_RUN(m))
                return false;

        u = manager_get_unit(m, SPECIAL_DBUS_SOCKET);
        if (!u)
                return false;
        if ((deserialized ? SOCKET(u)->deserialized_state : SOCKET(u)->state) != SOCKET_RUNNING)
                return false;

        u = manager_get_unit(m, SPECIAL_DBUS_SERVICE);
        if (!u)
                return false;
        if (!IN_SET((deserialized ? SERVICE(u)->deserialized_state : SERVICE(u)->state), SERVICE_RUNNING, SERVICE_RELOAD))
                return false;

        return true;
}