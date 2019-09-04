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
struct ea_name_index {char const* name; int index; } ;

/* Variables and functions */
 struct ea_name_index* ea_names ; 

__attribute__((used)) static const char *find_ea_prefix(int index)
{
	struct ea_name_index *e;

	for (e = ea_names; e->name; e++)
		if (e->index == index)
			return e->name;

	return NULL;
}