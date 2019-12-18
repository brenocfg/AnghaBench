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
struct ref_format {int dummy; } ;
struct enum_map {int /*<<< orphan*/  size; } ;
typedef  enum status_code { ____Placeholder_status_code } status_code ;

/* Variables and functions */
 int ERROR_OUT_OF_MEMORY ; 
 int SUCCESS ; 
 struct ref_format** calloc (int /*<<< orphan*/ ,int) ; 
 int parse_ref_format_arg (struct ref_format**,char const*,struct enum_map const*) ; 
 struct enum_map* reference_type_map ; 

enum status_code
parse_ref_formats(struct ref_format ***formats, const char *argv[])
{
	const struct enum_map *map = reference_type_map;
	int argc;

	if (!*formats) {
		*formats = calloc(reference_type_map->size, sizeof(struct ref_format *));
		if (!*formats)
			return ERROR_OUT_OF_MEMORY;
	}

	for (argc = 0; argv[argc]; argc++) {
		enum status_code code = parse_ref_format_arg(*formats, argv[argc], map);
		if (code != SUCCESS)
			return code;
	}

	return SUCCESS;
}