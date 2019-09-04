#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int natts; } ;
struct TYPE_7__ {int /*<<< orphan*/  attname; } ;
struct TYPE_6__ {TYPE_5__* rd_att; } ;
typedef  TYPE_1__* Relation ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_2__* Form_pg_attribute ;

/* Variables and functions */
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 TYPE_2__* TupleDescAttr (TYPE_5__*,int) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeString (int /*<<< orphan*/ ) ; 

__attribute__((used)) static List *
build_indexcolumn_list(Relation idxrel)
{
	List *columns = NIL;
	int i;

	for (i = 0; i < idxrel->rd_att->natts; i++)
	{
		Form_pg_attribute idxattr = TupleDescAttr(idxrel->rd_att, i);

		columns = lappend(columns, makeString(NameStr(idxattr->attname)));
	}

	return columns;
}