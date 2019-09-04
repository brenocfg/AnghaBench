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
struct window_pane {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 struct window_pane* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct window_pane*) ; 
 int /*<<< orphan*/  all_window_panes ; 
 int /*<<< orphan*/  window_pane_tree ; 

struct window_pane *
window_pane_find_by_id(u_int id)
{
	struct window_pane	wp;

	wp.id = id;
	return (RB_FIND(window_pane_tree, &all_window_panes, &wp));
}