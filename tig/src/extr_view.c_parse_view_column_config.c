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
struct view_column {int dummy; } ;
struct view {int /*<<< orphan*/  name; TYPE_1__* ops; } ;
typedef  enum view_column_type { ____Placeholder_view_column_type } view_column_type ;
typedef  enum status_code { ____Placeholder_status_code } status_code ;
struct TYPE_2__ {int column_bits; } ;

/* Variables and functions */
 int error (char*,char const*,...) ; 
 struct view* find_view (char const*) ; 
 struct view_column* get_view_column (struct view*,int) ; 
 int parse_view_column_config_exprs (struct view_column*,char const*) ; 
 int parse_view_column_option (struct view_column*,char const*,char const*) ; 
 char* view_column_name (int) ; 

enum status_code
parse_view_column_config(const char *view_name, enum view_column_type type,
			 const char *option_name, const char *argv[])
{
	struct view_column *column;
	struct view *view = find_view(view_name);

	if (!view)
		return error("Unknown view: %s", view_name);

	if (!(view->ops->column_bits & (1 << type)))
		return error("The %s view does not support %s column", view->name,
			     view_column_name(type));

	column = get_view_column(view, type);
	if (!column)
		return error("The %s view does not have a %s column configured", view->name,
			     view_column_name(type));

	if (option_name)
		return parse_view_column_option(column, option_name, argv[0]);
	return parse_view_column_config_exprs(column, argv[0]);
}