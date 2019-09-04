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
struct id_color {size_t color; } ;
struct colors {int /*<<< orphan*/  id_map; int /*<<< orphan*/ * count; } ;

/* Variables and functions */
 int /*<<< orphan*/  NO_INSERT ; 
 int /*<<< orphan*/  htab_clear_slot (int /*<<< orphan*/ ,void**) ; 
 void** htab_find_slot (int /*<<< orphan*/ ,struct id_color*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  id_color_delete (struct id_color*) ; 
 struct id_color* id_color_new (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
colors_remove_id(struct colors *colors, const char *id)
{
	struct id_color *node = id_color_new(id, 0);
	void **slot = htab_find_slot(colors->id_map, node, NO_INSERT);

	if (slot != NULL && *slot != NULL) {
		colors->count[((struct id_color *) *slot)->color]--;
		htab_clear_slot(colors->id_map, slot);
	}

	id_color_delete(node);
}