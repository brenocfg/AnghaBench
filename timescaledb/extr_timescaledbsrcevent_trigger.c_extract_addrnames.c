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
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  TEXTOID ; 
 int /*<<< orphan*/  TextDatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deconstruct_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,char,int /*<<< orphan*/ **,int**,int*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static List *
extract_addrnames(ArrayType *arr)
{
	Datum *elems;
	bool *nulls;
	int nelems;
	List *list = NIL;
	int i;

	deconstruct_array(arr, TEXTOID, -1, false, 'i', &elems, &nulls, &nelems);

	for (i = 0; i < nelems; i++)
	{
		if (nulls[i])
			elog(ERROR, "unexpected NULL in name list");

		/* TextDatumGetCString heap allocates the string */
		list = lappend(list, TextDatumGetCString(elems[i]));
	}

	return list;
}