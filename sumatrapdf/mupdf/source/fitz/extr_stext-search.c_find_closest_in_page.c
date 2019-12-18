#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_5__* first_block; } ;
typedef  TYPE_3__ fz_stext_page ;
struct TYPE_18__ {scalar_t__ x0; scalar_t__ x1; scalar_t__ y0; scalar_t__ y1; } ;
struct TYPE_16__ {TYPE_6__ bbox; struct TYPE_16__* next; } ;
typedef  TYPE_4__ fz_stext_line ;
struct TYPE_13__ {TYPE_4__* first_line; } ;
struct TYPE_14__ {TYPE_1__ t; } ;
struct TYPE_17__ {scalar_t__ type; TYPE_2__ u; struct TYPE_17__* next; } ;
typedef  TYPE_5__ fz_stext_block ;
typedef  TYPE_6__ fz_rect ;
struct TYPE_19__ {scalar_t__ x; scalar_t__ y; } ;
typedef  TYPE_7__ fz_point ;

/* Variables and functions */
 scalar_t__ FZ_STEXT_BLOCK_TEXT ; 
 float dist2 (scalar_t__,scalar_t__) ; 
 int find_closest_in_line (TYPE_4__*,int,TYPE_7__) ; 
 float fz_min (float,float) ; 
 scalar_t__ line_length (TYPE_4__*) ; 

__attribute__((used)) static int find_closest_in_page(fz_stext_page *page, fz_point p)
{
	fz_stext_block *block;
	fz_stext_line *line;
	fz_stext_line *closest_line = NULL;
	int closest_idx = 0;
	float closest_dist = 1e30f;
	float this_dist;
	int idx = 0;

	for (block = page->first_block; block; block = block->next)
	{
		if (block->type != FZ_STEXT_BLOCK_TEXT)
			continue;
		for (line = block->u.t.first_line; line; line = line->next)
		{
			fz_rect box = line->bbox;
			if (p.x >= box.x0 && p.x <= box.x1)
			{
				if (p.y < box.y0)
					this_dist = dist2(box.y0 - p.y, 0);
				else if (p.y > box.y1)
					this_dist = dist2(p.y - box.y1, 0);
				else
					this_dist = 0;
			}
			else if (p.y >= box.y0 && p.y <= box.y1)
			{
				if (p.x < box.x0)
					this_dist = dist2(box.x0 - p.x, 0);
				else if (p.x > box.x1)
					this_dist = dist2(p.x - box.x1, 0);
				else
					this_dist = 0;
			}
			else
			{
				float dul = dist2(p.x - box.x0, p.y - box.y0);
				float dur = dist2(p.x - box.x1, p.y - box.y0);
				float dll = dist2(p.x - box.x0, p.y - box.y1);
				float dlr = dist2(p.x - box.x1, p.y - box.y1);
				this_dist = fz_min(fz_min(dul, dur), fz_min(dll, dlr));
			}
			if (this_dist < closest_dist)
			{
				closest_dist = this_dist;
				closest_line = line;
				closest_idx = idx;
			}
			idx += line_length(line);
		}
	}

	if (closest_line)
		return find_closest_in_line(closest_line, closest_idx, p);
	return 0;
}