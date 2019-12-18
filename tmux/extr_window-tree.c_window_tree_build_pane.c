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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  u_int ;
struct winlink {int /*<<< orphan*/  idx; } ;
struct window_tree_modedata {int /*<<< orphan*/  data; int /*<<< orphan*/  format; } ;
struct window_tree_itemdata {int /*<<< orphan*/  pane; int /*<<< orphan*/  winlink; int /*<<< orphan*/  session; int /*<<< orphan*/  type; } ;
struct window_pane {int /*<<< orphan*/  id; } ;
struct session {int /*<<< orphan*/  id; } ;
struct mode_tree_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WINDOW_TREE_PANE ; 
 char* format_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct session*,struct winlink*,struct window_pane*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  mode_tree_add (int /*<<< orphan*/ ,struct mode_tree_item*,struct window_tree_itemdata*,int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  window_pane_index (struct window_pane*,int /*<<< orphan*/ *) ; 
 struct window_tree_itemdata* window_tree_add_item (struct window_tree_modedata*) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
window_tree_build_pane(struct session *s, struct winlink *wl,
    struct window_pane *wp, void *modedata, struct mode_tree_item *parent)
{
	struct window_tree_modedata	*data = modedata;
	struct window_tree_itemdata	*item;
	char				*name, *text;
	u_int				 idx;

	window_pane_index(wp, &idx);

	item = window_tree_add_item(data);
	item->type = WINDOW_TREE_PANE;
	item->session = s->id;
	item->winlink = wl->idx;
	item->pane = wp->id;

	text = format_single(NULL, data->format, NULL, s, wl, wp);
	xasprintf(&name, "%u", idx);

	mode_tree_add(data->data, parent, item, (uint64_t)wp, name, text, -1);
	free(text);
	free(name);
}