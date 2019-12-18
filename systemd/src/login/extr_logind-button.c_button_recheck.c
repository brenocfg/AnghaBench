#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sd_event_source ;
struct TYPE_3__ {int /*<<< orphan*/  manager; struct TYPE_3__* lid_closed; } ;
typedef  TYPE_1__ Button ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  button_lid_switch_handle_action (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int button_recheck(sd_event_source *e, void *userdata) {
        Button *b = userdata;

        assert(b);
        assert(b->lid_closed);

        button_lid_switch_handle_action(b->manager, false);
        return 1;
}