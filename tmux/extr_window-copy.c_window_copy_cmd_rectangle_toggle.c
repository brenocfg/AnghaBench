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
struct window_mode_entry {struct window_copy_mode_data* data; } ;
struct window_copy_mode_data {int /*<<< orphan*/  lineflag; } ;
struct window_copy_cmd_state {struct window_mode_entry* wme; } ;
typedef  enum window_copy_cmd_action { ____Placeholder_window_copy_cmd_action } window_copy_cmd_action ;

/* Variables and functions */
 int /*<<< orphan*/  LINE_SEL_NONE ; 
 int WINDOW_COPY_CMD_NOTHING ; 
 int /*<<< orphan*/  window_copy_rectangle_toggle (struct window_mode_entry*) ; 

__attribute__((used)) static enum window_copy_cmd_action
window_copy_cmd_rectangle_toggle(struct window_copy_cmd_state *cs)
{
	struct window_mode_entry	*wme = cs->wme;
	struct window_copy_mode_data	*data = wme->data;

	data->lineflag = LINE_SEL_NONE;
	window_copy_rectangle_toggle(wme);

	return (WINDOW_COPY_CMD_NOTHING);
}