#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_5__ {scalar_t__ state; int /*<<< orphan*/  result; } ;
typedef  TYPE_1__ Path ;

/* Variables and functions */
 TYPE_1__* PATH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PATH_DEAD ; 
 scalar_t__ PATH_FAILED ; 
 int /*<<< orphan*/  PATH_SUCCESS ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  path_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void path_reset_failed(Unit *u) {
        Path *p = PATH(u);

        assert(p);

        if (p->state == PATH_FAILED)
                path_set_state(p, PATH_DEAD);

        p->result = PATH_SUCCESS;
}