#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  current; } ;
typedef  TYPE_1__ ChunkAppendState ;

/* Variables and functions */
 int /*<<< orphan*/  NO_MATCHING_SUBPLANS ; 

__attribute__((used)) static void
choose_next_subplan_for_leader(ChunkAppendState *state)
{
	state->current = NO_MATCHING_SUBPLANS;
}