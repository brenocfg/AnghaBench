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
struct window_mode_entry {TYPE_2__* mode; } ;
struct key_table {int /*<<< orphan*/  references; } ;
struct key_binding {int dummy; } ;
struct cmdq_item {int /*<<< orphan*/  target; int /*<<< orphan*/  client; } ;
struct cmd_find_state {int /*<<< orphan*/  wl; int /*<<< orphan*/  s; TYPE_3__* wp; } ;
struct client {int dummy; } ;
typedef  int key_code ;
struct TYPE_6__ {TYPE_1__* window; int /*<<< orphan*/  modes; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* key_table ) (struct window_mode_entry*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  options; } ;

/* Variables and functions */
 int KEYC_XTERM ; 
 struct window_mode_entry* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct cmdq_item* key_bindings_dispatch (struct key_binding*,struct cmdq_item*,struct client*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct key_binding* key_bindings_get (struct key_table*,int) ; 
 struct key_table* key_bindings_get_table (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  key_bindings_unref_table (struct key_table*) ; 
 scalar_t__ options_get_number (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct window_mode_entry*) ; 
 int /*<<< orphan*/  window_pane_key (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct cmdq_item *
cmd_send_keys_inject_key(struct client *c, struct cmd_find_state *fs,
    struct cmdq_item *item, key_code key)
{
	struct window_mode_entry	*wme;
	struct key_table		*table;
	struct key_binding		*bd;

	wme = TAILQ_FIRST(&fs->wp->modes);
	if (wme == NULL || wme->mode->key_table == NULL) {
		if (options_get_number(fs->wp->window->options, "xterm-keys"))
			key |= KEYC_XTERM;
		window_pane_key(fs->wp, item->client, fs->s, fs->wl, key, NULL);
		return (item);
	}
	table = key_bindings_get_table(wme->mode->key_table(wme), 1);

	bd = key_bindings_get(table, key & ~KEYC_XTERM);
	if (bd != NULL) {
		table->references++;
		item = key_bindings_dispatch(bd, item, c, NULL, &item->target);
		key_bindings_unref_table(table);
	}
	return (item);
}