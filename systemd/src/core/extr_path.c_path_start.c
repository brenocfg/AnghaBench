#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_8__ {int /*<<< orphan*/  result; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ Path ;

/* Variables and functions */
 TYPE_1__* IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* PATH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PATH_DEAD ; 
 int /*<<< orphan*/  PATH_FAILED ; 
 int /*<<< orphan*/  PATH_FAILURE_START_LIMIT_HIT ; 
 int /*<<< orphan*/  PATH_SUCCESS ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  path_enter_dead (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_enter_waiting (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  path_mkdir (TYPE_1__*) ; 
 int unit_acquire_invocation_id (int /*<<< orphan*/ *) ; 
 int unit_test_start_limit (int /*<<< orphan*/ *) ; 
 int unit_test_trigger_loaded (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int path_start(Unit *u) {
        Path *p = PATH(u);
        int r;

        assert(p);
        assert(IN_SET(p->state, PATH_DEAD, PATH_FAILED));

        r = unit_test_trigger_loaded(u);
        if (r < 0)
                return r;

        r = unit_test_start_limit(u);
        if (r < 0) {
                path_enter_dead(p, PATH_FAILURE_START_LIMIT_HIT);
                return r;
        }

        r = unit_acquire_invocation_id(u);
        if (r < 0)
                return r;

        path_mkdir(p);

        p->result = PATH_SUCCESS;
        path_enter_waiting(p, true, true);

        return 1;
}