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
struct TYPE_3__ {int /*<<< orphan*/ * spa_condensing_indirect; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  spa_condensing_indirect_destroy (int /*<<< orphan*/ *) ; 

void
spa_condense_fini(spa_t *spa)
{
	if (spa->spa_condensing_indirect != NULL) {
		spa_condensing_indirect_destroy(spa->spa_condensing_indirect);
		spa->spa_condensing_indirect = NULL;
	}
}