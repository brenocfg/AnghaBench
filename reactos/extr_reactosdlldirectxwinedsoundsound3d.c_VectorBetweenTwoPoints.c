#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ z; scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_1__ D3DVECTOR ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline D3DVECTOR VectorBetweenTwoPoints (const D3DVECTOR *a, const D3DVECTOR *b)
{
	D3DVECTOR c;
	c.x = b->x - a->x;
	c.y = b->y - a->y;
	c.z = b->z - a->z;
	TRACE("A (%f,%f,%f), B (%f,%f,%f), AB = (%f,%f,%f)\n", a->x, a->y, a->z, b->x, b->y,
	      b->z, c.x, c.y, c.z);
	return c;
}