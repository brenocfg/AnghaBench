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
struct TYPE_2__ {int /*<<< orphan*/  current; } ;
struct view {int /*<<< orphan*/  watch; TYPE_1__ sort; int /*<<< orphan*/  lines; } ;
struct ref {int /*<<< orphan*/  name; } ;
typedef  enum status_code { ____Placeholder_status_code } status_code ;
typedef  enum open_flags { ____Placeholder_open_flags } open_flags ;

/* Variables and functions */
 int ERROR_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  OPEN_RELOAD ; 
 int /*<<< orphan*/  REFS_ALL_NAME ; 
 int SUCCESS ; 
 int /*<<< orphan*/  VIEW_COLUMN_REF ; 
 int WATCH_HEAD ; 
 int WATCH_REFS ; 
 int begin_update (struct view*,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ ) ; 
 struct ref* calloc (int,scalar_t__) ; 
 char* encoding_arg ; 
 int /*<<< orphan*/  foreach_ref (int /*<<< orphan*/  (*) (struct view*,struct ref*),struct view*) ; 
 int /*<<< orphan*/  get_view_column (struct view*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opt_mailmap ; 
 struct ref* refs_all ; 
 int /*<<< orphan*/  refs_open_visitor (struct view*,struct ref*) ; 
 int /*<<< orphan*/  resort_view (struct view*,int) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  watch_register (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static enum status_code
refs_open(struct view *view, enum open_flags flags)
{
	const char *refs_log[] = {
		"git", "log", encoding_arg, "--no-color", "--date=raw",
			opt_mailmap ? "--pretty=format:%H%x00%aN <%aE> %ad%x00%s"
				    : "--pretty=format:%H%x00%an <%ae> %ad%x00%s",
			"--all", "--simplify-by-decoration", NULL
	};
	enum status_code code;

	if (!refs_all) {
		struct ref *ref = calloc(1, sizeof(*refs_all) + strlen(REFS_ALL_NAME));

		if (!ref)
			return ERROR_OUT_OF_MEMORY;

		strncpy(ref->name, REFS_ALL_NAME, strlen(REFS_ALL_NAME));
		refs_all = ref;
	}

	code = begin_update(view, NULL, refs_log, OPEN_RELOAD);
	if (code != SUCCESS)
		return code;

	if (!view->lines)
		view->sort.current = get_view_column(view, VIEW_COLUMN_REF);
	refs_open_visitor(view, refs_all);
	foreach_ref(refs_open_visitor, view);
	resort_view(view, true);

	watch_register(&view->watch, WATCH_HEAD | WATCH_REFS);

	return SUCCESS;
}