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
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_6__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ Path ;

/* Variables and functions */
 TYPE_1__* IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* PATH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PATH_RUNNING ; 
 int /*<<< orphan*/  PATH_SUCCESS ; 
 int /*<<< orphan*/  PATH_WAITING ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  path_enter_dead (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int path_stop(Unit *u) {
        Path *p = PATH(u);

        assert(p);
        assert(IN_SET(p->state, PATH_WAITING, PATH_RUNNING));

        path_enter_dead(p, PATH_SUCCESS);
        return 1;
}