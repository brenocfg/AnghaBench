#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  newowner; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Hypertable ;
typedef  TYPE_1__ AlterTableCmd ;

/* Variables and functions */
 int /*<<< orphan*/  ATExecChangeOwner (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  get_rolespec_oid (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
process_altertable_change_owner_chunk(Hypertable *ht, Oid chunk_relid, void *arg)
{
	AlterTableCmd *cmd = arg;
	Oid roleid = get_rolespec_oid(cmd->newowner, false);

	ATExecChangeOwner(chunk_relid, roleid, false, AccessExclusiveLock);
}