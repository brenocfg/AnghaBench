#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ type; struct TYPE_4__* next; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ fz_css_value ;
typedef  int /*<<< orphan*/  fz_css_match ;

/* Variables and functions */
 scalar_t__ CSS_KEYWORD ; 
 int /*<<< orphan*/  add_property (int /*<<< orphan*/ *,char*,TYPE_1__*,int) ; 
 scalar_t__ keyword_in_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_style_position_kw ; 
 int /*<<< orphan*/  list_style_type_kw ; 
 int /*<<< orphan*/  nelem (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
add_shorthand_list_style(fz_css_match *match, fz_css_value *value, int spec)
{
	while (value)
	{
		if (value->type == CSS_KEYWORD)
		{
			if (keyword_in_list(value->data, list_style_type_kw, nelem(list_style_type_kw)))
			{
				add_property(match, "list-style-type", value, spec);
			}
			else if (keyword_in_list(value->data, list_style_position_kw, nelem(list_style_position_kw)))
			{
				add_property(match, "list-style-position", value, spec);
			}
		}
		value = value->next;
	}
}