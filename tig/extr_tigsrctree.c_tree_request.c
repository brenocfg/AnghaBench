#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct view {int /*<<< orphan*/  pos; TYPE_1__* env; int /*<<< orphan*/  vid; } ;
struct tree_entry {int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;
struct line {int type; struct tree_entry* data; } ;
typedef  enum request { ____Placeholder_request } request ;
typedef  enum open_flags { ____Placeholder_open_flags } open_flags ;
struct TYPE_2__ {scalar_t__* directory; int /*<<< orphan*/  file; int /*<<< orphan*/  ref; } ;

/* Variables and functions */
#define  LINE_DIRECTORY 134 
#define  LINE_FILE 133 
 int OPEN_DEFAULT ; 
 int OPEN_SPLIT ; 
#define  REQ_BACK 132 
#define  REQ_EDIT 131 
#define  REQ_ENTER 130 
 int REQ_NONE ; 
#define  REQ_PARENT 129 
#define  REQ_VIEW_BLAME 128 
 int REQ_VIEW_CLOSE ; 
 int /*<<< orphan*/  is_head_commit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_blob_editor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_blob_view (struct view*,int) ; 
 int /*<<< orphan*/  open_editor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pop_tree_stack_entry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  push_tree_stack_entry (struct view*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reload_view (struct view*) ; 
 int /*<<< orphan*/  report (char*) ; 
 int /*<<< orphan*/  reset_view_history (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* tree_path (struct line*) ; 
 int /*<<< orphan*/  tree_path_is_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_view_history ; 
 int /*<<< orphan*/  view_is_displayed (struct view*) ; 

__attribute__((used)) static enum request
tree_request(struct view *view, enum request request, struct line *line)
{
	enum open_flags flags;
	struct tree_entry *entry = line->data;

	switch (request) {
	case REQ_VIEW_BLAME:
		if (line->type != LINE_FILE) {
			report("Blame only supported for files");
			return REQ_NONE;
		}

		string_copy(view->env->ref, view->vid);
		return request;

	case REQ_EDIT:
		if (line->type != LINE_FILE) {
			report("Edit only supported for files");
		} else if (!is_head_commit(view->vid)) {
			open_blob_editor(entry->id, entry->name, 0);
		} else {
			open_editor(view->env->file, 0);
		}
		return REQ_NONE;

	case REQ_PARENT:
	case REQ_BACK:
		if (!*view->env->directory) {
			/* quit view if at top of tree */
			return REQ_VIEW_CLOSE;
		}
		/* fake 'cd  ..' */
		pop_tree_stack_entry(&view->pos);
		reload_view(view);
		return REQ_NONE;

	case REQ_ENTER:
		break;

	default:
		return request;
	}

	/* Cleanup the stack if the tree view is at a different tree. */
	if (!*view->env->directory)
		reset_view_history(&tree_view_history);

	switch (line->type) {
	case LINE_DIRECTORY:
		/* Depending on whether it is a subdirectory or parent link
		 * mangle the path buffer. */
		if (tree_path_is_parent(entry->name) && *view->env->directory) {
			pop_tree_stack_entry(&view->pos);

		} else {
			const char *basename = tree_path(line);

			push_tree_stack_entry(view, basename, &view->pos);
		}

		/* Trees and subtrees share the same ID, so they are not not
		 * unique like blobs. */
		reload_view(view);
		break;

	case LINE_FILE:
		flags = view_is_displayed(view) ? OPEN_SPLIT : OPEN_DEFAULT;
		open_blob_view(view, flags);
		break;

	default:
		return REQ_NONE;
	}

	return REQ_NONE;
}