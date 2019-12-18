#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  objectId; int /*<<< orphan*/  classId; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ ObjectAddress ;

/* Variables and functions */
 int /*<<< orphan*/  CHUNK_DML_BLOCKER_NAME ; 
 int /*<<< orphan*/  DROP_RESTRICT ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TriggerRelationId ; 
 int /*<<< orphan*/  get_trigger_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  performDeletion (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
chunk_dml_trigger_drop(Oid relid)
{
	if (OidIsValid(relid))
	{
		ObjectAddress objaddr = {
			.classId = TriggerRelationId,
			.objectId = get_trigger_oid(relid, CHUNK_DML_BLOCKER_NAME, true),
		};
		if (OidIsValid(objaddr.objectId))
			performDeletion(&objaddr, DROP_RESTRICT, 0);
	}
}