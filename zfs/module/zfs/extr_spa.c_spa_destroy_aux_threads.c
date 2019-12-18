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
struct TYPE_3__ {int /*<<< orphan*/ * spa_livelist_condense_zthr; int /*<<< orphan*/ * spa_livelist_delete_zthr; int /*<<< orphan*/ * spa_checkpoint_discard_zthr; int /*<<< orphan*/ * spa_condense_zthr; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  zthr_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
spa_destroy_aux_threads(spa_t *spa)
{
	if (spa->spa_condense_zthr != NULL) {
		zthr_destroy(spa->spa_condense_zthr);
		spa->spa_condense_zthr = NULL;
	}
	if (spa->spa_checkpoint_discard_zthr != NULL) {
		zthr_destroy(spa->spa_checkpoint_discard_zthr);
		spa->spa_checkpoint_discard_zthr = NULL;
	}
	if (spa->spa_livelist_delete_zthr != NULL) {
		zthr_destroy(spa->spa_livelist_delete_zthr);
		spa->spa_livelist_delete_zthr = NULL;
	}
	if (spa->spa_livelist_condense_zthr != NULL) {
		zthr_destroy(spa->spa_livelist_condense_zthr);
		spa->spa_livelist_condense_zthr = NULL;
	}
}