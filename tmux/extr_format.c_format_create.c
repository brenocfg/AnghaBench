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
struct window_mode {int /*<<< orphan*/ * default_format; int /*<<< orphan*/  name; } ;
struct format_tree {int tag; int flags; int /*<<< orphan*/  time; struct cmdq_item* item; struct client* client; int /*<<< orphan*/  tree; } ;
struct cmdq_item {int dummy; } ;
struct client {int /*<<< orphan*/  references; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * VERSION ; 
 struct window_mode** all_window_modes ; 
 int /*<<< orphan*/  event_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evtimer_set (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *),int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  format_add (struct format_tree*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  format_add_cb (struct format_tree*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_add_tv (struct format_tree*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  format_cb_host ; 
 int /*<<< orphan*/  format_cb_host_short ; 
 int /*<<< orphan*/  format_cb_pid ; 
 int /*<<< orphan*/  format_create_add_item (struct format_tree*,struct cmdq_item*) ; 
 int /*<<< orphan*/  format_job_event ; 
 int /*<<< orphan*/  format_job_timer (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * socket_path ; 
 int /*<<< orphan*/  start_time ; 
 size_t strcspn (char*,char*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 struct format_tree* xcalloc (int,int) ; 
 int /*<<< orphan*/  xsnprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

struct format_tree *
format_create(struct client *c, struct cmdq_item *item, int tag, int flags)
{
	struct format_tree		 *ft;
	const struct window_mode	**wm;
	char				  tmp[64];

	if (!event_initialized(&format_job_event)) {
		evtimer_set(&format_job_event, format_job_timer, NULL);
		format_job_timer(-1, 0, NULL);
	}

	ft = xcalloc(1, sizeof *ft);
	RB_INIT(&ft->tree);

	if (c != NULL) {
		ft->client = c;
		ft->client->references++;
	}
	ft->item = item;

	ft->tag = tag;
	ft->flags = flags;
	ft->time = time(NULL);

	format_add(ft, "version", "%s", VERSION);
	format_add_cb(ft, "host", format_cb_host);
	format_add_cb(ft, "host_short", format_cb_host_short);
	format_add_cb(ft, "pid", format_cb_pid);
	format_add(ft, "socket_path", "%s", socket_path);
	format_add_tv(ft, "start_time", &start_time);

	for (wm = all_window_modes; *wm != NULL; wm++) {
		if ((*wm)->default_format != NULL) {
			xsnprintf(tmp, sizeof tmp, "%s_format", (*wm)->name);
			tmp[strcspn(tmp, "-")] = '_';
			format_add(ft, tmp, "%s", (*wm)->default_format);
		}
	}

	if (item != NULL)
		format_create_add_item(ft, item);

	return (ft);
}