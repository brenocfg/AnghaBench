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
struct window_pane_input_data {int /*<<< orphan*/  wp; struct cmdq_item* item; } ;
struct window_pane {int flags; int /*<<< orphan*/  id; } ;
struct cmdq_item {struct client* client; } ;
struct client {int dummy; } ;

/* Variables and functions */
 int PANE_EMPTY ; 
 int server_set_stdin_callback (struct client*,int /*<<< orphan*/ ,struct window_pane_input_data*,char**) ; 
 int /*<<< orphan*/  window_pane_input_callback ; 
 struct window_pane_input_data* xmalloc (int) ; 
 char* xstrdup (char*) ; 

int
window_pane_start_input(struct window_pane *wp, struct cmdq_item *item,
    char **cause)
{
	struct client			*c = item->client;
	struct window_pane_input_data	*cdata;

	if (~wp->flags & PANE_EMPTY) {
		*cause = xstrdup("pane is not empty");
		return (-1);
	}

	cdata = xmalloc(sizeof *cdata);
	cdata->item = item;
	cdata->wp = wp->id;

	return (server_set_stdin_callback(c, window_pane_input_callback, cdata,
	    cause));
}