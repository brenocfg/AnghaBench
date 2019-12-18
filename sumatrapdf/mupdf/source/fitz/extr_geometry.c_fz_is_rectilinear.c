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
struct TYPE_3__ {int /*<<< orphan*/  d; int /*<<< orphan*/  a; int /*<<< orphan*/  c; int /*<<< orphan*/  b; } ;
typedef  TYPE_1__ fz_matrix ;

/* Variables and functions */
 scalar_t__ FLT_EPSILON ; 
 scalar_t__ fabsf (int /*<<< orphan*/ ) ; 

int
fz_is_rectilinear(fz_matrix m)
{
	return (fabsf(m.b) < FLT_EPSILON && fabsf(m.c) < FLT_EPSILON) ||
		(fabsf(m.a) < FLT_EPSILON && fabsf(m.d) < FLT_EPSILON);
}