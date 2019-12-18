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
typedef  int /*<<< orphan*/  uint_t ;
typedef  scalar_t__ mod_hash_key_t ;

/* Variables and functions */

uint_t
mod_hash_byptr(void *hash_data, mod_hash_key_t key)
{
	uintptr_t k = (uintptr_t)key;
	k >>= (int)(uintptr_t)hash_data;

	return ((uint_t)k);
}