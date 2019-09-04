#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct winlink {int dummy; } ;
struct window_pane {TYPE_1__* window; int /*<<< orphan*/  modes; } ;
struct window_mode_entry {TYPE_2__* mode; } ;
struct session {int dummy; } ;
struct key_table {int /*<<< orphan*/  references; } ;
struct key_binding {int dummy; } ;
struct TYPE_6__ {struct winlink* wl; struct session* s; struct window_pane* wp; } ;
struct cmdq_item {TYPE_3__ target; } ;
struct client {int dummy; } ;
typedef  int key_code ;
struct TYPE_5__ {int /*<<< orphan*/  (* key_table ) (struct window_mode_entry*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  options; } ;

/* Variables and functions */
 int KEYC_XTERM ; 
 struct window_mode_entry* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_bindings_dispatch (struct key_binding*,struct cmdq_item*,struct client*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 struct key_binding* key_bindings_get (struct key_table*,int) ; 
 struct key_table* key_bindings_get_table (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  key_bindings_unref_table (struct key_table*) ; 
 scalar_t__ options_get_number (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct window_mode_entry*) ; 
 int /*<<< orphan*/  window_pane_key (struct window_pane*,int /*<<< orphan*/ *,struct session*,struct winlink*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cmd_send_keys_inject(struct client *c, struct cmdq_item *item, key_code key)
{
	struct window_pane		*wp = item->target.wp;
	struct session			*s = item->target.s;
	struct winlink			*wl = item->target.wl;
	struct window_mode_entry	*wme;
	struct key_table		*table;
	struct key_binding		*bd;

	wme = TAILQ_FIRST(&wp->modes);
	if (wme == NULL || wme->mode->key_table == NULL) {
		if (options_get_number(wp->window->options, "xterm-keys"))
			key |= KEYC_XTERM;
		window_pane_key(wp, NULL, s, wl, key, NULL);
		return;
	}
	table = key_bindings_get_table(wme->mode->key_table(wme), 1);

	bd = key_bindings_get(table, key & ~KEYC_XTERM);
	if (bd != NULL) {
		table->references++;
		key_bindings_dispatch(bd, item, c, NULL, &item->target);
		key_bindings_unref_table(table);
	}
}