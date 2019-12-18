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
struct session_group {int name; } ;
struct session {int name; int id; int attached; int /*<<< orphan*/  activity_time; int /*<<< orphan*/  last_attached_time; int /*<<< orphan*/  creation_time; int /*<<< orphan*/  windows; } ;
struct format_tree {struct session* s; } ;

/* Variables and functions */
 int /*<<< orphan*/  format_add (struct format_tree*,char*,char*,int) ; 
 int /*<<< orphan*/  format_add_cb (struct format_tree*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_add_tv (struct format_tree*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  format_cb_session_alerts ; 
 int /*<<< orphan*/  format_cb_session_group_list ; 
 int /*<<< orphan*/  format_cb_session_stack ; 
 struct session_group* session_group_contains (struct session*) ; 
 int session_group_count (struct session_group*) ; 
 int winlink_count (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
format_defaults_session(struct format_tree *ft, struct session *s)
{
	struct session_group	*sg;

	ft->s = s;

	format_add(ft, "session_name", "%s", s->name);
	format_add(ft, "session_windows", "%u", winlink_count(&s->windows));
	format_add(ft, "session_id", "$%u", s->id);

	sg = session_group_contains(s);
	format_add(ft, "session_grouped", "%d", sg != NULL);
	if (sg != NULL) {
		format_add(ft, "session_group", "%s", sg->name);
		format_add(ft, "session_group_size", "%u",
		    session_group_count (sg));
		format_add_cb(ft, "session_group_list",
		    format_cb_session_group_list);
	}

	format_add_tv(ft, "session_created", &s->creation_time);
	format_add_tv(ft, "session_last_attached", &s->last_attached_time);
	format_add_tv(ft, "session_activity", &s->activity_time);

	format_add(ft, "session_attached", "%u", s->attached);
	format_add(ft, "session_many_attached", "%d", s->attached > 1);

	format_add_cb(ft, "session_alerts", format_cb_session_alerts);
	format_add_cb(ft, "session_stack", format_cb_session_stack);
}