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
typedef  int /*<<< orphan*/  regproc ;
typedef  int /*<<< orphan*/  int64 ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Name ;
typedef  int /*<<< orphan*/  DimensionInfo ;

/* Variables and functions */
 int /*<<< orphan*/  INT8OID ; 
 int /*<<< orphan*/  Int64GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ts_dimension_info_create_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline DimensionInfo *
ts_dimension_info_create_open_interval_usec(Oid table_relid, Name column_name, int64 interval_usec,
											regproc partitioning_func)
{
	return ts_dimension_info_create_open(table_relid,
										 column_name,
										 Int64GetDatum(interval_usec),
										 INT8OID,
										 partitioning_func);
}