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
struct TYPE_4__ {int /*<<< orphan*/  manager; int /*<<< orphan*/  default_dependencies; } ;
typedef  int /*<<< orphan*/  Service ;

/* Variables and functions */
 scalar_t__ MANAGER_IS_SYSTEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPECIAL_BASIC_TARGET ; 
 int /*<<< orphan*/  SPECIAL_SHUTDOWN_TARGET ; 
 int /*<<< orphan*/  SPECIAL_SYSINIT_TARGET ; 
 TYPE_1__* UNIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNIT_AFTER ; 
 int /*<<< orphan*/  UNIT_BEFORE ; 
 int /*<<< orphan*/  UNIT_CONFLICTS ; 
 int /*<<< orphan*/  UNIT_DEPENDENCY_DEFAULT ; 
 int /*<<< orphan*/  UNIT_REQUIRES ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int unit_add_dependency_by_name (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int unit_add_two_dependencies_by_name (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int service_add_default_dependencies(Service *s) {
        int r;

        assert(s);

        if (!UNIT(s)->default_dependencies)
                return 0;

        /* Add a number of automatic dependencies useful for the
         * majority of services. */

        if (MANAGER_IS_SYSTEM(UNIT(s)->manager)) {
                /* First, pull in the really early boot stuff, and
                 * require it, so that we fail if we can't acquire
                 * it. */

                r = unit_add_two_dependencies_by_name(UNIT(s), UNIT_AFTER, UNIT_REQUIRES, SPECIAL_SYSINIT_TARGET, true, UNIT_DEPENDENCY_DEFAULT);
                if (r < 0)
                        return r;
        } else {

                /* In the --user instance there's no sysinit.target,
                 * in that case require basic.target instead. */

                r = unit_add_dependency_by_name(UNIT(s), UNIT_REQUIRES, SPECIAL_BASIC_TARGET, true, UNIT_DEPENDENCY_DEFAULT);
                if (r < 0)
                        return r;
        }

        /* Second, if the rest of the base system is in the same
         * transaction, order us after it, but do not pull it in or
         * even require it. */
        r = unit_add_dependency_by_name(UNIT(s), UNIT_AFTER, SPECIAL_BASIC_TARGET, true, UNIT_DEPENDENCY_DEFAULT);
        if (r < 0)
                return r;

        /* Third, add us in for normal shutdown. */
        return unit_add_two_dependencies_by_name(UNIT(s), UNIT_BEFORE, UNIT_CONFLICTS, SPECIAL_SHUTDOWN_TARGET, true, UNIT_DEPENDENCY_DEFAULT);
}