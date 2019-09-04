#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ castmethod; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_cast ;

/* Variables and functions */
 int /*<<< orphan*/  CASTSOURCETARGET ; 
 scalar_t__ COERCION_METHOD_BINARY ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT8OID ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
ts_type_is_int8_binary_compatible(Oid sourcetype)
{
	HeapTuple tuple;
	Form_pg_cast castForm;
	bool result;

	tuple =
		SearchSysCache2(CASTSOURCETARGET, ObjectIdGetDatum(sourcetype), ObjectIdGetDatum(INT8OID));
	if (!HeapTupleIsValid(tuple))
		return false; /* no cast */
	castForm = (Form_pg_cast) GETSTRUCT(tuple);
	result = castForm->castmethod == COERCION_METHOD_BINARY;
	ReleaseSysCache(tuple);
	return result;
}