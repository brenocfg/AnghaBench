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
struct TYPE_4__ {int /*<<< orphan*/ * specs; } ;
typedef  int /*<<< orphan*/  PathSpec ;
typedef  TYPE_1__ Path ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path_spec_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path_spec_unwatch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spec ; 

void path_free_specs(Path *p) {
        PathSpec *s;

        assert(p);

        while ((s = p->specs)) {
                path_spec_unwatch(s);
                LIST_REMOVE(spec, p->specs, s);
                path_spec_done(s);
                free(s);
        }
}