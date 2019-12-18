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
typedef  int /*<<< orphan*/  mod_hash_key_t ;

/* Variables and functions */

int
mod_hash_ptrkey_cmp(mod_hash_key_t key1, mod_hash_key_t key2)
{
	uintptr_t k1 = (uintptr_t)key1;
	uintptr_t k2 = (uintptr_t)key2;
	if (k1 > k2)
		return (-1);
	else if (k1 < k2)
		return (1);
	else
		return (0);
}