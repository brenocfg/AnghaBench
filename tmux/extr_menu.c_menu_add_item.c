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
struct menu_item {char* name; char* command; int /*<<< orphan*/  key; } ;
struct menu {scalar_t__ count; scalar_t__ width; struct menu_item* items; } ;
struct cmdq_item {int dummy; } ;
struct cmd_find_state {int /*<<< orphan*/ * wp; int /*<<< orphan*/ * wl; int /*<<< orphan*/ * s; } ;
struct client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEYC_NONE ; 
 int /*<<< orphan*/  KEYC_UNKNOWN ; 
 char* format_single (struct cmdq_item*,char const*,struct client*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ format_width (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* key_string_lookup_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct menu_item*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,char*,...) ; 
 struct menu_item* xreallocarray (struct menu_item*,scalar_t__,int) ; 

void
menu_add_item(struct menu *menu, const struct menu_item *item,
    struct cmdq_item *qitem, struct client *c, struct cmd_find_state *fs)
{
	struct menu_item	*new_item;
	const char		*key, *cmd;
	char			*s, *name;
	u_int			 width;
	int			 line;

	line = (item == NULL || item->name == NULL || *item->name == '\0');
	if (line && menu->count == 0)
		return;

	menu->items = xreallocarray(menu->items, menu->count + 1,
	    sizeof *menu->items);
	new_item = &menu->items[menu->count++];
	memset(new_item, 0, sizeof *new_item);

	if (line)
		return;

	if (fs != NULL)
		s = format_single(qitem, item->name, c, fs->s, fs->wl, fs->wp);
	else
		s = format_single(qitem, item->name, c, NULL, NULL, NULL);
	if (*s == '\0') { /* no item if empty after format expanded */
		menu->count--;
		return;
	}
	if (*s != '-' && item->key != KEYC_UNKNOWN && item->key != KEYC_NONE) {
		key = key_string_lookup_key(item->key);
		xasprintf(&name, "%s#[default] #[align=right](%s)", s, key);
	} else
		xasprintf(&name, "%s", s);
	new_item->name = name;
	free(s);

	cmd = item->command;
	if (cmd != NULL) {
		if (fs != NULL)
			s = format_single(qitem, cmd, c, fs->s, fs->wl, fs->wp);
		else
			s = format_single(qitem, cmd, c, NULL, NULL, NULL);
	} else
		s = NULL;
	new_item->command = s;
	new_item->key = item->key;

	width = format_width(new_item->name);
	if (width > menu->width)
		menu->width = width;
}