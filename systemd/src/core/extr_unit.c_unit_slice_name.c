#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  slice; } ;
typedef  TYPE_1__ Unit ;
struct TYPE_6__ {char const* id; } ;

/* Variables and functions */
 TYPE_4__* UNIT_DEREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNIT_ISSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

const char *unit_slice_name(Unit *u) {
        assert(u);

        if (!UNIT_ISSET(u->slice))
                return NULL;

        return UNIT_DEREF(u->slice)->id;
}