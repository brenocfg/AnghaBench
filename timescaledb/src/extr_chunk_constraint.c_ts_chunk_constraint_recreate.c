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
struct TYPE_7__ {int /*<<< orphan*/  constraint_name; } ;
struct TYPE_9__ {TYPE_1__ fd; } ;
struct TYPE_8__ {int /*<<< orphan*/  objectId; int /*<<< orphan*/  classId; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ ObjectAddress ;
typedef  TYPE_3__ ChunkConstraint ;

/* Variables and functions */
 int /*<<< orphan*/  ConstraintRelationId ; 
 int /*<<< orphan*/  DROP_RESTRICT ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chunk_constraint_create_on_table (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_relation_constraint_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  performDeletion (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ts_chunk_constraint_recreate(ChunkConstraint *cc, Oid chunk_oid)
{
	ObjectAddress constrobj = {
		.classId = ConstraintRelationId,
		.objectId = get_relation_constraint_oid(chunk_oid, NameStr(cc->fd.constraint_name), false),
	};

	performDeletion(&constrobj, DROP_RESTRICT, 0);
	chunk_constraint_create_on_table(cc, chunk_oid);
}