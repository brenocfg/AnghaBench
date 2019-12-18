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
typedef  int uint_t ;
typedef  scalar_t__ mod_hash_key_t ;

/* Variables and functions */

uint_t
mod_hash_byid(void *hash_data, mod_hash_key_t key)
{
	uint_t kval = (uint_t)(uintptr_t)hash_data;
	return ((uint_t)(uintptr_t)key * (uint_t)kval);
}