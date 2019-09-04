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
struct TYPE_3__ {int /*<<< orphan*/  newname; } ;
typedef  TYPE_1__ RenameStmt ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 char* get_namespace_name (int /*<<< orphan*/ ) ; 
 char* get_rel_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rel_namespace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_continuous_agg_rename_view (char*,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process_rename_view(Oid relid, RenameStmt *stmt)
{
	char *schema = get_namespace_name(get_rel_namespace(relid));
	char *name = get_rel_name(relid);
	ts_continuous_agg_rename_view(schema, name, schema, stmt->newname);
}