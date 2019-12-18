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
typedef  int /*<<< orphan*/  u_char ;
struct window_pane_input_data {int /*<<< orphan*/  item; int /*<<< orphan*/  wp; } ;
struct window_pane {int dummy; } ;
struct evbuffer {int dummy; } ;
struct client {int flags; int /*<<< orphan*/ * stdin_callback; struct evbuffer* stdin_data; } ;

/* Variables and functions */
 int CLIENT_DEAD ; 
 int CLIENT_EXIT ; 
 int /*<<< orphan*/ * EVBUFFER_DATA (struct evbuffer*) ; 
 size_t EVBUFFER_LENGTH (struct evbuffer*) ; 
 int /*<<< orphan*/  cmdq_continue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evbuffer_drain (struct evbuffer*,size_t) ; 
 int /*<<< orphan*/  free (struct window_pane_input_data*) ; 
 int /*<<< orphan*/  input_parse_buffer (struct window_pane*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  server_client_unref (struct client*) ; 
 struct window_pane* window_pane_find_by_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
window_pane_input_callback(struct client *c, int closed, void *data)
{
	struct window_pane_input_data	*cdata = data;
	struct window_pane		*wp;
	struct evbuffer			*evb = c->stdin_data;
	u_char				*buf = EVBUFFER_DATA(evb);
	size_t				 len = EVBUFFER_LENGTH(evb);

	wp = window_pane_find_by_id(cdata->wp);
	if (wp == NULL || closed || c->flags & CLIENT_DEAD) {
		if (wp == NULL)
			c->flags |= CLIENT_EXIT;
		evbuffer_drain(evb, len);

		c->stdin_callback = NULL;
		server_client_unref(c);

		cmdq_continue(cdata->item);
		free(cdata);

		return;
	}

	input_parse_buffer(wp, buf, len);
	evbuffer_drain(evb, len);
}