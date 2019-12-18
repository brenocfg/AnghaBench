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
struct TYPE_3__ {char* name; int missing_ok; int /*<<< orphan*/  subtype; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ AlterTableCmd ;

/* Variables and functions */
 int /*<<< orphan*/  AT_SetNotNull ; 
 int /*<<< orphan*/  AlterTableInternal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NOTICE ; 
 int /*<<< orphan*/  T_AlterTableCmd ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 int /*<<< orphan*/  list_make1 (TYPE_1__*) ; 

__attribute__((used)) static void
dimension_add_not_null_on_column(Oid table_relid, char *colname)
{
	AlterTableCmd cmd = {
		.type = T_AlterTableCmd,
		.subtype = AT_SetNotNull,
		.name = colname,
		.missing_ok = false,
	};

	ereport(NOTICE,
			(errmsg("adding not-null constraint to column \"%s\"", colname),
			 errdetail("Time dimensions cannot have NULL values")));

	AlterTableInternal(table_relid, list_make1(&cmd), false);
}