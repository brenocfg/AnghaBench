#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  func_oid; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__ FuncStrategy ;

/* Variables and functions */
 int /*<<< orphan*/  LookupFuncName (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * list_make2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeString (char*) ; 
 char* ts_extension_schema_name () ; 

__attribute__((used)) static FuncStrategy *
initialize_func_strategy(FuncStrategy *func_strategy, char *name, int nargs, Oid arg_types[])
{
	List *l = list_make2(makeString(ts_extension_schema_name()), makeString(name));
	func_strategy->func_oid = LookupFuncName(l, nargs, arg_types, false);
	return func_strategy;
}