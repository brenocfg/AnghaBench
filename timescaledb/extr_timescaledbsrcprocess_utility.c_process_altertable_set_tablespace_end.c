#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int num_tablespaces; TYPE_3__* tablespaces; } ;
typedef  TYPE_4__ Tablespaces ;
struct TYPE_18__ {int /*<<< orphan*/  name; } ;
struct TYPE_13__ {int /*<<< orphan*/  id; } ;
struct TYPE_17__ {int /*<<< orphan*/  main_table_relid; TYPE_1__ fd; } ;
struct TYPE_14__ {int /*<<< orphan*/  tablespace_name; } ;
struct TYPE_15__ {TYPE_2__ fd; int /*<<< orphan*/  tablespace_oid; } ;
typedef  int /*<<< orphan*/  NameData ;
typedef  TYPE_5__ Hypertable ;
typedef  TYPE_6__ AlterTableCmd ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  foreach_chunk (TYPE_5__*,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  get_rel_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  namestrcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_altertable_chunk ; 
 int /*<<< orphan*/  ts_hypertable_has_tablespace (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_tablespace_attach_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ts_tablespace_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* ts_tablespace_scan (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process_altertable_set_tablespace_end(Hypertable *ht, AlterTableCmd *cmd)
{
	NameData tspc_name;
	Tablespaces *tspcs;

	namestrcpy(&tspc_name, cmd->name);

	tspcs = ts_tablespace_scan(ht->fd.id);

	if (tspcs->num_tablespaces > 1)
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
				 errmsg("cannot set new tablespace when multiple tablespaces are attached to "
						"hypertable \"%s\"",
						get_rel_name(ht->main_table_relid)),
				 errhint("Detach tablespaces before altering the hypertable.")));

	if (tspcs->num_tablespaces == 1)
	{
		Assert(ts_hypertable_has_tablespace(ht, tspcs->tablespaces[0].tablespace_oid));
		ts_tablespace_delete(ht->fd.id, NameStr(tspcs->tablespaces[0].fd.tablespace_name));
	}

	ts_tablespace_attach_internal(&tspc_name, ht->main_table_relid, true);
	foreach_chunk(ht, process_altertable_chunk, cmd);
}