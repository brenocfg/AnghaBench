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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;

/* Variables and functions */
 int MAX (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIN (int,int /*<<< orphan*/ ) ; 
 int spa_get_dspace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_min_slop ; 
 int spa_slop_shift ; 

uint64_t
spa_get_slop_space(spa_t *spa)
{
	uint64_t space = spa_get_dspace(spa);
	return (MAX(space >> spa_slop_shift, MIN(space >> 1, spa_min_slop)));
}