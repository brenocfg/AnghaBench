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
struct TYPE_7__ {scalar_t__ type; int /*<<< orphan*/  interval; int /*<<< orphan*/  partitioning_func; int /*<<< orphan*/  num_slices; int /*<<< orphan*/  coltype; int /*<<< orphan*/ * colname; TYPE_2__* ht; int /*<<< orphan*/  dimension_id; int /*<<< orphan*/  table_relid; scalar_t__ set_not_null; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct TYPE_6__ {TYPE_1__ fd; } ;
typedef  TYPE_3__ DimensionInfo ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 scalar_t__ DIMENSION_TYPE_OPEN ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dimension_add_not_null_on_column (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dimension_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ts_dimension_add_from_info(DimensionInfo *info)
{
	if (info->set_not_null && info->type == DIMENSION_TYPE_OPEN)
		dimension_add_not_null_on_column(info->table_relid, NameStr(*info->colname));

	Assert(info->ht != NULL);

	info->dimension_id = dimension_insert(info->ht->fd.id,
										  info->colname,
										  info->coltype,
										  info->num_slices,
										  info->partitioning_func,
										  info->interval);
}