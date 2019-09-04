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
struct winlink {int dummy; } ;
struct window_pane {int dummy; } ;
struct session {int dummy; } ;
struct format_tree {int dummy; } ;
struct cmdq_item {int /*<<< orphan*/ * client; } ;
struct client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FORMAT_NONE ; 
 struct format_tree* format_create (int /*<<< orphan*/ *,struct cmdq_item*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_defaults (struct format_tree*,struct client*,struct session*,struct winlink*,struct window_pane*) ; 
 char* format_expand (struct format_tree*,char const*) ; 
 int /*<<< orphan*/  format_free (struct format_tree*) ; 

char *
format_single(struct cmdq_item *item, const char *fmt, struct client *c,
    struct session *s, struct winlink *wl, struct window_pane *wp)
{
	struct format_tree	*ft;
	char			*expanded;

	if (item != NULL)
		ft = format_create(item->client, item, FORMAT_NONE, 0);
	else
		ft = format_create(NULL, item, FORMAT_NONE, 0);
	format_defaults(ft, c, s, wl, wp);

	expanded = format_expand(ft, fmt);
	format_free(ft);
	return (expanded);
}