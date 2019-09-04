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
struct diff_stat_context {char const* text; int type; } ;
typedef  enum line_type { ____Placeholder_line_type } line_type ;

/* Variables and functions */
 int /*<<< orphan*/  diff_common_add_cell (struct diff_stat_context*,int,int) ; 
 char* strchr (char const*,char) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static bool
diff_common_read_diff_stat_part(struct diff_stat_context *context, char c, enum line_type next_type)
{
	const char *sep = c == '|' ? strrchr(context->text, c) : strchr(context->text, c);

	if (sep == NULL)
		return false;

	diff_common_add_cell(context, sep - context->text, false);
	context->text = sep;
	context->type = next_type;

	return true;
}