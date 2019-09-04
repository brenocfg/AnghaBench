#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  id; int /*<<< orphan*/  column_type; int /*<<< orphan*/  column_name; } ;
struct TYPE_6__ {TYPE_1__ fd; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ Dimension ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_TABLE_DEFINITION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  IS_VALID_OPEN_DIM_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int dimension_scan_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dimension_tuple_update ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_type_be (int /*<<< orphan*/ ) ; 

int
ts_dimension_set_type(Dimension *dim, Oid newtype)
{
	if (!IS_VALID_OPEN_DIM_TYPE(newtype))
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_TABLE_DEFINITION),
				 errmsg("cannot change data type of hypertable column \"%s\" from %s to %s",
						NameStr(dim->fd.column_name),
						format_type_be(dim->fd.column_type),
						format_type_be(newtype)),
				 errdetail("time dimension of hypertable can only have types: TIMESTAMP, "
						   "TIMESTAMPTZ, and DATE")));

	dim->fd.column_type = newtype;

	return dimension_scan_update(dim->fd.id, dimension_tuple_update, dim, RowExclusiveLock);
}