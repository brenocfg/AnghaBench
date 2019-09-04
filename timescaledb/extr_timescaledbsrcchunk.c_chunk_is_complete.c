#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* constraints; } ;
struct TYPE_9__ {TYPE_1__* space; } ;
struct TYPE_8__ {scalar_t__ num_dimension_constraints; } ;
struct TYPE_7__ {scalar_t__ num_dimensions; } ;
typedef  TYPE_3__ ChunkScanCtx ;
typedef  TYPE_4__ Chunk ;

/* Variables and functions */

__attribute__((used)) static bool
chunk_is_complete(ChunkScanCtx *scanctx, Chunk *chunk)
{
	if (scanctx->space->num_dimensions != chunk->constraints->num_dimension_constraints)
		return false;

	return true;
}