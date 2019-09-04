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
struct window_tree_modedata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  window_tree_destroy (struct window_tree_modedata*) ; 

__attribute__((used)) static void
window_tree_command_free(void *modedata)
{
	struct window_tree_modedata	*data = modedata;

	window_tree_destroy(data);
}