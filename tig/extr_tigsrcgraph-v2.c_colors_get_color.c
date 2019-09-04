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
struct colors {int /*<<< orphan*/  id_map; } ;

/* Variables and functions */
 scalar_t__ htab_find (int /*<<< orphan*/ ,struct id_color*) ; 
 int /*<<< orphan*/  id_color_delete (struct id_color*) ; 
 struct id_color* id_color_new (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
colors_get_color(struct colors *colors, const char *id)
{
	struct id_color *key = id_color_new(id, 0);
	struct id_color *node = (struct id_color *) htab_find(colors->id_map, key);

	id_color_delete(key);

	if (node == NULL) {
		return (size_t) -1; // Max value of size_t. ID not found.
	}
	return node->color;
}