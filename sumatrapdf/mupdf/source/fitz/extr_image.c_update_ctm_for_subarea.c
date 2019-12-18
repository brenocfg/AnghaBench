#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {float a; float d; float e; float f; scalar_t__ c; scalar_t__ b; } ;
typedef  TYPE_1__ fz_matrix ;
struct TYPE_9__ {int x0; int y0; int x1; int y1; } ;
typedef  TYPE_2__ fz_irect ;

/* Variables and functions */
 TYPE_1__ fz_concat (TYPE_1__,TYPE_1__) ; 

__attribute__((used)) static void
update_ctm_for_subarea(fz_matrix *ctm, const fz_irect *subarea, int w, int h)
{
	fz_matrix m;

	if (subarea->x0 == 0 && subarea->y0 == 0 && subarea->x1 == w && subarea->y1 == h)
		return;

	m.a = (float) (subarea->x1 - subarea->x0) / w;
	m.b = 0;
	m.c = 0;
	m.d = (float) (subarea->y1 - subarea->y0) / h;
	m.e = (float) subarea->x0 / w;
	m.f = (float) subarea->y0 / h;
	*ctm = fz_concat(m, *ctm);
}