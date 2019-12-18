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
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ fz_css_value ;
typedef  int /*<<< orphan*/  fz_css_number ;
typedef  int /*<<< orphan*/  fz_css_match ;

/* Variables and functions */
 int /*<<< orphan*/  N_LENGTH ; 
 int /*<<< orphan*/  make_number (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  number_from_value (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* value_from_property (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static fz_css_number
border_width_from_property(fz_css_match *match, const char *property)
{
	fz_css_value *value = value_from_property(match, property);
	if (value)
	{
		if (!strcmp(value->data, "thin"))
			return make_number(1, N_LENGTH);
		if (!strcmp(value->data, "medium"))
			return make_number(2, N_LENGTH);
		if (!strcmp(value->data, "thick"))
			return make_number(4, N_LENGTH);
		return number_from_value(value, 0, N_LENGTH);
	}
	return make_number(2, N_LENGTH); /* initial: 'medium' */
}