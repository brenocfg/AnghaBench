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
 int /*<<< orphan*/  spa_livelist_delete_check (int /*<<< orphan*/ *) ; 

__attribute__((used)) static boolean_t
spa_livelist_delete_cb_check(void *arg, zthr_t *z)
{
	spa_t *spa = arg;
	return (spa_livelist_delete_check(spa));
}