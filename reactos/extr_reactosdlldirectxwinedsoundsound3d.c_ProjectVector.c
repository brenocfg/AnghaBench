#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ D3DVECTOR ;
typedef  int D3DVALUE ;

/* Variables and functions */
 int ScalarProduct (TYPE_1__ const*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int VectorMagnitude (TYPE_1__ const*) ; 

__attribute__((used)) static inline D3DVALUE ProjectVector (const D3DVECTOR *a, const D3DVECTOR *p)
{
	D3DVALUE prod, result;
	prod = ScalarProduct(a, p);
	result = prod/VectorMagnitude(p);
	TRACE("length projection of (%f,%f,%f) on (%f,%f,%f) = %f\n", a->x, a->y, a->z, p->x,
              p->y, p->z, result);
	return result;
}