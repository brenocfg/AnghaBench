#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct view {scalar_t__ parent; TYPE_2__* env; int /*<<< orphan*/  line; } ;
struct line {int /*<<< orphan*/  type; } ;
typedef  enum request { ____Placeholder_request } request ;
struct TYPE_5__ {int /*<<< orphan*/ * name; } ;
struct TYPE_7__ {char status; TYPE_1__ new; } ;
struct TYPE_6__ {int /*<<< orphan*/  goto_lineno; int /*<<< orphan*/ * ref; int /*<<< orphan*/  file; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINE_DIFF_ADD ; 
 int /*<<< orphan*/  LINE_DIFF_CHUNK ; 
 int /*<<< orphan*/  LINE_DIFF_DEL ; 
 scalar_t__ LINE_STAT_UNTRACKED ; 
#define  REQ_EDIT 135 
#define  REQ_ENTER 134 
 int REQ_NONE ; 
#define  REQ_REFRESH 133 
#define  REQ_STAGE_SPLIT_CHUNK 132 
#define  REQ_STAGE_UPDATE_LINE 131 
#define  REQ_STATUS_REVERT 130 
#define  REQ_STATUS_UPDATE 129 
#define  REQ_VIEW_BLAME 128 
 int REQ_VIEW_CLOSE ; 
 int diff_common_edit (struct view*,int,struct line*) ; 
 int diff_common_enter (struct view*,int,struct line*) ; 
 int /*<<< orphan*/  diff_get_lineno (struct view*,struct line*) ; 
 char* diff_get_pathname (struct view*,struct line*) ; 
 struct line* find_prev_line_by_type (struct view*,struct line*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_refs (int) ; 
 int /*<<< orphan*/  open_editor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refresh_view (struct view*) ; 
 int /*<<< orphan*/  report (char*) ; 
 int /*<<< orphan*/  stage_chunk_is_wrapped (struct view*,struct line*) ; 
 int /*<<< orphan*/  stage_exists (struct view*,TYPE_3__*,scalar_t__) ; 
 scalar_t__ stage_line_type ; 
 int /*<<< orphan*/  stage_revert (struct view*,struct line*) ; 
 int /*<<< orphan*/  stage_split_chunk (struct view*,struct line*) ; 
 TYPE_3__ stage_status ; 
 int /*<<< orphan*/  stage_update (struct view*,struct line*,int) ; 
 int /*<<< orphan*/  string_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_ncopy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static enum request
stage_request(struct view *view, enum request request, struct line *line)
{
	switch (request) {
	case REQ_STATUS_UPDATE:
		if (!stage_update(view, line, false))
			return REQ_NONE;
		break;

	case REQ_STATUS_REVERT:
		if (!stage_revert(view, line))
			return REQ_NONE;
		break;

	case REQ_STAGE_UPDATE_LINE:
		if (stage_line_type == LINE_STAT_UNTRACKED ||
		    stage_status.status == 'A') {
			report("Staging single lines is not supported for new files");
			return REQ_NONE;
		}
		if (line->type != LINE_DIFF_DEL && line->type != LINE_DIFF_ADD) {
			report("Please select a change to stage");
			return REQ_NONE;
		}
		if (stage_chunk_is_wrapped(view, line)) {
			report("Staging is not supported for wrapped lines");
			return REQ_NONE;
		}
		if (!stage_update(view, line, true))
			return REQ_NONE;
		break;


	case REQ_STAGE_SPLIT_CHUNK:
		if (stage_line_type == LINE_STAT_UNTRACKED ||
		    !(line = find_prev_line_by_type(view, line, LINE_DIFF_CHUNK))) {
			report("No chunks to split in sight");
			return REQ_NONE;
		}
		stage_split_chunk(view, line);
		return REQ_NONE;

	case REQ_EDIT:
		if (!stage_status.new.name[0])
			return diff_common_edit(view, request, line);

		if (stage_status.status == 'D') {
			report("File has been deleted.");
			return REQ_NONE;
		}

		if (stage_line_type == LINE_STAT_UNTRACKED) {
			open_editor(stage_status.new.name, (line - view->line) + 1);
		} else {
			open_editor(stage_status.new.name, diff_get_lineno(view, line));
		}
		break;

	case REQ_REFRESH:
		/* Reload everything(including current branch information) ... */
		load_refs(true);
		break;

	case REQ_VIEW_BLAME:
		if (stage_line_type == LINE_STAT_UNTRACKED) {
			report("Nothing to blame here");
			return REQ_NONE;
		}

		if (stage_status.new.name[0]) {
			string_copy(view->env->file, stage_status.new.name);
		} else {
			const char *file = diff_get_pathname(view, line);

			if (file)
				string_ncopy(view->env->file, file, strlen(file));
		}

		view->env->ref[0] = 0;
		view->env->goto_lineno = diff_get_lineno(view, line);
		if (view->env->goto_lineno > 0)
			view->env->goto_lineno--;
		return request;

	case REQ_ENTER:
		return diff_common_enter(view, request, line);

	default:
		return request;
	}

	/* Check whether the staged entry still exists, and close the
	 * stage view if it doesn't. */
	if (view->parent && !stage_exists(view, &stage_status, stage_line_type)) {
		stage_line_type = 0;
		return REQ_VIEW_CLOSE;
	}

	refresh_view(view);

	return REQ_NONE;
}