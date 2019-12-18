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
 int /*<<< orphan*/  ASSERT (char*) ; 

uint_t
mod_hash_bystr(void *hash_data, mod_hash_key_t key)
{
	uint_t hash = 0;
	uint_t g;
	char *p, *k = (char *)key;

	ASSERT(k);
	for (p = k; *p != '\0'; p++) {
		hash = (hash << 4) + *p;
		if ((g = (hash & 0xf0000000)) != 0) {
			hash ^= (g >> 24);
			hash ^= g;
		}
	}
	return (hash);
}