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
struct TYPE_3__ {scalar_t__ type; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ fz_css_value ;
typedef  int /*<<< orphan*/  fz_css_number ;

/* Variables and functions */
 scalar_t__ CSS_KEYWORD ; 
 scalar_t__ CSS_LENGTH ; 
 scalar_t__ CSS_NUMBER ; 
 scalar_t__ CSS_PERCENT ; 
 int N_AUTO ; 
 int N_LENGTH ; 
 int N_NUMBER ; 
 int N_PERCENT ; 
 int N_SCALE ; 
 float fz_css_strtof (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  make_number (float,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static fz_css_number
number_from_value(fz_css_value *value, float initial, int initial_unit)
{
	char *p;

	if (!value)
		return make_number(initial, initial_unit);

	if (value->type == CSS_PERCENT)
		return make_number(fz_css_strtof(value->data, NULL), N_PERCENT);

	if (value->type == CSS_NUMBER)
		return make_number(fz_css_strtof(value->data, NULL), N_NUMBER);

	if (value->type == CSS_LENGTH)
	{
		float x = fz_css_strtof(value->data, &p);

		if (p[0] == 'e' && p[1] == 'm' && p[2] == 0)
			return make_number(x, N_SCALE);
		if (p[0] == 'e' && p[1] == 'x' && p[2] == 0)
			return make_number(x / 2, N_SCALE);

		if (p[0] == 'i' && p[1] == 'n' && p[2] == 0)
			return make_number(x * 72, N_LENGTH);
		if (p[0] == 'c' && p[1] == 'm' && p[2] == 0)
			return make_number(x * 7200 / 254, N_LENGTH);
		if (p[0] == 'm' && p[1] == 'm' && p[2] == 0)
			return make_number(x * 720 / 254, N_LENGTH);
		if (p[0] == 'p' && p[1] == 'c' && p[2] == 0)
			return make_number(x * 12, N_LENGTH);

		if (p[0] == 'p' && p[1] == 't' && p[2] == 0)
			return make_number(x, N_LENGTH);
		if (p[0] == 'p' && p[1] == 'x' && p[2] == 0)
			return make_number(x, N_LENGTH);

		/* FIXME: 'rem' should be 'em' of root element. This is a bad approximation. */
		if (p[0] == 'r' && p[1] == 'e' && p[2] == 'm' && p[3] == 0)
			return make_number(x * 16, N_LENGTH);

		/* FIXME: 'ch' should be width of '0' character. This is an approximation. */
		if (p[0] == 'c' && p[1] == 'h' && p[2] == 0)
			return make_number(x / 2, N_LENGTH);

		return make_number(x, N_LENGTH);
	}

	if (value->type == CSS_KEYWORD)
	{
		if (!strcmp(value->data, "auto"))
			return make_number(0, N_AUTO);
	}

	return make_number(initial, initial_unit);
}