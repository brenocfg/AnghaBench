#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  subtype; int /*<<< orphan*/ * name; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Hypertable ;
typedef  TYPE_1__ AlterTableCmd ;

/* Variables and functions */
 int /*<<< orphan*/  AT_ValidateConstraint ; 
 int /*<<< orphan*/  AlterTableInternal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* copyObject (TYPE_1__*) ; 
 int /*<<< orphan*/  list_make1 (TYPE_1__*) ; 
 int /*<<< orphan*/ * ts_chunk_constraint_get_name_from_hypertable_constraint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
validate_hypertable_constraint(Hypertable *ht, Oid chunk_relid, void *arg)
{
	AlterTableCmd *cmd = (AlterTableCmd *) arg;
	AlterTableCmd *chunk_cmd = copyObject(cmd);

	chunk_cmd->name =
		ts_chunk_constraint_get_name_from_hypertable_constraint(chunk_relid, cmd->name);

	if (chunk_cmd->name == NULL)
		return;

	/* do not pass down the VALIDATE RECURSE subtype */
	chunk_cmd->subtype = AT_ValidateConstraint;
	AlterTableInternal(chunk_relid, list_make1(chunk_cmd), false);
}