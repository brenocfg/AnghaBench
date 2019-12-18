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
struct view {char const** argv; TYPE_2__* ops; int /*<<< orphan*/  ref; TYPE_1__* env; int /*<<< orphan*/  encoding; struct blob_state* private; } ;
struct blob_state {int /*<<< orphan*/  file; scalar_t__* commit; } ;
typedef  enum status_code { ____Placeholder_status_code } status_code ;
typedef  enum open_flags { ____Placeholder_open_flags } open_flags ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_3__ {char* commit; scalar_t__* file; int /*<<< orphan*/ * blob; } ;

/* Variables and functions */
 int OPEN_PREPARED ; 
 int OPEN_REFRESH ; 
 int /*<<< orphan*/  REQ_VIEW_TREE ; 
 int SIZEOF_STR ; 
 int begin_update (struct view*,int /*<<< orphan*/ *,char const**,int) ; 
 int /*<<< orphan*/  default_encoding ; 
 int error (char*,...) ; 
 int /*<<< orphan*/  get_path (scalar_t__*) ; 
 int /*<<< orphan*/  get_path_encoding (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_view_key (struct view*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_run_buf (char const**,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  string_copy (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  string_copy_rev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_format (char*,char*,char const*,scalar_t__*) ; 
 int /*<<< orphan*/  string_ncopy (scalar_t__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_rev_is_null (char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static enum status_code
blob_open(struct view *view, enum open_flags flags)
{
	struct blob_state *state = view->private;
	static const char *blob_argv[] = {
		"git", "cat-file", "blob", "%(blob)", NULL
	};
	const char **argv = (flags & (OPEN_PREPARED | OPEN_REFRESH)) ? view->argv : blob_argv;

	if (argv != blob_argv) {
		state->file = get_path(view->env->file);
		state->commit[0] = 0;
	}

	if (!state->file && !view->env->blob[0] && view->env->file[0]) {
		const char *commit = view->env->commit[0] && !string_rev_is_null(view->env->commit)
				   ? view->env->commit : "HEAD";
		char blob_spec[SIZEOF_STR];
		const char *rev_parse_argv[] = {
			"git", "rev-parse", blob_spec, NULL
		};

		if (!string_format(blob_spec, "%s:%s", commit, view->env->file) ||
		    !io_run_buf(rev_parse_argv, view->env->blob, sizeof(view->env->blob), NULL, false))
			return error("Failed to resolve blob from file name");

		string_ncopy(state->commit, commit, strlen(commit));
	}

	if (!state->file && !view->env->blob[0])
		return error("No file chosen, press %s to open tree view",
			     get_view_key(view, REQ_VIEW_TREE));

	view->encoding = get_path_encoding(view->env->file, default_encoding);

	if (*view->env->file)
		string_copy(view->ref, view->env->file);
	else
		string_copy_rev(view->ref, view->ops->id);

	return begin_update(view, NULL, argv, flags);
}