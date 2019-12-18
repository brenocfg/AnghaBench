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
 int WINDOW_COPY_CMD_CANCEL ; 
 int WINDOW_COPY_CMD_NOTHING ; 
 scalar_t__ window_copy_pagedown (struct window_mode_entry*,int,int) ; 

__attribute__((used)) static enum window_copy_cmd_action
window_copy_cmd_halfpage_down_and_cancel(struct window_copy_cmd_state *cs)
{

	struct window_mode_entry	*wme = cs->wme;
	u_int				 np = wme->prefix;

	for (; np != 0; np--) {
		if (window_copy_pagedown(wme, 1, 1))
			return (WINDOW_COPY_CMD_CANCEL);
	}
	return (WINDOW_COPY_CMD_NOTHING);
}