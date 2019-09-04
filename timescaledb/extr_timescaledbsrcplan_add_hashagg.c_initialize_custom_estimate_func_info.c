#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ nargs; int /*<<< orphan*/  function_oid; int /*<<< orphan*/  function_name; int /*<<< orphan*/  arg_types; scalar_t__ extension_function; } ;
struct TYPE_11__ {TYPE_4__* entry; } ;
struct TYPE_10__ {scalar_t__ nargs; int /*<<< orphan*/  oid; struct TYPE_10__* next; int /*<<< orphan*/  args; } ;
struct TYPE_9__ {int keysize; int entrysize; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ HASHCTL ;
typedef  TYPE_2__* FuncCandidateList ;
typedef  TYPE_3__ CustomEstimateForFunctionInfoHashEntry ;
typedef  TYPE_4__ CustomEstimateForFunctionInfo ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 TYPE_2__* FuncnameGetCandidates (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int,int) ; 
 int HASH_BLOBS ; 
 int HASH_ELEM ; 
 int /*<<< orphan*/  HASH_ENTER ; 
 int /*<<< orphan*/  NIL ; 
 int _MAX_HASHAGG_FUNCTIONS ; 
 int /*<<< orphan*/  custom_estimate_func_hash ; 
 TYPE_4__* custom_estimate_func_info ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hash_create (char*,int,TYPE_1__*,int) ; 
 TYPE_3__* hash_search (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  list_make1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_make2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_extension_schema_name () ; 
 int /*<<< orphan*/  ts_function_types_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
initialize_custom_estimate_func_info()
{
	int i = 0;

	HASHCTL hashctl = { .keysize = sizeof(Oid),
						.entrysize = sizeof(CustomEstimateForFunctionInfoHashEntry) };

	custom_estimate_func_hash = hash_create("custom_estimate_func_hash",
											_MAX_HASHAGG_FUNCTIONS,
											&hashctl,
											HASH_ELEM | HASH_BLOBS);

	for (i = 0; i < _MAX_HASHAGG_FUNCTIONS; i++)
	{
		CustomEstimateForFunctionInfo def = custom_estimate_func_info[i];
		CustomEstimateForFunctionInfoHashEntry *hash_entry;
		bool function_found = false;
		bool hash_found;
		FuncCandidateList funclist;

		if (def.extension_function)
			funclist = FuncnameGetCandidates(list_make2(makeString(ts_extension_schema_name()),
														makeString(def.function_name)),
											 def.nargs,
											 NIL,
											 false,
											 false,
											 false);
		else
			funclist = FuncnameGetCandidates(list_make1(makeString(def.function_name)),
											 def.nargs,
											 NIL,
											 false,
											 false,
											 false);

		/* check types */
		while (!function_found && funclist != NULL)
		{
			if (funclist->nargs != def.nargs ||
				!ts_function_types_equal(funclist->args, def.arg_types, def.nargs))
				funclist = funclist->next;
			else
				function_found = true;
		}

		if (!function_found)
			elog(ERROR,
				 "cache lookup failed for function \"%s\" with %d args",
				 def.function_name,
				 def.nargs);

		custom_estimate_func_info[i].function_oid = funclist->oid;

		hash_entry = hash_search(custom_estimate_func_hash,
								 &(custom_estimate_func_info[i].function_oid),
								 HASH_ENTER,
								 &hash_found);
		Assert(!hash_found);
		hash_entry->entry = &custom_estimate_func_info[i];
	}
}