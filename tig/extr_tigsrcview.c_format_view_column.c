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
struct view_column {int /*<<< orphan*/  type; } ;
typedef  enum status_code { ____Placeholder_status_code } status_code ;

/* Variables and functions */
 int /*<<< orphan*/  COLUMN_OPTIONS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FORMAT_COLUMN_OPTIONS_PARSE ; 
 int error (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum status_code
format_view_column(struct view_column *column, char buf[], size_t bufsize)
{
#define FORMAT_COLUMN_OPTION_INFO(name, type, flags) \
	{ #name, STRING_SIZE(#name), #type, &opt->name, flags },

#define FORMAT_COLUMN_OPTIONS_PARSE(col_name, id, options) \
	if (column->type == VIEW_COLUMN_##id) { \
		struct col_name##_options *opt = &column->opt.col_name; \
		struct option_info info[] = { \
			options(FORMAT_COLUMN_OPTION_INFO) \
		}; \
		\
		return format_view_column_options(info, ARRAY_SIZE(info), buf, bufsize); \
	}

	COLUMN_OPTIONS(FORMAT_COLUMN_OPTIONS_PARSE);

	return error("Unknown view column type: %d", column->type);
}