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
typedef  scalar_t__ AutomountResult ;
typedef  TYPE_1__ Automount ;

/* Variables and functions */
 int /*<<< orphan*/  AUTOMOUNT_DEAD ; 
 int /*<<< orphan*/  AUTOMOUNT_FAILED ; 
 scalar_t__ AUTOMOUNT_SUCCESS ; 
 int /*<<< orphan*/  UNIT (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  automount_result_to_string (scalar_t__) ; 
 int /*<<< orphan*/  automount_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_log_result (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void automount_enter_dead(Automount *a, AutomountResult f) {
        assert(a);

        if (a->result == AUTOMOUNT_SUCCESS)
                a->result = f;

        unit_log_result(UNIT(a), a->result == AUTOMOUNT_SUCCESS, automount_result_to_string(a->result));
        automount_set_state(a, a->result != AUTOMOUNT_SUCCESS ? AUTOMOUNT_FAILED : AUTOMOUNT_DEAD);
}