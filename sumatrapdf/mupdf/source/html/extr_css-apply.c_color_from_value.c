#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char type; int /*<<< orphan*/ * data; TYPE_1__* next; struct TYPE_6__* args; } ;
typedef  TYPE_2__ fz_css_value ;
typedef  int /*<<< orphan*/  fz_css_color ;
struct TYPE_5__ {TYPE_2__* next; } ;

/* Variables and functions */
 char CSS_HASH ; 
 char CSS_KEYWORD ; 
 int /*<<< orphan*/  N_NUMBER ; 
 int fz_from_css_number (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_color (int,int,int,int) ; 
 int /*<<< orphan*/  number_from_value (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ *,char*) ; 
 size_t strlen (int /*<<< orphan*/ *) ; 
 int tohex (int /*<<< orphan*/ ) ; 

__attribute__((used)) static fz_css_color
color_from_value(fz_css_value *value, fz_css_color initial)
{
	if (!value)
		return initial;

	if (value->type == CSS_HASH)
	{
		int r, g, b;
		size_t n;
hex_color:
		n = strlen(value->data);
		if (n == 3)
		{
			r = tohex(value->data[0]) * 16 + tohex(value->data[0]);
			g = tohex(value->data[1]) * 16 + tohex(value->data[1]);
			b = tohex(value->data[2]) * 16 + tohex(value->data[2]);
		}
		else if (n == 6)
		{
			r = tohex(value->data[0]) * 16 + tohex(value->data[1]);
			g = tohex(value->data[2]) * 16 + tohex(value->data[3]);
			b = tohex(value->data[4]) * 16 + tohex(value->data[5]);
		}
		else
		{
			r = g = b = 0;
		}
		return make_color(r, g, b, 255);
	}

	if (value->type == '(' && !strcmp(value->data, "rgb"))
	{
		fz_css_value *vr, *vg, *vb;
		int r, g, b;
		vr = value->args;
		vg = vr && vr->next ? vr->next->next : NULL; /* skip the ',' nodes */
		vb = vg && vg->next ? vg->next->next : NULL; /* skip the ',' nodes */
		r = fz_from_css_number(number_from_value(vr, 0, N_NUMBER), 255, 255, 0);
		g = fz_from_css_number(number_from_value(vg, 0, N_NUMBER), 255, 255, 0);
		b = fz_from_css_number(number_from_value(vb, 0, N_NUMBER), 255, 255, 0);
		return make_color(r, g, b, 255);
	}

	if (value->type == CSS_KEYWORD)
	{
		if (!strcmp(value->data, "transparent"))
			return make_color(0, 0, 0, 0);
		if (!strcmp(value->data, "maroon"))
			return make_color(0x80, 0x00, 0x00, 255);
		if (!strcmp(value->data, "red"))
			return make_color(0xFF, 0x00, 0x00, 255);
		if (!strcmp(value->data, "orange"))
			return make_color(0xFF, 0xA5, 0x00, 255);
		if (!strcmp(value->data, "yellow"))
			return make_color(0xFF, 0xFF, 0x00, 255);
		if (!strcmp(value->data, "olive"))
			return make_color(0x80, 0x80, 0x00, 255);
		if (!strcmp(value->data, "purple"))
			return make_color(0x80, 0x00, 0x80, 255);
		if (!strcmp(value->data, "fuchsia"))
			return make_color(0xFF, 0x00, 0xFF, 255);
		if (!strcmp(value->data, "white"))
			return make_color(0xFF, 0xFF, 0xFF, 255);
		if (!strcmp(value->data, "lime"))
			return make_color(0x00, 0xFF, 0x00, 255);
		if (!strcmp(value->data, "green"))
			return make_color(0x00, 0x80, 0x00, 255);
		if (!strcmp(value->data, "navy"))
			return make_color(0x00, 0x00, 0x80, 255);
		if (!strcmp(value->data, "blue"))
			return make_color(0x00, 0x00, 0xFF, 255);
		if (!strcmp(value->data, "aqua"))
			return make_color(0x00, 0xFF, 0xFF, 255);
		if (!strcmp(value->data, "teal"))
			return make_color(0x00, 0x80, 0x80, 255);
		if (!strcmp(value->data, "black"))
			return make_color(0x00, 0x00, 0x00, 255);
		if (!strcmp(value->data, "silver"))
			return make_color(0xC0, 0xC0, 0xC0, 255);
		if (!strcmp(value->data, "gray"))
			return make_color(0x80, 0x80, 0x80, 255);
		goto hex_color; /* last ditch attempt: maybe it's a #XXXXXX color without the # */
	}
	return initial;
}