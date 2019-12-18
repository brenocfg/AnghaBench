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
struct window_tree_modedata {int dead; int /*<<< orphan*/  data; } ;
struct window_mode_entry {struct window_tree_modedata* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  mode_tree_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  window_tree_destroy (struct window_tree_modedata*) ; 

__attribute__((used)) static void
window_tree_free(struct window_mode_entry *wme)
{
	struct window_tree_modedata *data = wme->data;

	if (data == NULL)
		return;

	data->dead = 1;
	mode_tree_free(data->data);
	window_tree_destroy(data);
}