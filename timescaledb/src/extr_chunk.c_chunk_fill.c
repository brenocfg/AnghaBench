#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
struct TYPE_9__ {TYPE_2__ schema_name; TYPE_1__ table_name; } ;
struct TYPE_8__ {int /*<<< orphan*/  table_id; int /*<<< orphan*/  hypertable_relid; TYPE_4__ fd; } ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_3__ Chunk ;

/* Variables and functions */
 int /*<<< orphan*/  chunk_formdata_fill (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_namespace_oid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_relname_relid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_inheritance_parent_relid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
chunk_fill(Chunk *chunk, HeapTuple tuple, TupleDesc desc)
{
	chunk_formdata_fill(&chunk->fd, tuple, desc);

	chunk->table_id = get_relname_relid(chunk->fd.table_name.data,
										get_namespace_oid(chunk->fd.schema_name.data, true));
	chunk->hypertable_relid = ts_inheritance_parent_relid(chunk->table_id);
}