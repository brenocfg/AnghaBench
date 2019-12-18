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
struct string_map {int dummy; } ;

/* Variables and functions */
 void** string_map_put_to (struct string_map*,char const*) ; 

void *
string_map_put(struct string_map *map, const char *key, void *value)
{
	void **slot = string_map_put_to(map, key);

	if (!slot)
		return NULL;

	*slot = value;
	return value;
}