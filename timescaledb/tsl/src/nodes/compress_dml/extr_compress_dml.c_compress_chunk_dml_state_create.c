#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * methods; } ;
struct TYPE_7__ {TYPE_1__ cscan_state; int /*<<< orphan*/  chunk_relid; } ;
struct TYPE_6__ {int /*<<< orphan*/  custom_private; } ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_2__ CustomScan ;
typedef  TYPE_3__ CompressChunkDmlState ;

/* Variables and functions */
 int /*<<< orphan*/  T_CustomScanState ; 
 int /*<<< orphan*/  compress_chunk_dml_state_methods ; 
 int /*<<< orphan*/  linitial_oid (int /*<<< orphan*/ ) ; 
 scalar_t__ newNode (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Node *
compress_chunk_dml_state_create(CustomScan *scan)
{
	CompressChunkDmlState *state;

	state = (CompressChunkDmlState *) newNode(sizeof(CompressChunkDmlState), T_CustomScanState);
	state->chunk_relid = linitial_oid(scan->custom_private);
	state->cscan_state.methods = &compress_chunk_dml_state_methods;
	return (Node *) state;
}