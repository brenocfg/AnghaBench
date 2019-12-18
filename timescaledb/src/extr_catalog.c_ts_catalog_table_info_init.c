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
struct TYPE_7__ {int /*<<< orphan*/  schema_name; int /*<<< orphan*/  table_name; } ;
typedef  TYPE_1__ TableInfoDef ;
struct TYPE_8__ {scalar_t__ length; int /*<<< orphan*/ * names; } ;
typedef  TYPE_2__ TableIndexDef ;
struct TYPE_9__ {scalar_t__ serial_relid; int /*<<< orphan*/  schema_name; int /*<<< orphan*/  name; scalar_t__* index_ids; scalar_t__ id; } ;
typedef  scalar_t__ Size ;
typedef  int /*<<< orphan*/  RangeVar ;
typedef  scalar_t__ Oid ;
typedef  TYPE_3__ CatalogTableInfo ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  NoLock ; 
 scalar_t__ RangeVarGetRelid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ _MAX_TABLE_INDEXES ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ get_namespace_oid (int /*<<< orphan*/ ,int) ; 
 scalar_t__ get_relname_relid (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * makeRangeVarFromNameList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stringToQualifiedNameList (char const*) ; 

void
ts_catalog_table_info_init(CatalogTableInfo *tables_info, int max_tables,
						   const TableInfoDef *table_ary, const TableIndexDef *index_ary,
						   const char **serial_id_ary)
{
	int i;

	for (i = 0; i < max_tables; i++)
	{
		Oid schema_oid;
		Oid id;
		const char *sequence_name;
		Size number_indexes, j;

		schema_oid = get_namespace_oid(table_ary[i].schema_name, false);
		id = get_relname_relid(table_ary[i].table_name, schema_oid);

		if (id == InvalidOid)
			elog(ERROR,
				 "OID lookup failed for table \"%s.%s\"",
				 table_ary[i].schema_name,
				 table_ary[i].table_name);

		tables_info[i].id = id;

		number_indexes = index_ary[i].length;
		Assert(number_indexes <= _MAX_TABLE_INDEXES);

		for (j = 0; j < number_indexes; j++)
		{
			id = get_relname_relid(index_ary[i].names[j], schema_oid);

			if (id == InvalidOid)
				elog(ERROR, "OID lookup failed for table index \"%s\"", index_ary[i].names[j]);

			tables_info[i].index_ids[j] = id;
		}

		tables_info[i].name = table_ary[i].table_name;
		tables_info[i].schema_name = table_ary[i].schema_name;
		sequence_name = serial_id_ary[i];

		if (NULL != sequence_name)
		{
			RangeVar *sequence;

			sequence = makeRangeVarFromNameList(stringToQualifiedNameList(sequence_name));
			tables_info[i].serial_relid = RangeVarGetRelid(sequence, NoLock, false);
		}
		else
			tables_info[i].serial_relid = InvalidOid;
	}
}