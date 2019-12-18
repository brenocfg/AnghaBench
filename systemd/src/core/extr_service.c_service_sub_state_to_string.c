#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 TYPE_1__* SERVICE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 char const* service_state_to_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *service_sub_state_to_string(Unit *u) {
        assert(u);

        return service_state_to_string(SERVICE(u)->state);
}