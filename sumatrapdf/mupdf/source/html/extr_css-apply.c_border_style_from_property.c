#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ fz_css_value ;
typedef  int /*<<< orphan*/  fz_css_match ;

/* Variables and functions */
 int BS_NONE ; 
 int BS_SOLID ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* value_from_property (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int
border_style_from_property(fz_css_match *match, const char *property)
{
	fz_css_value *value = value_from_property(match, property);
	if (value)
	{
		if (!strcmp(value->data, "none")) return BS_NONE;
		else if (!strcmp(value->data, "hidden")) return BS_NONE;
		else if (!strcmp(value->data, "solid")) return BS_SOLID;
	}
	return BS_NONE;
}