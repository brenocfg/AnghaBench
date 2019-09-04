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
struct TYPE_7__ {int /*<<< orphan*/  desc; int /*<<< orphan*/  tuple; } ;
typedef  TYPE_1__ TupleInfo ;
struct TYPE_9__ {int /*<<< orphan*/  table_id; } ;
struct TYPE_8__ {int /*<<< orphan*/  objectId; int /*<<< orphan*/  classId; } ;
typedef  TYPE_2__ ObjectAddress ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_3__ Chunk ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_chunk_constraint_chunk_id ; 
 int /*<<< orphan*/  Anum_chunk_constraint_constraint_name ; 
 int /*<<< orphan*/  ConstraintRelationId ; 
 int /*<<< orphan*/  DROP_RESTRICT ; 
 int /*<<< orphan*/  DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * DatumGetName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_relation_constraint_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  heap_getattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  performDeletion (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* ts_chunk_get_by_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
chunk_constraint_drop_constraint(TupleInfo *ti)
{
	bool isnull;
	Datum constrname =
		heap_getattr(ti->tuple, Anum_chunk_constraint_constraint_name, ti->desc, &isnull);
	int32 chunk_id =
		DatumGetInt32(heap_getattr(ti->tuple, Anum_chunk_constraint_chunk_id, ti->desc, &isnull));
	Chunk *chunk = ts_chunk_get_by_id(chunk_id, 0, true);
	ObjectAddress constrobj = {
		.classId = ConstraintRelationId,
		.objectId =
			get_relation_constraint_oid(chunk->table_id, NameStr(*DatumGetName(constrname)), true),
	};

	if (OidIsValid(constrobj.objectId))
		performDeletion(&constrobj, DROP_RESTRICT, 0);
}