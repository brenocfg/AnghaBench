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
struct TYPE_6__ {scalar_t__ result; } ;
typedef  scalar_t__ PathResult ;
typedef  TYPE_1__ Path ;

/* Variables and functions */
 int /*<<< orphan*/  PATH_DEAD ; 
 int /*<<< orphan*/  PATH_FAILED ; 
 scalar_t__ PATH_SUCCESS ; 
 int /*<<< orphan*/  UNIT (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  path_result_to_string (scalar_t__) ; 
 int /*<<< orphan*/  path_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_log_result (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void path_enter_dead(Path *p, PathResult f) {
        assert(p);

        if (p->result == PATH_SUCCESS)
                p->result = f;

        unit_log_result(UNIT(p), p->result == PATH_SUCCESS, path_result_to_string(p->result));
        path_set_state(p, p->result != PATH_SUCCESS ? PATH_FAILED : PATH_DEAD);
}