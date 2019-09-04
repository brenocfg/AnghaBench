#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  partial_grouplist; int /*<<< orphan*/  partial_seltlist; } ;
struct TYPE_8__ {int /*<<< orphan*/ * sortClause; int /*<<< orphan*/ * havingQual; int /*<<< orphan*/  groupClause; int /*<<< orphan*/  targetList; void* jointree; void* rtable; } ;
typedef  TYPE_1__ Query ;
typedef  TYPE_2__ MatTableColumnInfo ;

/* Variables and functions */
 int /*<<< orphan*/  CAGG_MAKEQUERY (TYPE_1__*,TYPE_1__*) ; 
 void* copyObject (void*) ; 

__attribute__((used)) static Query *
mattablecolumninfo_get_partial_select_query(MatTableColumnInfo *mattblinfo, Query *userview_query)
{
	Query *partial_selquery;
	CAGG_MAKEQUERY(partial_selquery, userview_query);
	partial_selquery->rtable = copyObject(userview_query->rtable);
	partial_selquery->jointree = copyObject(userview_query->jointree);
	partial_selquery->targetList = mattblinfo->partial_seltlist;
	partial_selquery->groupClause = mattblinfo->partial_grouplist;
	partial_selquery->havingQual = NULL;
	partial_selquery->sortClause = NULL;
	return partial_selquery;
}