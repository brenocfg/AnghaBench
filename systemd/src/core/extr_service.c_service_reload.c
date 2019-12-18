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
typedef  TYPE_1__ Service ;

/* Variables and functions */
 TYPE_1__* IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* SERVICE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SERVICE_EXITED ; 
 int /*<<< orphan*/  SERVICE_RUNNING ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  service_enter_reload (TYPE_1__*) ; 

__attribute__((used)) static int service_reload(Unit *u) {
        Service *s = SERVICE(u);

        assert(s);

        assert(IN_SET(s->state, SERVICE_RUNNING, SERVICE_EXITED));

        service_enter_reload(s);
        return 1;
}