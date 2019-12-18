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
struct TYPE_3__ {scalar_t__ spa_minref; int /*<<< orphan*/  spa_refcount; } ;
typedef  TYPE_1__ spa_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 scalar_t__ zfs_refcount_count (int /*<<< orphan*/ *) ; 

boolean_t
spa_refcount_zero(spa_t *spa)
{
	ASSERT(MUTEX_HELD(&spa_namespace_lock));

	return (zfs_refcount_count(&spa->spa_refcount) == spa->spa_minref);
}