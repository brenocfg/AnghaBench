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
typedef  scalar_t__ int32 ;
struct TYPE_7__ {scalar_t__ capacity; } ;
typedef  TYPE_1__ DimensionVec ;

/* Variables and functions */
 int /*<<< orphan*/  DIMENSION_VEC_SIZE (scalar_t__) ; 
 TYPE_1__* palloc (int /*<<< orphan*/ ) ; 
 TYPE_1__* repalloc (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static DimensionVec *
dimension_vec_expand(DimensionVec *vec, int32 new_capacity)
{
	if (vec != NULL && vec->capacity >= new_capacity)
		return vec;

	if (NULL == vec)
		vec = palloc(DIMENSION_VEC_SIZE(new_capacity));
	else
		vec = repalloc(vec, DIMENSION_VEC_SIZE(new_capacity));

	vec->capacity = new_capacity;

	return vec;
}