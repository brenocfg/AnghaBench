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
struct option_info {int /*<<< orphan*/  name; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  prefixed ;

/* Variables and functions */
 int SIZEOF_STR ; 
 scalar_t__ enum_equals (struct option_info,char const*,size_t) ; 
 scalar_t__ enum_equals_prefix (struct option_info,char const*,size_t) ; 
 scalar_t__ enum_name_prefixed (char*,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  string_enum_compare (char const*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

struct option_info *
find_option_info(struct option_info *option, size_t options, const char *prefix, const char *name)
{
	size_t namelen = strlen(name);
	char prefixed[SIZEOF_STR];
	int i;

	if (*prefix && namelen == strlen(prefix) &&
	    !string_enum_compare(prefix, name, namelen)) {
		name = "display";
		namelen = strlen(name);
	}

	for (i = 0; i < options; i++) {
		if (!strcmp(option[i].type, "view_settings") &&
		    enum_equals_prefix(option[i], name, namelen))
			return &option[i];

		if (enum_equals(option[i], name, namelen))
			return &option[i];

		if (enum_name_prefixed(prefixed, sizeof(prefixed), prefix, option[i].name) &&
		    namelen == strlen(prefixed) &&
		    !string_enum_compare(prefixed, name, namelen))
			return &option[i];
	}

	return NULL;
}