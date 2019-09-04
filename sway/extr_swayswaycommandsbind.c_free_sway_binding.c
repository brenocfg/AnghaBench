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
struct sway_binding {struct sway_binding* command; struct sway_binding* input; int /*<<< orphan*/  syms; int /*<<< orphan*/  keys; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct sway_binding*) ; 
 int /*<<< orphan*/  list_free_items_and_destroy (int /*<<< orphan*/ ) ; 

void free_sway_binding(struct sway_binding *binding) {
	if (!binding) {
		return;
	}

	list_free_items_and_destroy(binding->keys);
	list_free_items_and_destroy(binding->syms);
	free(binding->input);
	free(binding->command);
	free(binding);
}