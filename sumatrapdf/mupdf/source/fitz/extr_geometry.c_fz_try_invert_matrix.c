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
struct TYPE_4__ {float a; float b; float c; float d; double e; double f; } ;
typedef  TYPE_1__ fz_matrix ;

/* Variables and functions */
 double DBL_EPSILON ; 

int
fz_try_invert_matrix(fz_matrix *dst, fz_matrix src)
{
	double sa = (double)src.a;
	double sb = (double)src.b;
	double sc = (double)src.c;
	double sd = (double)src.d;
	double da, db, dc, dd;
	double det = sa * sd - sb * sc;
	if (det >= -DBL_EPSILON && det <= DBL_EPSILON)
		return 1;
	det = 1 / det;
	da = sd * det;
	dst->a = (float)da;
	db = -sb * det;
	dst->b = (float)db;
	dc = -sc * det;
	dst->c = (float)dc;
	dd = sa * det;
	dst->d = (float)dd;
	da = -src.e * da - src.f * dc;
	dst->f = (float)(-src.e * db - src.f * dd);
	dst->e = (float)da;
	return 0;
}