#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* space; } ;
struct TYPE_4__ {int /*<<< orphan*/  num_dimensions; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ Hypertable ;
typedef  int /*<<< orphan*/  Chunk ;

/* Variables and functions */
 int /*<<< orphan*/  ts_chunk_constraint_create_on_chunk (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ts_chunk_get_by_relid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
process_add_constraint_chunk(Hypertable *ht, Oid chunk_relid, void *arg)
{
	Oid hypertable_constraint_oid = *((Oid *) arg);
	Chunk *chunk = ts_chunk_get_by_relid(chunk_relid, ht->space->num_dimensions, true);

	ts_chunk_constraint_create_on_chunk(chunk, hypertable_constraint_oid);
}