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
typedef  int /*<<< orphan*/  UnitActiveState ;

/* Variables and functions */
 int /*<<< orphan*/  ELEMENTSOF (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EXIT_PROGRAM_DEAD_AND_PID_EXISTS ; 
#define  UNIT_FAILED 128 
 int check_unit_generic (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strv_skip (char**,int) ; 

__attribute__((used)) static int check_unit_failed(int argc, char *argv[], void *userdata) {
        static const UnitActiveState states[] = {
                UNIT_FAILED,
        };

        return check_unit_generic(EXIT_PROGRAM_DEAD_AND_PID_EXISTS, states, ELEMENTSOF(states), strv_skip(argv, 1));
}