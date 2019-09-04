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
struct window_mode_entry {int dummy; } ;
struct window_copy_cmd_state {TYPE_1__* args; struct window_mode_entry* wme; } ;
typedef  enum window_copy_cmd_action { ____Placeholder_window_copy_cmd_action } window_copy_cmd_action ;
struct TYPE_2__ {char** argv; } ;

/* Variables and functions */
 int WINDOW_COPY_CMD_NOTHING ; 
 int /*<<< orphan*/  window_copy_goto_line (struct window_mode_entry*,char const*) ; 

__attribute__((used)) static enum window_copy_cmd_action
window_copy_cmd_goto_line(struct window_copy_cmd_state *cs)
{
	struct window_mode_entry	*wme = cs->wme;
	const char			*argument = cs->args->argv[1];

	if (*argument != '\0')
		window_copy_goto_line(wme, argument);
	return (WINDOW_COPY_CMD_NOTHING);
}