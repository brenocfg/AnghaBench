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
struct TYPE_5__ {int /*<<< orphan*/  behavior; } ;
struct TYPE_4__ {int /*<<< orphan*/  objectId; int /*<<< orphan*/  classId; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ ObjectAddress ;
typedef  int /*<<< orphan*/  Hypertable ;
typedef  TYPE_2__ DropStmt ;

/* Variables and functions */
 int /*<<< orphan*/  RelationRelationId ; 
 int /*<<< orphan*/  performDeletion (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process_drop_table_chunk(Hypertable *ht, Oid chunk_relid, void *arg)
{
	DropStmt *stmt = arg;
	ObjectAddress objaddr = {
		.classId = RelationRelationId,
		.objectId = chunk_relid,
	};

	performDeletion(&objaddr, stmt->behavior, 0);
}