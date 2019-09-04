#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* caches; } ;
struct TYPE_5__ {int /*<<< orphan*/  inval_proxy_id; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ Catalog ;
typedef  size_t CacheType ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_SCHEMA_NAME ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  IsTransactionState () ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cache_proxy_table_names ; 
 int /*<<< orphan*/  catalog_is_valid (TYPE_2__*) ; 
 int /*<<< orphan*/  get_namespace_oid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_relname_relid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Oid
ts_catalog_get_cache_proxy_id(Catalog *catalog, CacheType type)
{
	if (!catalog_is_valid(catalog))
	{
		Oid schema;

		/*
		 * The catalog can be invalid during upgrade scripts. Try a non-cached
		 * relation lookup, but we need to be in a transaction for
		 * get_namespace_oid() to work.
		 */
		if (!IsTransactionState())
			return InvalidOid;

		schema = get_namespace_oid(CACHE_SCHEMA_NAME, true);

		if (!OidIsValid(schema))
			return InvalidOid;

		return get_relname_relid(cache_proxy_table_names[type], schema);
	}

	return catalog->caches[type].inval_proxy_id;
}