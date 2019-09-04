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
struct TYPE_2__ {size_t lineno; } ;
struct view {int matched_lines; size_t* matched_line; int /*<<< orphan*/  grep; TYPE_1__ pos; } ;
typedef  enum status_code { ____Placeholder_status_code } status_code ;

/* Variables and functions */
 int /*<<< orphan*/  select_view_line (struct view*,size_t) ; 
 int success (char*,size_t,int /*<<< orphan*/ ,size_t,size_t) ; 

__attribute__((used)) static enum status_code
find_next_match_line(struct view *view, int direction, bool wrapped)
{
	/* Note, `i` is unsigned and will wrap around in which case it
	 * will become bigger than view->matched_lines. */
	size_t i = direction > 0 ? 0 : view->matched_lines - 1;

	for (; i < view->matched_lines; i += direction) {
		size_t lineno = view->matched_line[i];

		if (direction > 0) {
			if (!wrapped && lineno <= view->pos.lineno)
				continue;
			if (wrapped && lineno > view->pos.lineno)
				continue;
		} else {
			if (!wrapped && lineno >= view->pos.lineno)
				continue;
			if (wrapped && lineno < view->pos.lineno)
				continue;
		}

		select_view_line(view, lineno);
		return success("Line %zu matches '%s' (%zu of %zu)", lineno + 1, view->grep, i + 1, view->matched_lines);
	}

	return -1;
}