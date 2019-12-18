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
struct view {scalar_t__ lines; char* vid; scalar_t__ pipe; int /*<<< orphan*/ ** argv; struct diff_state* private; } ;
struct diff_state {int adding_describe_ref; } ;
struct buffer {int /*<<< orphan*/  data; } ;
typedef  enum status_code { ____Placeholder_status_code } status_code ;

/* Variables and functions */
 int /*<<< orphan*/  OPEN_EXTRA ; 
 int SUCCESS ; 
 int argv_size (int /*<<< orphan*/ **) ; 
 int begin_update (struct view*,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ ) ; 
 int diff_common_read (struct view*,int /*<<< orphan*/ ,struct diff_state*) ; 
 int /*<<< orphan*/  diff_done_highlight (struct diff_state*) ; 
 int diff_read_describe (struct view*,struct buffer*,struct diff_state*) ; 
 int /*<<< orphan*/  diff_restore_line (struct view*,struct diff_state*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  get_status_message (int) ; 
 int /*<<< orphan*/  io_done (scalar_t__) ; 
 int /*<<< orphan*/  opt_diff_highlight ; 
 int /*<<< orphan*/ ** opt_file_args ; 
 int /*<<< orphan*/  ref_list_contains_tag (char*) ; 
 int /*<<< orphan*/  report (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ view_exec (struct view*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
diff_read(struct view *view, struct buffer *buf, bool force_stop)
{
	struct diff_state *state = view->private;

	if (state->adding_describe_ref)
		return diff_read_describe(view, buf, state);

	if (!buf) {
		if (!diff_done_highlight(state)) {
			report("Failed run the diff-highlight program: %s", opt_diff_highlight);
			return false;
		}

		/* Fall back to retry if no diff will be shown. */
		if (view->lines == 0 && opt_file_args) {
			int pos = argv_size(view->argv)
				- argv_size(opt_file_args) - 1;

			if (pos > 0 && !strcmp(view->argv[pos], "--")) {
				for (; view->argv[pos]; pos++) {
					free((void *) view->argv[pos]);
					view->argv[pos] = NULL;
				}

				if (view->pipe)
					io_done(view->pipe);
				if (view_exec(view, 0))
					return false;
			}
		}

		diff_restore_line(view, state);

		if (!state->adding_describe_ref && !ref_list_contains_tag(view->vid)) {
			const char *describe_argv[] = { "git", "describe", view->vid, NULL };
			enum status_code code = begin_update(view, NULL, describe_argv, OPEN_EXTRA);

			if (code != SUCCESS) {
				report("Failed to load describe data: %s", get_status_message(code));
				return true;
			}

			state->adding_describe_ref = true;
			return false;
		}

		return true;
	}

	return diff_common_read(view, buf->data, state);
}