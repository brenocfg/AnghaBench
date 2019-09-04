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
struct options_entry {int /*<<< orphan*/  value; } ;
struct options_array_item {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 scalar_t__ OPTIONS_IS_ARRAY (struct options_entry*) ; 
 struct options_array_item* options_array_item (struct options_entry*,int) ; 
 char* options_value_tostring (struct options_entry*,int /*<<< orphan*/ *,int) ; 
 char* xstrdup (char*) ; 

char *
options_tostring(struct options_entry *o, int idx, int numeric)
{
	struct options_array_item	*a;

	if (OPTIONS_IS_ARRAY(o)) {
		if (idx == -1)
			return (xstrdup(""));
		a = options_array_item(o, idx);
		if (a == NULL)
			return (xstrdup(""));
		return (options_value_tostring(o, &a->value, numeric));
	}
	return (options_value_tostring(o, &o->value, numeric));
}