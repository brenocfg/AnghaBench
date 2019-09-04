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
struct string_map {scalar_t__ htab; } ;

/* Variables and functions */
 int /*<<< orphan*/  htab_empty (scalar_t__) ; 

void
string_map_clear(struct string_map *map)
{
	if (map->htab)
		htab_empty(map->htab);
}