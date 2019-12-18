#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int len; scalar_t__ wmode; TYPE_1__* items; } ;
typedef  TYPE_2__ fz_text_span ;
struct TYPE_9__ {scalar_t__ x; scalar_t__ y; } ;
typedef  TYPE_3__ fz_point ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_7__ {scalar_t__ x; scalar_t__ y; scalar_t__ ucs; } ;

/* Variables and functions */
 TYPE_3__ fz_transform_point (TYPE_3__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
find_next_line_break(fz_context *ctx, const fz_text_span *span, fz_matrix inv_tm, int i)
{
	fz_point p, old_p;

	old_p.x = span->items[i].x;
	old_p.y = span->items[i].y;
	old_p = fz_transform_point(old_p, inv_tm);

	for (++i; i < span->len; ++i)
	{
		if (span->items[i].ucs >= 0)
		{
			p.x = span->items[i].x;
			p.y = span->items[i].y;
			p = fz_transform_point(p, inv_tm);
			if (span->wmode == 0)
			{
				if (p.y != old_p.y)
					return i;
			}
			else
			{
				if (p.x != old_p.x)
					return i;
			}
			old_p = p;
		}
	}

	return i;
}