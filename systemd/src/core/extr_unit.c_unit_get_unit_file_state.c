#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UnitFileState ;
struct TYPE_6__ {scalar_t__ unit_file_state; int /*<<< orphan*/  id; TYPE_1__* manager; scalar_t__ fragment_path; } ;
typedef  TYPE_2__ Unit ;
struct TYPE_5__ {int /*<<< orphan*/  unit_file_scope; } ;

/* Variables and functions */
 scalar_t__ UNIT_FILE_BAD ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int unit_file_get_state (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 

UnitFileState unit_get_unit_file_state(Unit *u) {
        int r;

        assert(u);

        if (u->unit_file_state < 0 && u->fragment_path) {
                r = unit_file_get_state(
                                u->manager->unit_file_scope,
                                NULL,
                                u->id,
                                &u->unit_file_state);
                if (r < 0)
                        u->unit_file_state = UNIT_FILE_BAD;
        }

        return u->unit_file_state;
}