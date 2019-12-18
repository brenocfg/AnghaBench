#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_9__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ Target ;
typedef  TYPE_1__ FILE ;
typedef  TYPE_1__ FDSet ;

/* Variables and functions */
 TYPE_1__* TARGET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  serialize_item (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_state_to_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int target_serialize(Unit *u, FILE *f, FDSet *fds) {
        Target *s = TARGET(u);

        assert(s);
        assert(f);
        assert(fds);

        (void) serialize_item(f, "state", target_state_to_string(s->state));
        return 0;
}