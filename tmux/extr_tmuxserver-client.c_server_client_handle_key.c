#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct winlink {struct window* window; } ;
struct window_pane {int /*<<< orphan*/  id; int /*<<< orphan*/  modes; } ;
struct window_mode_entry {TYPE_2__* mode; } ;
struct window {int dummy; } ;
struct timeval {int tv_sec; int tv_usec; } ;
struct session {int /*<<< orphan*/  options; struct winlink* curw; } ;
struct mouse_event {int valid; char key; } ;
struct key_table {int /*<<< orphan*/  name; int /*<<< orphan*/  references; } ;
struct key_binding {int flags; } ;
struct cmd_find_state {struct window_pane* wp; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* mouse_drag_update ) (struct client*,struct mouse_event*) ;struct mouse_event mouse; } ;
struct client {int flags; struct key_table* keytable; int /*<<< orphan*/  repeat_timer; TYPE_1__ tty; int /*<<< orphan*/ * prompt_string; int /*<<< orphan*/  activity_time; struct session* session; } ;
typedef  char key_code ;
struct TYPE_4__ {int /*<<< orphan*/  (* key_table ) (struct window_mode_entry*) ;} ;

/* Variables and functions */
 int CLIENT_DEAD ; 
 int CLIENT_IDENTIFY ; 
 int CLIENT_READONLY ; 
 int CLIENT_REPEAT ; 
 int CLIENT_SUSPENDED ; 
 char KEYC_ANY ; 
 char KEYC_DRAGGING ; 
 scalar_t__ KEYC_IS_MOUSE (char) ; 
 char KEYC_MOUSE ; 
 char KEYC_UNKNOWN ; 
 char KEYC_XTERM ; 
 int KEY_BINDING_REPEAT ; 
 struct window_mode_entry* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 scalar_t__ cmd_find_from_mouse (struct cmd_find_state*,struct mouse_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmd_find_from_session (struct cmd_find_state*,struct session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evtimer_add (int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  evtimer_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 scalar_t__ gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_bindings_dispatch (struct key_binding*,int /*<<< orphan*/ *,struct client*,struct mouse_event*,struct cmd_find_state*) ; 
 struct key_binding* key_bindings_get (struct key_table*,char) ; 
 struct key_table* key_bindings_get_table (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  key_bindings_unref_table (struct key_table*) ; 
 int /*<<< orphan*/  log_debug (char*,...) ; 
 int options_get_number (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ server_client_assume_paste (struct session*) ; 
 char server_client_check_mouse (struct client*) ; 
 int /*<<< orphan*/  server_client_clear_identify (struct client*,struct window_pane*) ; 
 scalar_t__ server_client_is_default_key_table (struct client*,struct key_table*) ; 
 int /*<<< orphan*/  server_client_set_key_table (struct client*,char*) ; 
 int /*<<< orphan*/  server_status_client (struct client*) ; 
 int /*<<< orphan*/  session_update_activity (struct session*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  status_message_clear (struct client*) ; 
 scalar_t__ status_prompt_key (struct client*,char) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct client*,struct mouse_event*) ; 
 int /*<<< orphan*/  stub2 (struct window_mode_entry*) ; 
 struct window_pane* window_pane_at_index (struct window*,char) ; 
 int /*<<< orphan*/  window_pane_key (struct window_pane*,struct client*,struct session*,struct winlink*,char,struct mouse_event*) ; 
 int /*<<< orphan*/  window_unzoom (struct window*) ; 

void
server_client_handle_key(struct client *c, key_code key)
{
	struct mouse_event		*m = &c->tty.mouse;
	struct session			*s = c->session;
	struct winlink			*wl;
	struct window			*w;
	struct window_pane		*wp;
	struct window_mode_entry	*wme;
	struct timeval			 tv;
	struct key_table		*table, *first;
	struct key_binding		*bd;
	int				 xtimeout, flags;
	struct cmd_find_state		 fs;
	key_code			 key0;

	/* Check the client is good to accept input. */
	if (s == NULL || (c->flags & (CLIENT_DEAD|CLIENT_SUSPENDED)) != 0)
		return;
	wl = s->curw;
	w = wl->window;

	/* Update the activity timer. */
	if (gettimeofday(&c->activity_time, NULL) != 0)
		fatal("gettimeofday failed");
	session_update_activity(s, &c->activity_time);

	/* Number keys jump to pane in identify mode. */
	if (c->flags & CLIENT_IDENTIFY && key >= '0' && key <= '9') {
		if (c->flags & CLIENT_READONLY)
			return;
		window_unzoom(w);
		wp = window_pane_at_index(w, key - '0');
		server_client_clear_identify(c, wp);
		return;
	}

	/* Handle status line. */
	if (!(c->flags & CLIENT_READONLY)) {
		status_message_clear(c);
		server_client_clear_identify(c, NULL);
	}
	if (c->prompt_string != NULL) {
		if (c->flags & CLIENT_READONLY)
			return;
		if (status_prompt_key(c, key) == 0)
			return;
	}

	/* Check for mouse keys. */
	m->valid = 0;
	if (key == KEYC_MOUSE) {
		if (c->flags & CLIENT_READONLY)
			return;
		key = server_client_check_mouse(c);
		if (key == KEYC_UNKNOWN)
			return;

		m->valid = 1;
		m->key = key;

		/*
		 * Mouse drag is in progress, so fire the callback (now that
		 * the mouse event is valid).
		 */
		if (key == KEYC_DRAGGING) {
			c->tty.mouse_drag_update(c, m);
			return;
		}
	} else
		m->valid = 0;

	/* Find affected pane. */
	if (!KEYC_IS_MOUSE(key) || cmd_find_from_mouse(&fs, m, 0) != 0)
		cmd_find_from_session(&fs, s, 0);
	wp = fs.wp;

	/* Forward mouse keys if disabled. */
	if (KEYC_IS_MOUSE(key) && !options_get_number(s->options, "mouse"))
		goto forward_key;

	/* Treat everything as a regular key when pasting is detected. */
	if (!KEYC_IS_MOUSE(key) && server_client_assume_paste(s))
		goto forward_key;

	/*
	 * Work out the current key table. If the pane is in a mode, use
	 * the mode table instead of the default key table.
	 */
	if (server_client_is_default_key_table(c, c->keytable) &&
	    wp != NULL &&
	    (wme = TAILQ_FIRST(&wp->modes)) != NULL &&
	    wme->mode->key_table != NULL)
		table = key_bindings_get_table(wme->mode->key_table(wme), 1);
	else
		table = c->keytable;
	first = table;

table_changed:
	/*
	 * The prefix always takes precedence and forces a switch to the prefix
	 * table, unless we are already there.
	 */
	key0 = (key & ~KEYC_XTERM);
	if ((key0 == (key_code)options_get_number(s->options, "prefix") ||
	    key0 == (key_code)options_get_number(s->options, "prefix2")) &&
	    strcmp(table->name, "prefix") != 0) {
		server_client_set_key_table(c, "prefix");
		server_status_client(c);
		return;
	}
	flags = c->flags;

try_again:
	/* Log key table. */
	if (wp == NULL)
		log_debug("key table %s (no pane)", table->name);
	else
		log_debug("key table %s (pane %%%u)", table->name, wp->id);
	if (c->flags & CLIENT_REPEAT)
		log_debug("currently repeating");

	/* Try to see if there is a key binding in the current table. */
	bd = key_bindings_get(table, key0);
	if (bd != NULL) {
		/*
		 * Key was matched in this table. If currently repeating but a
		 * non-repeating binding was found, stop repeating and try
		 * again in the root table.
		 */
		if ((c->flags & CLIENT_REPEAT) &&
		    (~bd->flags & KEY_BINDING_REPEAT)) {
			log_debug("found in key table %s (not repeating)",
			    table->name);
			server_client_set_key_table(c, NULL);
			first = table = c->keytable;
			c->flags &= ~CLIENT_REPEAT;
			server_status_client(c);
			goto table_changed;
		}
		log_debug("found in key table %s", table->name);

		/*
		 * Take a reference to this table to make sure the key binding
		 * doesn't disappear.
		 */
		table->references++;

		/*
		 * If this is a repeating key, start the timer. Otherwise reset
		 * the client back to the root table.
		 */
		xtimeout = options_get_number(s->options, "repeat-time");
		if (xtimeout != 0 && (bd->flags & KEY_BINDING_REPEAT)) {
			c->flags |= CLIENT_REPEAT;

			tv.tv_sec = xtimeout / 1000;
			tv.tv_usec = (xtimeout % 1000) * 1000L;
			evtimer_del(&c->repeat_timer);
			evtimer_add(&c->repeat_timer, &tv);
		} else {
			c->flags &= ~CLIENT_REPEAT;
			server_client_set_key_table(c, NULL);
		}
		server_status_client(c);

		/* Execute the key binding. */
		key_bindings_dispatch(bd, NULL, c, m, &fs);
		key_bindings_unref_table(table);
		return;
	}

	/*
	 * No match, try the ANY key.
	 */
	if (key0 != KEYC_ANY) {
		key0 = KEYC_ANY;
		goto try_again;
	}

	/*
	 * No match in this table. If not in the root table or if repeating,
	 * switch the client back to the root table and try again.
	 */
	log_debug("not found in key table %s", table->name);
	if (!server_client_is_default_key_table(c, table) ||
	    (c->flags & CLIENT_REPEAT)) {
		log_debug("trying in root table");
		server_client_set_key_table(c, NULL);
		table = c->keytable;
		if (c->flags & CLIENT_REPEAT)
			first = table;
		c->flags &= ~CLIENT_REPEAT;
		server_status_client(c);
		goto table_changed;
	}

	/*
	 * No match in the root table either. If this wasn't the first table
	 * tried, don't pass the key to the pane.
	 */
	if (first != table && (~flags & CLIENT_REPEAT)) {
		server_client_set_key_table(c, NULL);
		server_status_client(c);
		return;
	}

forward_key:
	if (c->flags & CLIENT_READONLY)
		return;
	if (wp != NULL)
		window_pane_key(wp, c, s, wl, key, m);
}