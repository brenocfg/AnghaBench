#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zthr_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  SPA_FEATURE_POOL_CHECKPOINT ; 
 int /*<<< orphan*/  spa_feature_is_active (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_has_checkpoint (int /*<<< orphan*/ *) ; 

boolean_t
spa_checkpoint_discard_thread_check(void *arg, zthr_t *zthr)
{
	spa_t *spa = arg;

	if (!spa_feature_is_active(spa, SPA_FEATURE_POOL_CHECKPOINT))
		return (B_FALSE);

	if (spa_has_checkpoint(spa))
		return (B_FALSE);

	return (B_TRUE);
}