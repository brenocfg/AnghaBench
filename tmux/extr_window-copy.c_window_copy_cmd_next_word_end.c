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
struct window_copy_cmd_state {struct session* s; struct window_mode_entry* wme; } ;
struct session {int /*<<< orphan*/  options; } ;
typedef  enum window_copy_cmd_action { ____Placeholder_window_copy_cmd_action } window_copy_cmd_action ;

/* Variables and functions */
 int WINDOW_COPY_CMD_NOTHING ; 
 char* options_get_string (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  window_copy_cursor_next_word_end (struct window_mode_entry*,char const*) ; 

__attribute__((used)) static enum window_copy_cmd_action
window_copy_cmd_next_word_end(struct window_copy_cmd_state *cs)
{
	struct window_mode_entry	*wme = cs->wme;
	struct session			*s = cs->s;
	u_int				 np = wme->prefix;
	const char			*ws;

	ws = options_get_string(s->options, "word-separators");
	for (; np != 0; np--)
		window_copy_cursor_next_word_end(wme, ws);
	return (WINDOW_COPY_CMD_NOTHING);
}