#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct view {int /*<<< orphan*/ * parent; TYPE_2__* env; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct status {unsigned char status; TYPE_1__ new; } ;
struct line {int /*<<< orphan*/  type; struct status* data; } ;
typedef  enum request { ____Placeholder_request } request ;
struct TYPE_4__ {int /*<<< orphan*/ * ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINE_STAT_UNTRACKED ; 
#define  REQ_EDIT 134 
#define  REQ_ENTER 133 
 int REQ_NONE ; 
#define  REQ_REFRESH 132 
#define  REQ_STATUS_MERGE 131 
#define  REQ_STATUS_REVERT 130 
#define  REQ_STATUS_UPDATE 129 
#define  REQ_VIEW_BLAME 128 
 int REQ_VIEW_CLOSE ; 
 int /*<<< orphan*/  load_repo_head () ; 
 int /*<<< orphan*/  main_status_exists (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  main_view ; 
 int /*<<< orphan*/  open_editor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_mergetool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refresh_view (struct view*) ; 
 int /*<<< orphan*/  report (char*) ; 
 scalar_t__ show_untracked_only ; 
 int status_enter (struct view*,struct line*) ; 
 int /*<<< orphan*/  status_has_none (struct view*,struct line*) ; 
 int /*<<< orphan*/  status_revert (struct status*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  status_update (struct view*) ; 

__attribute__((used)) static enum request
status_request(struct view *view, enum request request, struct line *line)
{
	struct status *status = line->data;

	switch (request) {
	case REQ_STATUS_UPDATE:
		if (!status_update(view))
			return REQ_NONE;
		break;

	case REQ_STATUS_REVERT:
		if (!status_revert(status, line->type, status_has_none(view, line)))
			return REQ_NONE;
		break;

	case REQ_STATUS_MERGE:
		if (!status || status->status != 'U') {
			report("Merging only possible for files with unmerged status ('U').");
			return REQ_NONE;
		}
		open_mergetool(status->new.name);
		break;

	case REQ_EDIT:
		if (!status)
			return request;
		if (status->status == 'D') {
			report("File has been deleted.");
			return REQ_NONE;
		}

		open_editor(status->new.name, 0);
		break;

	case REQ_VIEW_BLAME:
		if (line->type == LINE_STAT_UNTRACKED || !status) {
			report("Nothing to blame here");
			return REQ_NONE;
		}
		if (status)
			view->env->ref[0] = 0;
		return request;

	case REQ_ENTER:
		/* After returning the status view has been split to
		 * show the stage view. No further reloading is
		 * necessary. */
		return status_enter(view, line);

	case REQ_REFRESH:
		/* Load the current branch information and then the view. */
		load_repo_head();
		break;

	default:
		return request;
	}

	if (show_untracked_only && view->parent == &main_view && !main_status_exists(view->parent, LINE_STAT_UNTRACKED))
		return REQ_VIEW_CLOSE;

	refresh_view(view);

	return REQ_NONE;
}