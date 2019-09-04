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
struct string_map_iterator {void* member_1; int /*<<< orphan*/  member_0; } ;
struct string_map {scalar_t__ htab; } ;
typedef  int /*<<< orphan*/  string_map_iterator_fn ;

/* Variables and functions */
 int /*<<< orphan*/  htab_traverse_noresize (scalar_t__,int /*<<< orphan*/ ,struct string_map_iterator*) ; 
 int /*<<< orphan*/  string_map_iterate ; 

void
string_map_foreach(struct string_map *map, string_map_iterator_fn fn, void *data)
{
	if (map->htab) {
		struct string_map_iterator iterator = { fn, data };

		htab_traverse_noresize(map->htab, string_map_iterate, &iterator);
	}
}