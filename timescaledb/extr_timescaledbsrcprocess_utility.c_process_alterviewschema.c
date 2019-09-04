#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ objectType; int /*<<< orphan*/  newschema; int /*<<< orphan*/ * relation; } ;
struct TYPE_4__ {scalar_t__ parsetree; } ;
typedef  TYPE_1__ ProcessUtilityArgs ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ AlterObjectSchemaStmt ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  NoLock ; 
 scalar_t__ OBJECT_VIEW ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RangeVarGetRelid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 char* get_namespace_name (int /*<<< orphan*/ ) ; 
 char* get_rel_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rel_namespace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_continuous_agg_rename_view (char*,char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
process_alterviewschema(ProcessUtilityArgs *args)
{
	AlterObjectSchemaStmt *alterstmt = (AlterObjectSchemaStmt *) args->parsetree;
	Oid relid;
	char *schema;
	char *name;

	Assert(alterstmt->objectType == OBJECT_VIEW);

	if (NULL == alterstmt->relation)
		return;

	relid = RangeVarGetRelid(alterstmt->relation, NoLock, true);
	if (!OidIsValid(relid))
		return;

	schema = get_namespace_name(get_rel_namespace(relid));
	name = get_rel_name(relid);

	ts_continuous_agg_rename_view(schema, name, alterstmt->newschema, name);
}