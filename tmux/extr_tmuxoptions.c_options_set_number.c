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
struct TYPE_2__ {long long number; } ;
struct options_entry {TYPE_1__ value; } ;
struct options {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPTIONS_IS_NUMBER (struct options_entry*) ; 
 int /*<<< orphan*/  fatalx (char*,char const*) ; 
 struct options_entry* options_default (struct options*,int /*<<< orphan*/ ) ; 
 struct options_entry* options_get_only (struct options*,char const*) ; 
 int /*<<< orphan*/  options_parent_table_entry (struct options*,char const*) ; 

struct options_entry *
options_set_number(struct options *oo, const char *name, long long value)
{
	struct options_entry	*o;

	if (*name == '@')
		fatalx("user option %s must be a string", name);

	o = options_get_only(oo, name);
	if (o == NULL) {
		o = options_default(oo, options_parent_table_entry(oo, name));
		if (o == NULL)
			return (NULL);
	}

	if (!OPTIONS_IS_NUMBER(o))
		fatalx("option %s is not a number", name);
	o->value.number = value;
	return (o);
}