#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  id; } ;
struct TYPE_13__ {TYPE_2__ fd; } ;
struct TYPE_12__ {int set_not_null; int skip; int type; int /*<<< orphan*/ * colname; int /*<<< orphan*/  dimension_id; int /*<<< orphan*/  if_not_exists; TYPE_1__* ht; int /*<<< orphan*/  coltype; int /*<<< orphan*/  table_relid; int /*<<< orphan*/  interval_type; scalar_t__ num_slices_is_set; } ;
struct TYPE_10__ {int /*<<< orphan*/  space; } ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_3__ DimensionInfo ;
typedef  TYPE_4__ Dimension ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ATTNAME ; 
 int /*<<< orphan*/  Anum_pg_attribute_attnotnull ; 
 int /*<<< orphan*/  Anum_pg_attribute_atttypid ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DIMENSION_INFO_IS_SET (TYPE_3__*) ; 
#define  DIMENSION_TYPE_ANY 130 
#define  DIMENSION_TYPE_CLOSED 129 
#define  DIMENSION_TYPE_OPEN 128 
 int /*<<< orphan*/  DatumGetBool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetObjectId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERRCODE_TS_DUPLICATE_DIMENSION ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_COLUMN ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NOTICE ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCacheAttName (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysCacheGetAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dimension_info_validate_closed (TYPE_3__*) ; 
 int /*<<< orphan*/  dimension_info_validate_open (TYPE_3__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 TYPE_4__* ts_hyperspace_get_dimension_by_name (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void
ts_dimension_info_validate(DimensionInfo *info)
{
	Dimension *dim;
	HeapTuple tuple;
	Datum datum;
	bool isnull = false;

	if (!DIMENSION_INFO_IS_SET(info))
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE), errmsg("invalid dimension info")));

	if (info->num_slices_is_set && OidIsValid(info->interval_type))
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("cannot specify both the number of partitions and an interval")));

	/* Check that the column exists and get its NOT NULL status */
	tuple = SearchSysCacheAttName(info->table_relid, NameStr(*info->colname));

	if (!HeapTupleIsValid(tuple))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_COLUMN),
				 errmsg("column \"%s\" does not exist", NameStr(*info->colname))));

	datum = SysCacheGetAttr(ATTNAME, tuple, Anum_pg_attribute_atttypid, &isnull);
	Assert(!isnull);

	info->coltype = DatumGetObjectId(datum);

	datum = SysCacheGetAttr(ATTNAME, tuple, Anum_pg_attribute_attnotnull, &isnull);
	Assert(!isnull);

	info->set_not_null = !DatumGetBool(datum);

	ReleaseSysCache(tuple);

	if (NULL != info->ht)
	{
		/* Check if the dimension already exists */
		dim = ts_hyperspace_get_dimension_by_name(info->ht->space,
												  DIMENSION_TYPE_ANY,
												  NameStr(*info->colname));

		if (NULL != dim)
		{
			if (!info->if_not_exists)
				ereport(ERROR,
						(errcode(ERRCODE_TS_DUPLICATE_DIMENSION),
						 errmsg("column \"%s\" is already a dimension", NameStr(*info->colname))));

			info->dimension_id = dim->fd.id;
			info->skip = true;

			ereport(NOTICE,
					(errmsg("column \"%s\" is already a dimension, skipping",
							NameStr(*info->colname))));
			return;
		}
	}

	switch (info->type)
	{
		case DIMENSION_TYPE_CLOSED:
			dimension_info_validate_closed(info);
			break;
		case DIMENSION_TYPE_OPEN:
			dimension_info_validate_open(info);
			break;
		case DIMENSION_TYPE_ANY:
			elog(ERROR, "invalid dimension type in configuration");
			break;
	}
}