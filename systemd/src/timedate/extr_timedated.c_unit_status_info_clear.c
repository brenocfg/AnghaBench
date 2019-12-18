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
struct TYPE_4__ {void* active_state; void* unit_file_state; void* load_state; } ;
typedef  TYPE_1__ UnitStatusInfo ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 void* mfree (void*) ; 

__attribute__((used)) static void unit_status_info_clear(UnitStatusInfo *p) {
        assert(p);

        p->load_state = mfree(p->load_state);
        p->unit_file_state = mfree(p->unit_file_state);
        p->active_state = mfree(p->active_state);
}