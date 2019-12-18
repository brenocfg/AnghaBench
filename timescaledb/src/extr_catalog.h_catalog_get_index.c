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
struct TYPE_5__ {TYPE_1__* tables; } ;
struct TYPE_4__ {int /*<<< orphan*/ * index_ids; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  size_t CatalogTable ;
typedef  TYPE_2__ Catalog ;

/* Variables and functions */
 int INVALID_INDEXID ; 
 int /*<<< orphan*/  InvalidOid ; 

__attribute__((used)) static inline Oid
catalog_get_index(Catalog *catalog, CatalogTable tableid, int indexid)
{
	return (indexid == INVALID_INDEXID) ? InvalidOid : catalog->tables[tableid].index_ids[indexid];
}