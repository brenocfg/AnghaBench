#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int assert_result; int /*<<< orphan*/  asserts; int /*<<< orphan*/  assert_timestamp; } ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_type_to_string ; 
 int condition_test_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  dual_timestamp_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_unit_internal ; 
 int /*<<< orphan*/  unit_add_to_dbus_queue (TYPE_1__*) ; 

__attribute__((used)) static bool unit_test_assert(Unit *u) {
        assert(u);

        dual_timestamp_get(&u->assert_timestamp);
        u->assert_result = condition_test_list(u->asserts, assert_type_to_string, log_unit_internal, u);

        unit_add_to_dbus_queue(u);

        return u->assert_result;
}