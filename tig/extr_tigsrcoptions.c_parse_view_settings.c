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
struct enum_map_entry {int namelen; } ;
typedef  enum view_column_type { ____Placeholder_view_column_type } view_column_type ;
typedef  enum status_code { ____Placeholder_status_code } status_code ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int size; struct enum_map_entry* entries; } ;

/* Variables and functions */
 int SIZEOF_STR ; 
 int STRING_SIZE (char*) ; 
 scalar_t__ enum_equals (struct enum_map_entry const,char const*,size_t) ; 
 scalar_t__ enum_equals_prefix (struct enum_map_entry const,char const*,size_t) ; 
 scalar_t__ enum_name_copy (char*,int,char const*) ; 
 int parse_view_column_config (char const*,int,char const*,char const**) ; 
 int parse_view_config (struct view_column**,char const*,char const**) ; 
 size_t strlen (char const*) ; 
 char* strstr (char const*,char*) ; 
 TYPE_1__* view_column_type_map ; 

__attribute__((used)) static enum status_code
parse_view_settings(struct view_column **view_column, const char *name_, const char *argv[])
{
	char buf[SIZEOF_STR];
	const char *name = enum_name_copy(buf, sizeof(buf), name_) ? buf : name_;
	const char *prefixed;

	if ((prefixed = strstr(name, "-view-"))) {
		const char *column_name = prefixed + STRING_SIZE("-view-");
		size_t column_namelen = strlen(column_name);
		enum view_column_type type;

		for (type = 0; type < view_column_type_map->size; type++) {
			const struct enum_map_entry *column = &view_column_type_map->entries[type];

			if (enum_equals(*column, column_name, column_namelen))
				return parse_view_column_config(name, type, NULL, argv);

			if (enum_equals_prefix(*column, column_name, column_namelen))
				return parse_view_column_config(name, type,
								column_name + column->namelen + 1,
								argv);
		}
	}

	return parse_view_config(view_column, name, argv);
}