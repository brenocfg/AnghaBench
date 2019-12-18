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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int arc_all_memory () ; 
 int /*<<< orphan*/  spa_get_random (int) ; 

uint64_t
arc_free_memory(void)
{
	return (spa_get_random(arc_all_memory() * 20 / 100));
}