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
struct line {int dummy; } ;

/* Variables and functions */
 scalar_t__ LINE_STAT_STAGED ; 
 scalar_t__ LINE_STAT_UNSTAGED ; 
 int /*<<< orphan*/  diff_common_select (struct view*,struct line*,char const*) ; 
 scalar_t__ stage_line_type ; 

__attribute__((used)) static void
stage_select(struct view *view, struct line *line)
{
	const char *changes_msg = stage_line_type == LINE_STAT_STAGED ? "Staged changes"
				: stage_line_type == LINE_STAT_UNSTAGED ? "Unstaged changes"
				: NULL;

	diff_common_select(view, line, changes_msg);
}