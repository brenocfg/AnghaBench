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
struct window_mode_entry {struct window_client_modedata* data; } ;
struct window_client_modedata {size_t item_size; struct window_client_modedata* command; struct window_client_modedata* format; struct window_client_modedata* item_list; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct window_client_modedata*) ; 
 int /*<<< orphan*/  mode_tree_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  window_client_free_item (struct window_client_modedata) ; 

__attribute__((used)) static void
window_client_free(struct window_mode_entry *wme)
{
	struct window_client_modedata	*data = wme->data;
	u_int				 i;

	if (data == NULL)
		return;

	mode_tree_free(data->data);

	for (i = 0; i < data->item_size; i++)
		window_client_free_item(data->item_list[i]);
	free(data->item_list);

	free(data->format);
	free(data->command);

	free(data);
}