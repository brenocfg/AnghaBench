#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  name; scalar_t__ def; } ;
struct TYPE_13__ {int /*<<< orphan*/  typeName; } ;
struct TYPE_10__ {int /*<<< orphan*/  id; } ;
struct TYPE_12__ {TYPE_1__ fd; } ;
struct TYPE_11__ {int /*<<< orphan*/  space; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ Hypertable ;
typedef  TYPE_3__ Dimension ;
typedef  TYPE_4__ ColumnDef ;
typedef  TYPE_5__ AlterTableCmd ;

/* Variables and functions */
 int /*<<< orphan*/  DIMENSION_TYPE_ANY ; 
 int /*<<< orphan*/  TypenameGetTypid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_chunk_recreate_all_constraints_for_dimension (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_dimension_set_type (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* ts_hyperspace_get_dimension_by_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_process_utility_set_expect_chunk_modification (int) ; 
 int /*<<< orphan*/  typename_get_unqual_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process_alter_column_type_end(Hypertable *ht, AlterTableCmd *cmd)
{
	ColumnDef *coldef = (ColumnDef *) cmd->def;
	Oid new_type = TypenameGetTypid(typename_get_unqual_name(coldef->typeName));
	Dimension *dim = ts_hyperspace_get_dimension_by_name(ht->space, DIMENSION_TYPE_ANY, cmd->name);

	if (NULL == dim)
		return;

	ts_dimension_set_type(dim, new_type);
	ts_process_utility_set_expect_chunk_modification(true);
	ts_chunk_recreate_all_constraints_for_dimension(ht->space, dim->fd.id);
	ts_process_utility_set_expect_chunk_modification(false);
}