#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct window_mode_entry {scalar_t__ prefix; struct window_copy_mode_data* data; } ;
struct window_copy_mode_data {char jumpchar; int /*<<< orphan*/  jumptype; } ;
struct window_copy_cmd_state {TYPE_1__* args; struct window_mode_entry* wme; } ;
typedef  enum window_copy_cmd_action { ____Placeholder_window_copy_cmd_action } window_copy_cmd_action ;
struct TYPE_2__ {char** argv; } ;

/* Variables and functions */
 int WINDOW_COPY_CMD_NOTHING ; 
 int /*<<< orphan*/  WINDOW_COPY_JUMPTOFORWARD ; 
 int /*<<< orphan*/  window_copy_cursor_jump_to (struct window_mode_entry*) ; 

__attribute__((used)) static enum window_copy_cmd_action
window_copy_cmd_jump_to_forward(struct window_copy_cmd_state *cs)
{
	struct window_mode_entry	*wme = cs->wme;
	struct window_copy_mode_data	*data = wme->data;
	u_int				 np = wme->prefix;
	const char			*argument = cs->args->argv[1];

	if (*argument != '\0') {
		data->jumptype = WINDOW_COPY_JUMPTOFORWARD;
		data->jumpchar = *argument;
		for (; np != 0; np--)
			window_copy_cursor_jump_to(wme);
	}
	return (WINDOW_COPY_CMD_NOTHING);
}