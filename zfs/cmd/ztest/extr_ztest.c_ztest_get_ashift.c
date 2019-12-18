#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_2__ {scalar_t__ zo_ashift; } ;

/* Variables and functions */
 scalar_t__ SPA_MINBLOCKSHIFT ; 
 TYPE_1__ ztest_opts ; 
 scalar_t__ ztest_random (int) ; 

__attribute__((used)) static uint64_t
ztest_get_ashift(void)
{
	if (ztest_opts.zo_ashift == 0)
		return (SPA_MINBLOCKSHIFT + ztest_random(5));
	return (ztest_opts.zo_ashift);
}