#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  tuple; int /*<<< orphan*/  scanrel; } ;
typedef  TYPE_1__ TupleInfo ;
struct TYPE_11__ {scalar_t__ drop_index; } ;
struct TYPE_10__ {int /*<<< orphan*/  index_name; } ;
struct TYPE_9__ {int /*<<< orphan*/  objectId; int /*<<< orphan*/  classId; } ;
typedef  int /*<<< orphan*/  ScanTupleResult ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ ObjectAddress ;
typedef  TYPE_3__ FormData_chunk_index ;
typedef  TYPE_4__ ChunkIndexDeleteData ;

/* Variables and functions */
 int /*<<< orphan*/  DROP_RESTRICT ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationRelationId ; 
 int /*<<< orphan*/  SCAN_CONTINUE ; 
 int /*<<< orphan*/  chunk_index_get_schemaid (TYPE_3__*,int) ; 
 int /*<<< orphan*/  get_relname_relid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  performDeletion (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_catalog_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ScanTupleResult
chunk_index_tuple_delete(TupleInfo *ti, void *data)
{
	FormData_chunk_index *chunk_index = (FormData_chunk_index *) GETSTRUCT(ti->tuple);
	Oid schemaid = chunk_index_get_schemaid(chunk_index, true);
	ChunkIndexDeleteData *cid = data;

	ts_catalog_delete(ti->scanrel, ti->tuple);

	if (cid->drop_index)
	{
		ObjectAddress idxobj = {
			.classId = RelationRelationId,
			.objectId = get_relname_relid(NameStr(chunk_index->index_name), schemaid),
		};

		if (OidIsValid(idxobj.objectId))
			performDeletion(&idxobj, DROP_RESTRICT, 0);
	}

	return SCAN_CONTINUE;
}