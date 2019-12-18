#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  schema_name; } ;
struct TYPE_7__ {TYPE_1__* tables; } ;
struct TYPE_6__ {scalar_t__ id; } ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  CatalogTable ;
typedef  TYPE_2__ Catalog ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_CATALOG_TABLE ; 
 unsigned int _MAX_CATALOG_TABLES ; 
 int /*<<< orphan*/  catalog_is_valid (TYPE_2__*) ; 
 int /*<<< orphan*/  catalog_table_name (unsigned int) ; 
 TYPE_3__* catalog_table_names ; 
 char* get_namespace_name (int /*<<< orphan*/ ) ; 
 char* get_rel_name (scalar_t__) ; 
 int /*<<< orphan*/  get_rel_namespace (scalar_t__) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static CatalogTable
catalog_get_table(Catalog *catalog, Oid relid)
{
	unsigned int i;

	if (!catalog_is_valid(catalog))
	{
		const char *schema_name = get_namespace_name(get_rel_namespace(relid));
		const char *relname = get_rel_name(relid);

		for (i = 0; i < _MAX_CATALOG_TABLES; i++)
			if (strcmp(catalog_table_names[i].schema_name, schema_name) == 0 &&
				strcmp(catalog_table_name(i), relname) == 0)
				return (CatalogTable) i;

		return INVALID_CATALOG_TABLE;
	}

	for (i = 0; i < _MAX_CATALOG_TABLES; i++)
		if (catalog->tables[i].id == relid)
			return (CatalogTable) i;

	return INVALID_CATALOG_TABLE;
}