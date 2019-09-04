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
struct window_mode_entry {int dummy; } ;
struct window_copy_cmd_state {struct window_mode_entry* wme; } ;
typedef  enum window_copy_cmd_action { ____Placeholder_window_copy_cmd_action } window_copy_cmd_action ;

/* Variables and functions */
 int WINDOW_COPY_CMD_CANCEL ; 
 int /*<<< orphan*/  window_copy_clear_selection (struct window_mode_entry*) ; 
 int /*<<< orphan*/  window_copy_cmd_copy_selection_no_clear (struct window_copy_cmd_state*) ; 

__attribute__((used)) static enum window_copy_cmd_action
window_copy_cmd_copy_selection_and_cancel(struct window_copy_cmd_state *cs)
{
	struct window_mode_entry	*wme = cs->wme;

	window_copy_cmd_copy_selection_no_clear(cs);
	window_copy_clear_selection(wme);
	return (WINDOW_COPY_CMD_CANCEL);
}