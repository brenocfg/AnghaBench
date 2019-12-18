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
struct TYPE_4__ {float e; float a; float c; float f; float b; float d; } ;
typedef  TYPE_1__ fz_matrix ;

/* Variables and functions */

fz_matrix
fz_pre_translate(fz_matrix m, float tx, float ty)
{
	m.e += tx * m.a + ty * m.c;
	m.f += tx * m.b + ty * m.d;
	return m;
}