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
union options_value {char const* string; } ;
struct options_entry {int dummy; } ;
struct options_array_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  global_options ; 
 struct options_array_item* options_array_first (struct options_entry*) ; 
 union options_value* options_array_item_value (struct options_array_item*) ; 
 struct options_array_item* options_array_next (struct options_array_item*) ; 
 struct options_entry* options_get_only (int /*<<< orphan*/ ,char*) ; 
 char* strchr (char const*,char) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,size_t) ; 
 char* xstrdup (char const*) ; 

char *
cmd_get_alias(const char *name)
{
	struct options_entry		*o;
	struct options_array_item	*a;
	union options_value		*ov;
	size_t				 wanted, n;
	const char			*equals;

	o = options_get_only(global_options, "command-alias");
	if (o == NULL)
		return (NULL);
	wanted = strlen(name);

	a = options_array_first(o);
	while (a != NULL) {
		ov = options_array_item_value(a);

		equals = strchr(ov->string, '=');
		if (equals != NULL) {
			n = equals - ov->string;
			if (n == wanted && strncmp(name, ov->string, n) == 0)
				return (xstrdup(equals + 1));
		}

		a = options_array_next(a);
	}
	return (NULL);
}