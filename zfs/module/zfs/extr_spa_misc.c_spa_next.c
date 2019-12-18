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
typedef  int /*<<< orphan*/  spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * AVL_NEXT (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * avl_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_namespace_avl ; 
 int /*<<< orphan*/  spa_namespace_lock ; 

spa_t *
spa_next(spa_t *prev)
{
	ASSERT(MUTEX_HELD(&spa_namespace_lock));

	if (prev)
		return (AVL_NEXT(&spa_namespace_avl, prev));
	else
		return (avl_first(&spa_namespace_avl));
}