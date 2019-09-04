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
struct enum_map_entry {int value; } ;

/* Variables and functions */
 scalar_t__ enum_equals (struct enum_map_entry const,char const*,size_t) ; 
 size_t strlen (char const*) ; 

bool
map_enum_do(const struct enum_map_entry *map, size_t map_size, int *value, const char *name)
{
	size_t namelen = strlen(name);
	int i;

	for (i = 0; i < map_size; i++)
		if (enum_equals(map[i], name, namelen)) {
			*value = map[i].value;
			return true;
		}

	return false;
}