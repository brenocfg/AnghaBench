#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* TupleDesc ;
struct TYPE_7__ {int /*<<< orphan*/  attnum; int /*<<< orphan*/  attname; } ;
struct TYPE_6__ {int natts; } ;
typedef  int /*<<< orphan*/ * Name ;
typedef  TYPE_2__ FormData_pg_attribute ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidAttrNumber ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 TYPE_2__* TupleDescAttr (TYPE_1__*,int) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

AttrNumber
attno_find_by_attname(TupleDesc tupdesc, Name attname)
{
	int i;

	if (NULL == attname)
		return InvalidAttrNumber;

	for (i = 0; i < tupdesc->natts; i++)
	{
		FormData_pg_attribute *attr = TupleDescAttr(tupdesc, i);

		if (strncmp(NameStr(attr->attname), NameStr(*attname), NAMEDATALEN) == 0)
			return attr->attnum;
	}
	return InvalidAttrNumber;
}