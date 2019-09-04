#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int nargs; struct TYPE_3__* next; int /*<<< orphan*/  oid; int /*<<< orphan*/  args; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__* FuncCandidateList ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 TYPE_1__* FuncnameGetCandidates (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char*,char*,int) ; 
 int /*<<< orphan*/  list_make2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeString (char*) ; 
 scalar_t__ ts_function_types_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

Oid
get_function_oid(char *name, char *schema_name, int nargs, Oid arg_types[])
{
	FuncCandidateList func_candidates;

	func_candidates = FuncnameGetCandidates(list_make2(makeString(schema_name), makeString(name)),
											nargs,
											NIL,
											false,
											false,
											false);
	while (func_candidates != NULL)
	{
		if (func_candidates->nargs == nargs &&
			ts_function_types_equal(func_candidates->args, arg_types, nargs))
			return func_candidates->oid;
		func_candidates = func_candidates->next;
	}
	elog(ERROR, "failed to find function %s in schema %s with %d args", name, schema_name, nargs);
}