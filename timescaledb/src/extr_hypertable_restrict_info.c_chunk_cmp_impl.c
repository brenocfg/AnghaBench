#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
struct TYPE_8__ {TYPE_2__ fd; TYPE_1__* cube; } ;
struct TYPE_6__ {int /*<<< orphan*/ * slices; } ;
typedef  TYPE_3__ Chunk ;

/* Variables and functions */
 int VALUE_CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ts_dimension_slice_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
chunk_cmp_impl(const Chunk *c1, const Chunk *c2)
{
	int cmp = ts_dimension_slice_cmp(c1->cube->slices[0], c2->cube->slices[0]);

	if (cmp == 0)
		cmp = VALUE_CMP(c1->fd.id, c2->fd.id);

	return cmp;
}