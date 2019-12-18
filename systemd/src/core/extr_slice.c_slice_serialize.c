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
typedef  TYPE_1__ Slice ;
typedef  TYPE_1__ FILE ;
typedef  TYPE_1__ FDSet ;

/* Variables and functions */
 TYPE_1__* SLICE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  serialize_item (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slice_state_to_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int slice_serialize(Unit *u, FILE *f, FDSet *fds) {
        Slice *s = SLICE(u);

        assert(s);
        assert(f);
        assert(fds);

        (void) serialize_item(f, "state", slice_state_to_string(s->state));

        return 0;
}