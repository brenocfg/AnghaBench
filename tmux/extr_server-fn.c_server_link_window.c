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
struct winlink {int /*<<< orphan*/  idx; int /*<<< orphan*/  window; int /*<<< orphan*/  flags; } ;
struct session_group {int dummy; } ;
struct session {int /*<<< orphan*/  options; struct winlink* curw; int /*<<< orphan*/  windows; int /*<<< orphan*/  lastw; } ;

/* Variables and functions */
 int /*<<< orphan*/  WINLINK_ALERTFLAGS ; 
 int /*<<< orphan*/  notify_session_window (char*,struct session*,int /*<<< orphan*/ ) ; 
 int options_get_number (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  server_redraw_session_group (struct session*) ; 
 struct winlink* session_attach (struct session*,int /*<<< orphan*/ ,int,char**) ; 
 struct session_group* session_group_contains (struct session*) ; 
 int /*<<< orphan*/  session_select (struct session*,int /*<<< orphan*/ ) ; 
 struct winlink* winlink_find_by_index (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  winlink_remove (int /*<<< orphan*/ *,struct winlink*) ; 
 int /*<<< orphan*/  winlink_stack_remove (int /*<<< orphan*/ *,struct winlink*) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,...) ; 

int
server_link_window(struct session *src, struct winlink *srcwl,
    struct session *dst, int dstidx, int killflag, int selectflag,
    char **cause)
{
	struct winlink		*dstwl;
	struct session_group	*srcsg, *dstsg;

	srcsg = session_group_contains(src);
	dstsg = session_group_contains(dst);
	if (src != dst && srcsg != NULL && dstsg != NULL && srcsg == dstsg) {
		xasprintf(cause, "sessions are grouped");
		return (-1);
	}

	dstwl = NULL;
	if (dstidx != -1)
		dstwl = winlink_find_by_index(&dst->windows, dstidx);
	if (dstwl != NULL) {
		if (dstwl->window == srcwl->window) {
			xasprintf(cause, "same index: %d", dstidx);
			return (-1);
		}
		if (killflag) {
			/*
			 * Can't use session_detach as it will destroy session
			 * if this makes it empty.
			 */
			notify_session_window("window-unlinked", dst,
			    dstwl->window);
			dstwl->flags &= ~WINLINK_ALERTFLAGS;
			winlink_stack_remove(&dst->lastw, dstwl);
			winlink_remove(&dst->windows, dstwl);

			/* Force select/redraw if current. */
			if (dstwl == dst->curw) {
				selectflag = 1;
				dst->curw = NULL;
			}
		}
	}

	if (dstidx == -1)
		dstidx = -1 - options_get_number(dst->options, "base-index");
	dstwl = session_attach(dst, srcwl->window, dstidx, cause);
	if (dstwl == NULL)
		return (-1);

	if (selectflag)
		session_select(dst, dstwl->idx);
	server_redraw_session_group(dst);

	return (0);
}