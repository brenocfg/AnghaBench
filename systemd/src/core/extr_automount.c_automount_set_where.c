#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
struct TYPE_6__ {scalar_t__ where; } ;
typedef  TYPE_1__ Automount ;

/* Variables and functions */
 TYPE_4__* UNIT (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  path_simplify (scalar_t__,int) ; 
 int unit_name_to_path (int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int automount_set_where(Automount *a) {
        int r;

        assert(a);

        if (a->where)
                return 0;

        r = unit_name_to_path(UNIT(a)->id, &a->where);
        if (r < 0)
                return r;

        path_simplify(a->where, false);
        return 1;
}