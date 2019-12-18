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
struct TYPE_5__ {scalar_t__ x0; scalar_t__ y0; scalar_t__ x1; scalar_t__ y1; } ;
typedef  TYPE_1__ fz_rect ;
struct TYPE_6__ {scalar_t__ x; scalar_t__ y; } ;
typedef  TYPE_2__ fz_point ;

/* Variables and functions */

__attribute__((used)) static inline void bound_expand(fz_rect *r, fz_point p)
{
	if (p.x < r->x0) r->x0 = p.x;
	if (p.y < r->y0) r->y0 = p.y;
	if (p.x > r->x1) r->x1 = p.x;
	if (p.y > r->y1) r->y1 = p.y;
}