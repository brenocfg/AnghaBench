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
struct reference {struct ref const* ref; } ;
struct ref {int /*<<< orphan*/  type; } ;
struct line {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINE_DEFAULT ; 
 int /*<<< orphan*/  REFERENCE_BRANCH ; 
 int /*<<< orphan*/  REFERENCE_HEAD ; 
 int /*<<< orphan*/  REFERENCE_LOCAL_TAG ; 
 int /*<<< orphan*/  REFERENCE_REMOTE ; 
 int /*<<< orphan*/  REFERENCE_TAG ; 
 int /*<<< orphan*/  REFERENCE_TRACKED_REMOTE ; 
#define  REFS_FILTER_BRANCHES 131 
#define  REFS_FILTER_NONE 130 
#define  REFS_FILTER_REMOTES 129 
#define  REFS_FILTER_TAGS 128 
 struct line* add_line_alloc (struct view*,struct reference**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ref const* refs_all ; 
 int refs_filter ; 
 int /*<<< orphan*/  view_column_info_update (struct view*,struct line*) ; 

__attribute__((used)) static bool
refs_open_visitor(void *data, const struct ref *ref)
{
	struct view *view = data;
	struct reference *reference;
	bool is_all = ref == refs_all;
	struct line *line;

        if (!is_all)
		switch (refs_filter) {
		case REFS_FILTER_TAGS:
			if (ref->type != REFERENCE_TAG && ref->type != REFERENCE_LOCAL_TAG)
				return true;
			break;
		case REFS_FILTER_BRANCHES:
			if (ref->type != REFERENCE_BRANCH && ref->type != REFERENCE_HEAD)
				return true;
			break;
		case REFS_FILTER_REMOTES:
			if (ref->type != REFERENCE_TRACKED_REMOTE && ref->type != REFERENCE_REMOTE)
				return true;
			break;
		case REFS_FILTER_NONE:
		default:
			break;
		}

	line = add_line_alloc(view, &reference, LINE_DEFAULT, 0, is_all);
	if (!line)
		return false;

	reference->ref = ref;
	view_column_info_update(view, line);

	return true;
}