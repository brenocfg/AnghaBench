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
typedef  int /*<<< orphan*/  finalfnargtypes ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  ANYELEMENTOID ; 
 int /*<<< orphan*/  BYTEAOID ; 
 int /*<<< orphan*/  FINALFN ; 
 int /*<<< orphan*/  INTERNAL_SCHEMA_NAME ; 
 int /*<<< orphan*/  LookupFuncName (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  NAMEOID ; 
 int /*<<< orphan*/  TEXTOID ; 
 int /*<<< orphan*/  get_array_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_make2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeString (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Oid
get_finalizefnoid()
{
	Oid finalfnoid;
	Oid finalfnargtypes[] = { TEXTOID,  NAMEOID,	  NAMEOID, get_array_type(NAMEOID),
							  BYTEAOID, ANYELEMENTOID };
	List *funcname = list_make2(makeString(INTERNAL_SCHEMA_NAME), makeString(FINALFN));
	int nargs = sizeof(finalfnargtypes) / sizeof(finalfnargtypes[0]);
	finalfnoid = LookupFuncName(funcname, nargs, finalfnargtypes, false);
	return finalfnoid;
}