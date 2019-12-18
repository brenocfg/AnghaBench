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
 int PB_ALWAYS ; 
 int PB_AUTO ; 
 int PB_AVOID ; 
 int PB_LEFT ; 
 int PB_RIGHT ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* value_from_property (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
page_break_from_property(fz_css_match *match, char *prop)
{
	fz_css_value *value = value_from_property(match, prop);
	if (value)
	{
		if (!strcmp(value->data, "auto")) return PB_AUTO;
		else if (!strcmp(value->data, "always")) return PB_ALWAYS;
		else if (!strcmp(value->data, "avoid")) return PB_AVOID;
		else if (!strcmp(value->data, "left")) return PB_LEFT;
		else if (!strcmp(value->data, "right")) return PB_RIGHT;
	}
	return PB_AUTO;
}