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
typedef  int /*<<< orphan*/  u_int ;
struct window_tree_modedata {int /*<<< orphan*/  data; } ;
struct window_mode_entry {struct window_tree_modedata* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  mode_tree_resize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
window_tree_resize(struct window_mode_entry *wme, u_int sx, u_int sy)
{
	struct window_tree_modedata	*data = wme->data;

	mode_tree_resize(data->data, sx, sy);
}