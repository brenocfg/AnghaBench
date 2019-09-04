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
struct TYPE_4__ {int x; int y; int z; } ;
typedef  TYPE_1__ D3DVECTOR ;
typedef  int D3DVALUE ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int,int,int,int,int,int,int) ; 

__attribute__((used)) static inline D3DVALUE ScalarProduct (const D3DVECTOR *a, const D3DVECTOR *b)
{
	D3DVALUE c;
	c = (a->x*b->x) + (a->y*b->y) + (a->z*b->z);
	TRACE("(%f,%f,%f) * (%f,%f,%f) = %f)\n", a->x, a->y, a->z, b->x, b->y,
	      b->z, c);
	return c;
}