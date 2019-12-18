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
struct diff_stat_context {char const* member_0; int /*<<< orphan*/  text; int /*<<< orphan*/  member_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINE_DEFAULT ; 
 int /*<<< orphan*/  LINE_DIFF_ADD ; 
 int /*<<< orphan*/  LINE_DIFF_DEL ; 
 int /*<<< orphan*/  LINE_DIFF_STAT ; 
 int /*<<< orphan*/  diff_common_add_cell (struct diff_stat_context*,int /*<<< orphan*/ ,int) ; 
 struct line* diff_common_add_line (struct view*,char const*,int /*<<< orphan*/ ,struct diff_stat_context*) ; 
 scalar_t__ diff_common_read_diff_stat_part (struct diff_stat_context*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct line *
diff_common_read_diff_stat(struct view *view, const char *text)
{
	struct diff_stat_context context = { text, LINE_DIFF_STAT };

	diff_common_read_diff_stat_part(&context, '|', LINE_DEFAULT);
	if (diff_common_read_diff_stat_part(&context, 'B', LINE_DEFAULT)) {
		/* Handle binary diffstat: Bin <deleted> -> <added> bytes */
		diff_common_read_diff_stat_part(&context, ' ', LINE_DIFF_DEL);
		diff_common_read_diff_stat_part(&context, '-', LINE_DEFAULT);
		diff_common_read_diff_stat_part(&context, ' ', LINE_DIFF_ADD);
		diff_common_read_diff_stat_part(&context, 'b', LINE_DEFAULT);

	} else {
		diff_common_read_diff_stat_part(&context, '+', LINE_DIFF_ADD);
		diff_common_read_diff_stat_part(&context, '-', LINE_DIFF_DEL);
	}
	diff_common_add_cell(&context, strlen(context.text), false);

	return diff_common_add_line(view, text, LINE_DIFF_STAT, &context);
}