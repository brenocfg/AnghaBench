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
struct ref {int dummy; } ;
struct line {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINE_DEFAULT ; 
 struct line* add_line_alloc (struct view*,struct reference**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ref const* refs_all ; 
 int /*<<< orphan*/  view_column_info_update (struct view*,struct line*) ; 

__attribute__((used)) static bool
refs_open_visitor(void *data, const struct ref *ref)
{
	struct view *view = data;
	struct reference *reference;
	bool is_all = ref == refs_all;
	struct line *line;

	line = add_line_alloc(view, &reference, LINE_DEFAULT, 0, is_all);
	if (!line)
		return false;

	reference->ref = ref;
	view_column_info_update(view, line);

	return true;
}