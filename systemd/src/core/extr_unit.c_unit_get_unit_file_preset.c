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
struct TYPE_6__ {scalar_t__ unit_file_preset; scalar_t__ fragment_path; TYPE_1__* manager; } ;
typedef  TYPE_2__ Unit ;
struct TYPE_5__ {int /*<<< orphan*/  unit_file_scope; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  basename (scalar_t__) ; 
 scalar_t__ unit_file_query_preset (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int unit_get_unit_file_preset(Unit *u) {
        assert(u);

        if (u->unit_file_preset < 0 && u->fragment_path)
                u->unit_file_preset = unit_file_query_preset(
                                u->manager->unit_file_scope,
                                NULL,
                                basename(u->fragment_path));

        return u->unit_file_preset;
}