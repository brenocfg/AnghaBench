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
struct TYPE_5__ {int /*<<< orphan*/  tuple; } ;
typedef  TYPE_1__ TupleInfo ;
typedef  int /*<<< orphan*/  Tablespaces ;
struct TYPE_6__ {int /*<<< orphan*/  tablespace_name; } ;
typedef  int /*<<< orphan*/  ScanTupleResult ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ FormData_tablespace ;

/* Variables and functions */
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCAN_CONTINUE ; 
 int /*<<< orphan*/  get_tablespace_oid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ts_tablespaces_add (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ScanTupleResult
tablespace_tuple_found(TupleInfo *ti, void *data)
{
	Tablespaces *tspcs = data;
	FormData_tablespace *form = (FormData_tablespace *) GETSTRUCT(ti->tuple);
	Oid tspcoid = get_tablespace_oid(NameStr(form->tablespace_name), true);

	if (NULL != tspcs)
		ts_tablespaces_add(tspcs, form, tspcoid);

	return SCAN_CONTINUE;
}