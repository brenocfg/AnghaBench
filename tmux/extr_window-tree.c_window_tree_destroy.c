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
typedef  size_t u_int ;
struct window_tree_modedata {scalar_t__ references; size_t item_size; struct window_tree_modedata* command; struct window_tree_modedata* format; struct window_tree_modedata* item_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct window_tree_modedata*) ; 
 int /*<<< orphan*/  window_tree_free_item (struct window_tree_modedata) ; 

__attribute__((used)) static void
window_tree_destroy(struct window_tree_modedata *data)
{
	u_int	i;

	if (--data->references != 0)
		return;

	for (i = 0; i < data->item_size; i++)
		window_tree_free_item(data->item_list[i]);
	free(data->item_list);

	free(data->format);
	free(data->command);

	free(data);
}