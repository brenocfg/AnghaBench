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
struct TYPE_4__ {int /*<<< orphan*/  refuse_manual_start; } ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 scalar_t__ unit_can_start (TYPE_1__*) ; 

__attribute__((used)) static bool unit_can_start_refuse_manual(Unit *u) {
        return unit_can_start(u) && !u->refuse_manual_start;
}