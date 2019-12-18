#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* path; struct TYPE_6__* name; } ;
typedef  TYPE_1__ UnitStatusInfo ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  unit_status_info_clear (TYPE_1__*) ; 

__attribute__((used)) static void unit_status_info_free(UnitStatusInfo *p) {
        assert(p);

        unit_status_info_clear(p);
        free(p->name);
        free(p->path);
        free(p);
}