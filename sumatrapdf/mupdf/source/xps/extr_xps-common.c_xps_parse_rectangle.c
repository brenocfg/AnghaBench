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
typedef  int /*<<< orphan*/  xps_document ;
struct TYPE_3__ {float x0; float y0; float x1; float y1; } ;
typedef  TYPE_1__ fz_rect ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 float fz_atof (char*) ; 

fz_rect
xps_parse_rectangle(fz_context *ctx, xps_document *doc, char *text)
{
	fz_rect rect;
	float args[4];
	char *s = text;
	int i;

	args[0] = 0; args[1] = 0;
	args[2] = 1; args[3] = 1;

	for (i = 0; i < 4 && *s; i++)
	{
		args[i] = fz_atof(s);
		while (*s && *s != ',')
			s++;
		if (*s == ',')
			s++;
	}

	rect.x0 = args[0];
	rect.y0 = args[1];
	rect.x1 = args[0] + args[2];
	rect.y1 = args[1] + args[3];
	return rect;
}