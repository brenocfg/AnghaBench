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
typedef  union view_column_options {int dummy; } view_column_options ;
struct option_info {int dummy; } ;
typedef  enum view_column_type { ____Placeholder_view_column_type } view_column_type ;

/* Variables and functions */
 int /*<<< orphan*/  COLUMN_OPTIONS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEFINE_COLUMN_OPTION_INFO_CHECK ; 

struct option_info *
find_column_option_info(enum view_column_type type, union view_column_options *opts,
			const char *option, struct option_info *column_info,
			const char **column_name)
{
#define DEFINE_COLUMN_OPTION_INFO(name, type, flags) \
	{ #name, STRING_SIZE(#name), #type, &opt->name, flags },

#define DEFINE_COLUMN_OPTION_INFO_CHECK(name, id, options) \
	if (type == VIEW_COLUMN_##id) { \
		struct name##_options *opt = &opts->name; \
		struct option_info info[] = { \
			options(DEFINE_COLUMN_OPTION_INFO) \
		}; \
		struct option_info *match; \
		match = find_option_info(info, ARRAY_SIZE(info), #name, option); \
		if (match) { \
			*column_info = *match; \
			*column_name = #name; \
			return column_info; \
		} \
	}

	COLUMN_OPTIONS(DEFINE_COLUMN_OPTION_INFO_CHECK);

	*column_name = NULL;
	return NULL;
}