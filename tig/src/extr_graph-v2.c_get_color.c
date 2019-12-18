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
struct graph_v2 {int /*<<< orphan*/  colors; } ;

/* Variables and functions */
 int /*<<< orphan*/  colors_add_id (int /*<<< orphan*/ *,char const*,size_t) ; 
 size_t colors_get_color (int /*<<< orphan*/ *,char const*) ; 
 size_t colors_get_free_color (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  colors_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t
get_color(struct graph_v2 *graph, const char *new_id)
{
	size_t color;

	if (!new_id)
		new_id = "";

	colors_init(&graph->colors);
	color = colors_get_color(&graph->colors, new_id);

	if (color < (size_t) -1) {
		return color;
	}

	color = colors_get_free_color(&graph->colors);
	colors_add_id(&graph->colors, new_id, color);

	return color;
}