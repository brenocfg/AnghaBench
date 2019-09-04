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
typedef  scalar_t__ u_int ;
struct window_mode_entry {scalar_t__ prefix; } ;
struct window_copy_cmd_state {struct window_mode_entry* wme; } ;
typedef  enum window_copy_cmd_action { ____Placeholder_window_copy_cmd_action } window_copy_cmd_action ;

/* Variables and functions */
 int WINDOW_COPY_CMD_NOTHING ; 
 int /*<<< orphan*/  window_copy_cursor_up (struct window_mode_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum window_copy_cmd_action
window_copy_cmd_cursor_up(struct window_copy_cmd_state *cs)
{
	struct window_mode_entry	*wme = cs->wme;
	u_int				 np = wme->prefix;

	for (; np != 0; np--)
		window_copy_cursor_up(wme, 0);
	return (WINDOW_COPY_CMD_NOTHING);
}