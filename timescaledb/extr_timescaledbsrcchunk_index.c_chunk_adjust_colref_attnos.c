#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int natts; } ;
struct TYPE_12__ {int /*<<< orphan*/  attname; } ;
struct TYPE_11__ {scalar_t__* ii_IndexAttrNumbers; } ;
struct TYPE_10__ {TYPE_7__* rd_att; } ;
typedef  TYPE_1__* Relation ;
typedef  TYPE_2__ IndexInfo ;
typedef  TYPE_3__ FormData_pg_attribute ;
typedef  scalar_t__ AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidAttrNumber ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 TYPE_3__* TupleDescAttr (TYPE_7__*,int) ; 
 scalar_t__ attno_find_by_attname (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
chunk_adjust_colref_attnos(IndexInfo *ii, Relation idxrel, Relation chunkrel)
{
	int i;

	for (i = 0; i < idxrel->rd_att->natts; i++)
	{
		FormData_pg_attribute *idxattr = TupleDescAttr(idxrel->rd_att, i);
		AttrNumber attno = attno_find_by_attname(chunkrel->rd_att, &idxattr->attname);

		if (attno == InvalidAttrNumber)
			elog(ERROR, "index attribute %s not found in chunk", NameStr(idxattr->attname));
#if PG96 || PG10
		ii->ii_KeyAttrNumbers[i] = attno;
#else
		ii->ii_IndexAttrNumbers[i] = attno;
#endif
	}
}