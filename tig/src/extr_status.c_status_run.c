#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct view {int lines; int /*<<< orphan*/  watch; TYPE_3__* line; } ;
struct TYPE_6__ {int /*<<< orphan*/ * name; } ;
struct TYPE_5__ {int /*<<< orphan*/ * name; int /*<<< orphan*/ * rev; } ;
struct status {char status; TYPE_2__ new; TYPE_1__ old; int /*<<< orphan*/  member_0; } ;
struct line {int dummy; } ;
struct io {int dummy; } ;
struct buffer {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
typedef  enum line_type { ____Placeholder_line_type } line_type ;
struct TYPE_8__ {int /*<<< orphan*/  exec_dir; } ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IO_RD ; 
 int LINE_STAT_NONE ; 
 int LINE_STAT_STAGED ; 
 int LINE_STAT_UNSTAGED ; 
 int LINE_STAT_UNTRACKED ; 
 int /*<<< orphan*/ * NULL_ID ; 
 int /*<<< orphan*/  WATCH_INDEX_STAGED_NO ; 
 int /*<<< orphan*/  WATCH_INDEX_STAGED_YES ; 
 int /*<<< orphan*/  WATCH_INDEX_UNSTAGED_NO ; 
 int /*<<< orphan*/  WATCH_INDEX_UNSTAGED_YES ; 
 int /*<<< orphan*/  WATCH_INDEX_UNTRACKED_NO ; 
 int /*<<< orphan*/  WATCH_INDEX_UNTRACKED_YES ; 
 struct line* add_line_alloc (struct view*,struct status**,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  add_line_nodata (struct view*,int) ; 
 int /*<<< orphan*/  io_done (struct io*) ; 
 scalar_t__ io_error (struct io*) ; 
 scalar_t__ io_get (struct io*,struct buffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  io_run (struct io*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const**) ; 
 TYPE_4__ repo ; 
 int /*<<< orphan*/  status_get_diff (struct status*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_ncopy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  view_column_info_update (struct view*,struct line*) ; 
 int /*<<< orphan*/  watch_apply (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
status_run(struct view *view, const char *argv[], char status, enum line_type type)
{
	struct status *unmerged = NULL;
	struct buffer buf;
	struct io io;

	if (!io_run(&io, IO_RD, repo.exec_dir, NULL, argv))
		return false;

	add_line_nodata(view, type);

	while (io_get(&io, &buf, 0, true)) {
		struct line *line;
		struct status parsed = {0};
		struct status *file = &parsed;

		/* Parse diff info part. */
		if (status) {
			file->status = status;
			if (status == 'A')
				string_copy(file->old.rev, NULL_ID);

		} else {
			if (!status_get_diff(&parsed, buf.data, buf.size))
				goto error_out;

			if (!io_get(&io, &buf, 0, true))
				break;
		}

		/* Grab the old name for rename/copy. */
		if (!*file->old.name &&
		    (file->status == 'R' || file->status == 'C')) {
			string_ncopy(file->old.name, buf.data, buf.size);

			if (!io_get(&io, &buf, 0, true))
				break;
		}

		/* git-ls-files just delivers a NUL separated list of
		 * file names similar to the second half of the
		 * git-diff-* output. */
		string_ncopy(file->new.name, buf.data, buf.size);
		if (!*file->old.name)
			string_copy(file->old.name, file->new.name);

		/* Collapse all modified entries that follow an associated
		 * unmerged entry. */
		if (unmerged && !strcmp(unmerged->new.name, file->new.name)) {
			unmerged->status = 'U';
			unmerged = NULL;
			continue;
		}

		line = add_line_alloc(view, &file, type, 0, false);
		if (!line)
			goto error_out;
		*file = parsed;
		view_column_info_update(view, line);
		if (file->status == 'U')
			unmerged = file;
	}

	if (io_error(&io)) {
error_out:
		io_done(&io);
		return false;
	}

	if (!view->line[view->lines - 1].data) {
		add_line_nodata(view, LINE_STAT_NONE);
		if (type == LINE_STAT_STAGED)
			watch_apply(&view->watch, WATCH_INDEX_STAGED_NO);
		else if (type == LINE_STAT_UNSTAGED)
			watch_apply(&view->watch, WATCH_INDEX_UNSTAGED_NO);
		else if (type == LINE_STAT_UNTRACKED)
			watch_apply(&view->watch, WATCH_INDEX_UNTRACKED_NO);
	} else {
		if (type == LINE_STAT_STAGED)
			watch_apply(&view->watch, WATCH_INDEX_STAGED_YES);
		else if (type == LINE_STAT_UNSTAGED)
			watch_apply(&view->watch, WATCH_INDEX_UNSTAGED_YES);
		else if (type == LINE_STAT_UNTRACKED)
			watch_apply(&view->watch, WATCH_INDEX_UNTRACKED_YES);
	}

	io_done(&io);
	return true;
}