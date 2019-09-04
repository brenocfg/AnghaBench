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
struct view {int dummy; } ;
struct ref_format {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct ref {int /*<<< orphan*/  name; struct ref* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINE_PP_REFS ; 
 int SIZEOF_STR ; 
 int /*<<< orphan*/  VIEW_ADD_DESCRIBE_REF ; 
 int /*<<< orphan*/  add_line_text (struct view*,char const*,int /*<<< orphan*/ ) ; 
 struct ref_format* get_ref_format (int /*<<< orphan*/ ,struct ref const*) ; 
 struct ref* get_ref_list (char const*) ; 
 int /*<<< orphan*/  opt_reference_format ; 
 scalar_t__ refs_contain_tag () ; 
 int /*<<< orphan*/  string_format_from (char*,size_t*,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ view_has_flags (struct view*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
add_pager_refs(struct view *view, const char *commit_id)
{
	char buf[SIZEOF_STR];
	const struct ref *list;
	size_t bufpos = 0;
	const char *sep = "Refs: ";

	list = get_ref_list(commit_id);
	if (!list) {
		if (view_has_flags(view, VIEW_ADD_DESCRIBE_REF) && refs_contain_tag())
			add_line_text(view, sep, LINE_PP_REFS);
		return;
	}

	for (; list; list = list->next) {
		const struct ref *ref = list;
		const struct ref_format *fmt = get_ref_format(opt_reference_format, ref);

		if (!string_format_from(buf, &bufpos, "%s%s%s%s", sep,
					fmt->start, ref->name, fmt->end))
			return;
		sep = ", ";
	}

	if (bufpos == 0)
		return;

	add_line_text(view, buf, LINE_PP_REFS);
}