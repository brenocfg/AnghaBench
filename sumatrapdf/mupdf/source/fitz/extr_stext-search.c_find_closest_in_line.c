#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_21__ {scalar_t__ x; scalar_t__ y; } ;
struct TYPE_15__ {scalar_t__ y0; scalar_t__ y1; scalar_t__ x0; scalar_t__ x1; } ;
struct TYPE_22__ {TYPE_7__ dir; TYPE_9__* first_char; TYPE_1__ bbox; } ;
typedef  TYPE_8__ fz_stext_line ;
struct TYPE_19__ {int x; int y; } ;
struct TYPE_18__ {int x; int y; } ;
struct TYPE_17__ {int x; int y; } ;
struct TYPE_16__ {int x; int y; } ;
struct TYPE_20__ {TYPE_5__ lr; TYPE_4__ ll; TYPE_3__ ur; TYPE_2__ ul; } ;
struct TYPE_23__ {TYPE_6__ quad; struct TYPE_23__* next; } ;
typedef  TYPE_9__ fz_stext_char ;
struct TYPE_14__ {scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_10__ fz_point ;

/* Variables and functions */
 float dist2 (float,float) ; 
 int line_length (TYPE_8__*) ; 

__attribute__((used)) static int find_closest_in_line(fz_stext_line *line, int idx, fz_point p)
{
	fz_stext_char *ch;
	float closest_dist = 1e30f;
	int closest_idx = idx;

	if (line->dir.x > line->dir.y)
	{
		if (p.y < line->bbox.y0)
			return idx;
		if (p.y > line->bbox.y1)
			return idx + line_length(line);
	}
	else
	{
		if (p.x < line->bbox.x0)
			return idx + line_length(line);
		if (p.x > line->bbox.x1)
			return idx;
	}

	for (ch = line->first_char; ch; ch = ch->next)
	{
		float mid_x = (ch->quad.ul.x + ch->quad.ur.x + ch->quad.ll.x + ch->quad.lr.x) / 4;
		float mid_y = (ch->quad.ul.y + ch->quad.ur.y + ch->quad.ll.y + ch->quad.lr.y) / 4;
		float this_dist = dist2(p.x - mid_x, p.y - mid_y);
		if (this_dist < closest_dist)
		{
			closest_dist = this_dist;
			if (line->dir.x > line->dir.y)
				closest_idx = (p.x < mid_x) ? idx : idx+1;
			else
				closest_idx = (p.y < mid_y) ? idx : idx+1;
		}
		++idx;
	}
	return closest_idx;
}