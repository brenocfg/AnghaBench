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
struct TYPE_8__ {TYPE_1__* constraints; } ;
struct TYPE_7__ {scalar_t__ num_dimensions; } ;
struct TYPE_6__ {scalar_t__ num_dimension_constraints; } ;
typedef  TYPE_2__ Hyperspace ;
typedef  TYPE_3__ Chunk ;

/* Variables and functions */

__attribute__((used)) static inline bool
chunk_is_complete(Chunk *chunk, Hyperspace *space)
{
	return space->num_dimensions == chunk->constraints->num_dimension_constraints;
}