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
struct view {char* ref; } ;
struct line {int /*<<< orphan*/  type; scalar_t__ data; } ;
struct io {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  doupdate () ; 
 int /*<<< orphan*/  get_cursor_pos (int,int) ; 
 scalar_t__ io_done (struct io*) ; 
 int /*<<< orphan*/  set_cursor_pos (int,int) ; 
 int /*<<< orphan*/  status_update_prepare (struct io*,int /*<<< orphan*/ ) ; 
 int status_update_write (struct io*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_copy (char*,char*) ; 
 int /*<<< orphan*/  string_format (char*,char*,int,int,int) ; 
 int /*<<< orphan*/  update_view_title (struct view*) ; 
 scalar_t__ view_has_line (struct view*,struct line*) ; 
 scalar_t__ view_is_displayed (struct view*) ; 

bool
status_update_files(struct view *view, struct line *line)
{
	char buf[sizeof(view->ref)];
	struct io io;
	bool result = true;
	struct line *pos;
	int files = 0;
	int file, done;
	int cursor_y = -1, cursor_x = -1;

	if (!status_update_prepare(&io, line->type))
		return false;

	for (pos = line; view_has_line(view, pos) && pos->data; pos++)
		files++;

	string_copy(buf, view->ref);
	get_cursor_pos(cursor_y, cursor_x);
	for (file = 0, done = 5; result && file < files; line++, file++) {
		int almost_done = file * 100 / files;

		if (almost_done > done && view_is_displayed(view)) {
			done = almost_done;
			string_format(view->ref, "updating file %u of %u (%d%% done)",
				      file, files, done);
			update_view_title(view);
			set_cursor_pos(cursor_y, cursor_x);
			doupdate();
		}
		result = status_update_write(&io, line->data, line->type);
	}
	string_copy(view->ref, buf);

	return io_done(&io) && result;
}