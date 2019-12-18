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
struct line {scalar_t__ wrapped; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINE_DIFF_HEADER ; 
 struct line* find_prev_line_by_type (struct view*,struct line*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opt_wrap_lines ; 

__attribute__((used)) static bool
stage_chunk_is_wrapped(struct view *view, struct line *line)
{
	struct line *pos = find_prev_line_by_type(view, line, LINE_DIFF_HEADER);

	if (!opt_wrap_lines || !pos)
		return false;

	for (; pos <= line; pos++)
		if (pos->wrapped)
			return true;

	return false;
}