#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  tuple; } ;
typedef  TYPE_1__ TupleInfo ;
struct TYPE_7__ {int /*<<< orphan*/  ht_oids; int /*<<< orphan*/ * table_name; int /*<<< orphan*/ * schema_name; } ;
struct TYPE_6__ {int /*<<< orphan*/  table_name; int /*<<< orphan*/  schema_name; } ;
typedef  int /*<<< orphan*/  ScanTupleResult ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ FormData_hypertable ;
typedef  TYPE_3__ AccumHypertable ;

/* Variables and functions */
 scalar_t__ DatumGetBool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NameGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCAN_CONTINUE ; 
 int /*<<< orphan*/  get_namespace_oid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_relname_relid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lappend_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nameeq ; 

__attribute__((used)) static ScanTupleResult
hypertable_tuple_match_name(TupleInfo *ti, void *data)
{
	Oid relid;
	FormData_hypertable *form = (FormData_hypertable *) GETSTRUCT(ti->tuple);
	AccumHypertable *accum = data;
	Oid schema_oid = get_namespace_oid(NameStr(form->schema_name), true);

	if (!OidIsValid(schema_oid))
		return SCAN_CONTINUE;

	relid = get_relname_relid(NameStr(form->table_name), schema_oid);
	if (!OidIsValid(relid))
		return SCAN_CONTINUE;

	if ((accum->schema_name == NULL ||
		 DatumGetBool(DirectFunctionCall2(nameeq,
										  NameGetDatum(accum->schema_name),
										  NameGetDatum(&form->schema_name)))) &&
		(accum->table_name == NULL ||
		 DatumGetBool(DirectFunctionCall2(nameeq,
										  NameGetDatum(accum->table_name),
										  NameGetDatum(&form->table_name)))))
		accum->ht_oids = lappend_oid(accum->ht_oids, relid);

	return SCAN_CONTINUE;
}