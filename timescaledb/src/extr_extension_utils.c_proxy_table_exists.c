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

/* Variables and functions */
 int /*<<< orphan*/  CACHE_SCHEMA_NAME ; 
 int /*<<< orphan*/  EXTENSION_PROXY_TABLE ; 
 int OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_namespace_oid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_relname_relid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool inline proxy_table_exists()
{
	Oid nsid = get_namespace_oid(CACHE_SCHEMA_NAME, true);

	if (!OidIsValid(nsid))
		return false;

	return OidIsValid(get_relname_relid(EXTENSION_PROXY_TABLE, nsid));
}