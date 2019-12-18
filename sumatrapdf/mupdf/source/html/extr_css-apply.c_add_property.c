#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_css_value ;
struct TYPE_11__ {int count; TYPE_2__* prop; } ;
typedef  TYPE_1__ fz_css_match ;
struct TYPE_12__ {char const* name; int spec; int /*<<< orphan*/ * value; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_shorthand_border (TYPE_1__*,int /*<<< orphan*/ *,int,int,int,int,int) ; 
 int /*<<< orphan*/  add_shorthand_border_color (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  add_shorthand_border_style (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  add_shorthand_border_width (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  add_shorthand_list_style (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  add_shorthand_margin (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  add_shorthand_padding (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ nelem (TYPE_2__*) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 

__attribute__((used)) static void
add_property(fz_css_match *match, const char *name, fz_css_value *value, int spec)
{
	int i;

	if (!strcmp(name, "margin"))
	{
		add_shorthand_margin(match, value, spec);
		return;
	}
	if (!strcmp(name, "padding"))
	{
		add_shorthand_padding(match, value, spec);
		return;
	}
	if (!strcmp(name, "border-width"))
	{
		add_shorthand_border_width(match, value, spec);
		return;
	}
	if (!strcmp(name, "border-color"))
	{
		add_shorthand_border_color(match, value, spec);
		return;
	}
	if (!strcmp(name, "border-style"))
	{
		add_shorthand_border_style(match, value, spec);
		return;
	}
	if (!strcmp(name, "border"))
	{
		add_shorthand_border(match, value, spec, 1, 1, 1, 1);
		return;
	}
	if (!strcmp(name, "border-top"))
	{
		add_shorthand_border(match, value, spec, 1, 0, 0, 0);
		return;
	}
	if (!strcmp(name, "border-right"))
	{
		add_shorthand_border(match, value, spec, 0, 1, 0, 0);
		return;
	}
	if (!strcmp(name, "border-bottom"))
	{
		add_shorthand_border(match, value, spec, 0, 0, 1, 0);
		return;
	}
	if (!strcmp(name, "border-left"))
	{
		add_shorthand_border(match, value, spec, 0, 0, 0, 1);
		return;
	}
	if (!strcmp(name, "list-style"))
	{
		add_shorthand_list_style(match, value, spec);
		return;
	}

	/* shorthand expansions: */
	/* TODO: border-color */
	/* TODO: border-style */
	/* TODO: font */
	/* TODO: list-style */
	/* TODO: background */

	for (i = 0; i < match->count; ++i)
	{
		if (!strcmp(match->prop[i].name, name))
		{
			if (match->prop[i].spec <= spec)
			{
				match->prop[i].value = value;
				match->prop[i].spec = spec;
			}
			return;
		}
	}

	if (match->count + 1 >= (int)nelem(match->prop))
	{
		// fz_warn(ctx, "too many css properties");
		return;
	}

	match->prop[match->count].name = name;
	match->prop[match->count].value = value;
	match->prop[match->count].spec = spec;
	++match->count;
}