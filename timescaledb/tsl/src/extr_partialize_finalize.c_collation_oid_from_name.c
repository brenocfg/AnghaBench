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
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  get_collation_oid (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_make1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeString (char*) ; 

__attribute__((used)) static Oid
collation_oid_from_name(char *schema_name, char *collation_name)
{
	List *namel = NIL;
	if (NULL == collation_name)
		return InvalidOid;
	if (NULL != schema_name)
		namel = list_make1(makeString(schema_name));
	namel = lappend(namel, makeString(collation_name));
	return get_collation_oid(namel, false);
}