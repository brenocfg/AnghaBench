#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char const* data; } ;
typedef  TYPE_1__ fz_css_value ;
struct TYPE_8__ {struct TYPE_8__* up; } ;
typedef  TYPE_2__ fz_css_match ;

/* Variables and functions */
 int /*<<< orphan*/  inherit_list ; 
 scalar_t__ keyword_in_list (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nelem (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 TYPE_1__* value_from_raw_property (TYPE_2__*,char const*) ; 

__attribute__((used)) static fz_css_value *
value_from_property(fz_css_match *match, const char *name)
{
	fz_css_value *value;

	value = value_from_raw_property(match, name);
	if (match->up)
	{
		if (value && !strcmp(value->data, "inherit"))
			if (strcmp(name, "font-size") != 0) /* never inherit 'font-size' textually */
				return value_from_property(match->up, name);
		if (!value && keyword_in_list(name, inherit_list, nelem(inherit_list)))
			return value_from_property(match->up, name);
	}
	return value;
}