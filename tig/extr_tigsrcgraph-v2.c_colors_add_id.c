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
struct id_color {int dummy; } ;
struct colors {int /*<<< orphan*/ * count; int /*<<< orphan*/  id_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  INSERT ; 
 void** htab_find_slot (int /*<<< orphan*/ ,struct id_color*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  id_color_delete (struct id_color*) ; 
 struct id_color* id_color_new (char const*,size_t const) ; 

__attribute__((used)) static void
colors_add_id(struct colors *colors, const char *id, const size_t color)
{
	struct id_color *node = id_color_new(id, color);
	void **slot = htab_find_slot(colors->id_map, node, INSERT);

	if (slot != NULL && *slot == NULL) {
		*slot = node;
		colors->count[color]++;
	} else {
		id_color_delete(node);
	}
}