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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {scalar_t__ type; } ;
typedef  TYPE_1__ Unit ;
struct TYPE_7__ {size_t kill_context_offset; } ;
typedef  int /*<<< orphan*/  KillContext ;

/* Variables and functions */
 TYPE_4__* UNIT_VTABLE (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

KillContext *unit_get_kill_context(Unit *u) {
        size_t offset;
        assert(u);

        if (u->type < 0)
                return NULL;

        offset = UNIT_VTABLE(u)->kill_context_offset;
        if (offset <= 0)
                return NULL;

        return (KillContext*) ((uint8_t*) u + offset);
}