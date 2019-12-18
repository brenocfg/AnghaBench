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
typedef  int uint64_t ;
struct TYPE_3__ {int sh_phys_max_off; int sh_pool_create_len; } ;
typedef  TYPE_1__ spa_history_phys_t ;

/* Variables and functions */

__attribute__((used)) static uint64_t
spa_history_log_to_phys(uint64_t log_off, spa_history_phys_t *shpp)
{
	uint64_t phys_len;

	phys_len = shpp->sh_phys_max_off - shpp->sh_pool_create_len;
	return ((log_off - shpp->sh_pool_create_len) % phys_len
	    + shpp->sh_pool_create_len);
}