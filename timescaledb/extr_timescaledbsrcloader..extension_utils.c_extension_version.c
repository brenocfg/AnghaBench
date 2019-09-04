#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_extension_extname ; 
 int /*<<< orphan*/  Anum_pg_extension_extversion ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CStringGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EXTENSION_NAME ; 
 int /*<<< orphan*/  ExtensionNameIndexId ; 
 int /*<<< orphan*/  ExtensionRelationId ; 
 int /*<<< orphan*/  F_NAMEEQ ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TextDatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_getattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  namein ; 
 char* pstrdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_getnext (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
extension_version(void)
{
	Datum result;
	Relation rel;
	SysScanDesc scandesc;
	HeapTuple tuple;
	ScanKeyData entry[1];
	bool is_null = true;
	char *sql_version = NULL;

	rel = heap_open(ExtensionRelationId, AccessShareLock);

	ScanKeyInit(&entry[0],
				Anum_pg_extension_extname,
				BTEqualStrategyNumber,
				F_NAMEEQ,
				DirectFunctionCall1(namein, CStringGetDatum(EXTENSION_NAME)));

	scandesc = systable_beginscan(rel, ExtensionNameIndexId, true, NULL, 1, entry);

	tuple = systable_getnext(scandesc);

	/* We assume that there can be at most one matching tuple */
	if (HeapTupleIsValid(tuple))
	{
		result = heap_getattr(tuple, Anum_pg_extension_extversion, RelationGetDescr(rel), &is_null);

		if (!is_null)
		{
			sql_version = pstrdup(TextDatumGetCString(result));
		}
	}

	systable_endscan(scandesc);
	heap_close(rel, AccessShareLock);

	if (sql_version == NULL)
	{
		elog(ERROR, "extension not found while getting version");
	}
	return sql_version;
}