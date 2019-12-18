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
struct style {int dummy; } ;
struct TYPE_2__ {struct style style; } ;
struct options_entry {TYPE_1__ value; } ;
struct options {int dummy; } ;

/* Variables and functions */
 scalar_t__ OPTIONS_IS_STYLE (struct options_entry*) ; 
 int /*<<< orphan*/  fatalx (char*,char const*) ; 
 int /*<<< orphan*/  grid_default_cell ; 
 struct options_entry* options_default (struct options*,int /*<<< orphan*/ ) ; 
 struct options_entry* options_get_only (struct options*,char const*) ; 
 int /*<<< orphan*/  options_parent_table_entry (struct options*,char const*) ; 
 int /*<<< orphan*/  style_copy (struct style*,struct style*) ; 
 int style_parse (struct style*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  style_set (struct style*,int /*<<< orphan*/ *) ; 

struct options_entry *
options_set_style(struct options *oo, const char *name, int append,
    const char *value)
{
	struct options_entry	*o;
	struct style		 sy;

	if (*name == '@')
		fatalx("user option %s must be a string", name);

	o = options_get_only(oo, name);
	if (o != NULL && append && OPTIONS_IS_STYLE(o))
		style_copy(&sy, &o->value.style);
	else
		style_set(&sy, &grid_default_cell);
	if (style_parse(&sy, &grid_default_cell, value) == -1)
		return (NULL);
	if (o == NULL) {
		o = options_default(oo, options_parent_table_entry(oo, name));
		if (o == NULL)
			return (NULL);
	}

	if (!OPTIONS_IS_STYLE(o))
		fatalx("option %s is not a style", name);
	style_copy(&o->value.style, &sy);
	return (o);
}