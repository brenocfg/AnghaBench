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
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {int spa_max_ashift; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */
 scalar_t__ MAX (scalar_t__,int) ; 
 scalar_t__ spa_asize_inflation ; 

uint64_t
spa_get_worst_case_asize(spa_t *spa, uint64_t lsize)
{
	if (lsize == 0)
		return (0);	/* No inflation needed */
	return (MAX(lsize, 1 << spa->spa_max_ashift) * spa_asize_inflation);
}