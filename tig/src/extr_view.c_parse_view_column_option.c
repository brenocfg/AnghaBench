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
struct view_column {int dummy; } ;
typedef  enum status_code { ____Placeholder_status_code } status_code ;

/* Variables and functions */
 int /*<<< orphan*/  COLUMN_OPTIONS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEFINE_COLUMN_OPTIONS_PARSE ; 
 int error (char*,char const*) ; 

__attribute__((used)) static enum status_code
parse_view_column_option(struct view_column *column,
			 const char *opt_name, const char *opt_value)
{
#define DEFINE_COLUMN_OPTION_INFO(name, type, flags) \
	{ #name, STRING_SIZE(#name), #type, &opt->name, flags },

#define DEFINE_COLUMN_OPTIONS_PARSE(name, id, options) \
	if (column->type == VIEW_COLUMN_##id) { \
		struct name##_options *opt = &column->opt.name; \
		struct option_info info[] = { \
			options(DEFINE_COLUMN_OPTION_INFO) \
		}; \
		struct option_info *option = find_option_info(info, ARRAY_SIZE(info), "", opt_name); \
		if (!option) \
			return error("Unknown option `%s' for column %s", opt_name, \
				     view_column_name(VIEW_COLUMN_##id)); \
		return parse_option(option, #name, opt_value); \
	}

	COLUMN_OPTIONS(DEFINE_COLUMN_OPTIONS_PARSE);

	return error("Unknown view column option: %s", opt_name);
}