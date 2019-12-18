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
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_4__ {scalar_t__ state; scalar_t__ will_auto_restart; } ;
typedef  TYPE_1__ Service ;

/* Variables and functions */
 TYPE_1__* SERVICE (int /*<<< orphan*/ *) ; 
 scalar_t__ SERVICE_AUTO_RESTART ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int unit_will_restart_default (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool service_will_restart(Unit *u) {
        Service *s = SERVICE(u);

        assert(s);

        if (s->will_auto_restart)
                return true;
        if (s->state == SERVICE_AUTO_RESTART)
                return true;

        return unit_will_restart_default(u);
}