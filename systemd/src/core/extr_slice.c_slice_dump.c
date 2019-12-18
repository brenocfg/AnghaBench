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

/* Variables and functions */
 TYPE_1__* SLICE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNIT (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  cgroup_context_dump (int /*<<< orphan*/ ,TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  fprintf (TYPE_1__*,char*,char const*,char*) ; 
 char* slice_state_to_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void slice_dump(Unit *u, FILE *f, const char *prefix) {
        Slice *t = SLICE(u);

        assert(t);
        assert(f);

        fprintf(f,
                "%sSlice State: %s\n",
                prefix, slice_state_to_string(t->state));

        cgroup_context_dump(UNIT(t), f, prefix);
}