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
struct string_map {char const* key; scalar_t__ htab; } ;

/* Variables and functions */
 void* htab_find_with_hash (scalar_t__,struct string_map*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htab_hash_string (char const*) ; 

void *
string_map_get(struct string_map *map, const char *key)
{
	if (map->htab) {
		map->key = key;
		return htab_find_with_hash(map->htab, map, htab_hash_string(key));
	}

	return NULL;
}