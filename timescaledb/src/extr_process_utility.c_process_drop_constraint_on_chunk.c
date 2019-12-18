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
struct TYPE_8__ {int /*<<< orphan*/  id; } ;
struct TYPE_10__ {TYPE_2__ fd; } ;
struct TYPE_9__ {TYPE_1__* space; } ;
struct TYPE_7__ {int /*<<< orphan*/  num_dimensions; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_3__ Hypertable ;
typedef  TYPE_4__ Chunk ;

/* Variables and functions */
 int /*<<< orphan*/  ts_chunk_constraint_delete_by_hypertable_constraint_name (int /*<<< orphan*/ ,char*,int,int) ; 
 TYPE_4__* ts_chunk_get_by_relid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
process_drop_constraint_on_chunk(Hypertable *ht, Oid chunk_relid, void *arg)
{
	char *hypertable_constraint_name = arg;
	Chunk *chunk = ts_chunk_get_by_relid(chunk_relid, ht->space->num_dimensions, true);

	/* drop both metadata and table; sql_drop won't be called recursively */
	ts_chunk_constraint_delete_by_hypertable_constraint_name(chunk->fd.id,
															 hypertable_constraint_name,
															 true,
															 true);
}