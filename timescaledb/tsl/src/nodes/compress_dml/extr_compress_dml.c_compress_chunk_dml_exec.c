#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_2__ {int /*<<< orphan*/  chunk_relid; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  CustomScanState ;
typedef  TYPE_1__ CompressChunkDmlState ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rel_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static TupleTableSlot *
compress_chunk_dml_exec(CustomScanState *node)
{
	CompressChunkDmlState *state = (CompressChunkDmlState *) node;
	Oid chunk_relid = state->chunk_relid;
	elog(ERROR,
		 "cannot update/delete rows from chunk \"%s\" as it is compressed",
		 get_rel_name(chunk_relid));
	return NULL;
}