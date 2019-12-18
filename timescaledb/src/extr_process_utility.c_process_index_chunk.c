#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  id; } ;
struct TYPE_16__ {TYPE_4__ fd; } ;
struct TYPE_11__ {int /*<<< orphan*/  objectId; } ;
struct TYPE_15__ {TYPE_2__ obj; int /*<<< orphan*/  stmt; } ;
struct TYPE_10__ {int /*<<< orphan*/  id; } ;
struct TYPE_14__ {TYPE_1__ fd; TYPE_3__* space; } ;
struct TYPE_12__ {int /*<<< orphan*/  num_dimensions; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  IndexStmt ;
typedef  TYPE_5__ Hypertable ;
typedef  TYPE_6__ CreateIndexInfo ;
typedef  TYPE_7__ Chunk ;

/* Variables and functions */
 int /*<<< orphan*/ * transformIndexStmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_7__* ts_chunk_get_by_relid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ts_chunk_index_create_from_stmt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process_index_chunk(Hypertable *ht, Oid chunk_relid, void *arg)
{
	CreateIndexInfo *info = (CreateIndexInfo *) arg;
	IndexStmt *stmt = transformIndexStmt(chunk_relid, info->stmt, NULL);
	Chunk *chunk = ts_chunk_get_by_relid(chunk_relid, ht->space->num_dimensions, true);

	ts_chunk_index_create_from_stmt(stmt, chunk->fd.id, chunk_relid, ht->fd.id, info->obj.objectId);
}