#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_7__ {int /*<<< orphan*/  hypertable_constraint_name; } ;
struct TYPE_9__ {TYPE_1__ fd; } ;
struct TYPE_8__ {scalar_t__ contype; int /*<<< orphan*/  conindid; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__ FormData_pg_constraint ;
typedef  TYPE_3__ ChunkConstraint ;

/* Variables and functions */
 scalar_t__ CONSTRAINT_FOREIGN ; 
 int /*<<< orphan*/  CONSTROID ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chunk_constraint_create_on_table (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_relation_constraint_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  is_dimension_constraint (TYPE_3__*) ; 
 int /*<<< orphan*/  ts_chunk_index_create_from_constraint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_process_utility_set_expect_chunk_modification (int) ; 

__attribute__((used)) static Oid
chunk_constraint_create(ChunkConstraint *cc, Oid chunk_oid, int32 chunk_id, Oid hypertable_oid,
						int32 hypertable_id)
{
	Oid chunk_constraint_oid;

	ts_process_utility_set_expect_chunk_modification(true);
	chunk_constraint_oid = chunk_constraint_create_on_table(cc, chunk_oid);
	ts_process_utility_set_expect_chunk_modification(false);

	/*
	 * The table constraint might not have been created if this constraint
	 * corresponds to a dimension slice that covers the entire range of values
	 * in the particular dimension. In that case, there is no need to add a
	 * table constraint.
	 */
	if (!OidIsValid(chunk_constraint_oid))
		return InvalidOid;

	if (!is_dimension_constraint(cc))
	{
		Oid hypertable_constraint_oid =
			get_relation_constraint_oid(hypertable_oid,
										NameStr(cc->fd.hypertable_constraint_name),
										false);
		HeapTuple tuple = SearchSysCache1(CONSTROID, hypertable_constraint_oid);

		if (HeapTupleIsValid(tuple))
		{
			FormData_pg_constraint *constr = (FormData_pg_constraint *) GETSTRUCT(tuple);

			if (OidIsValid(constr->conindid) && constr->contype != CONSTRAINT_FOREIGN)
				ts_chunk_index_create_from_constraint(hypertable_id,
													  hypertable_constraint_oid,
													  chunk_id,
													  chunk_constraint_oid);

			ReleaseSysCache(tuple);
		}
	}

	return chunk_constraint_oid;
}