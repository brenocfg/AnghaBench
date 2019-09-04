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
typedef  enum ExtensionState { ____Placeholder_ExtensionState } ExtensionState ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_SCHEMA_NAME ; 
 int /*<<< orphan*/  EXTENSION_PROXY_TABLE ; 
#define  EXTENSION_STATE_CREATED 131 
#define  EXTENSION_STATE_NOT_INSTALLED 130 
#define  EXTENSION_STATE_TRANSITIONING 129 
#define  EXTENSION_STATE_UNKNOWN 128 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  TIMESCALEDB_VERSION_MOD ; 
 int /*<<< orphan*/  extension_proxy_oid ; 
 int extstate ; 
 int /*<<< orphan*/  get_namespace_oid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_relname_relid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_catalog_reset () ; 
 int /*<<< orphan*/  ts_extension_check_version (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
extension_set_state(enum ExtensionState newstate)
{
	if (newstate == extstate)
	{
		return false;
	}
	switch (newstate)
	{
		case EXTENSION_STATE_TRANSITIONING:
		case EXTENSION_STATE_UNKNOWN:
			break;
		case EXTENSION_STATE_CREATED:
			ts_extension_check_version(TIMESCALEDB_VERSION_MOD);
			extension_proxy_oid = get_relname_relid(EXTENSION_PROXY_TABLE,
													get_namespace_oid(CACHE_SCHEMA_NAME, false));
			ts_catalog_reset();
			break;
		case EXTENSION_STATE_NOT_INSTALLED:
			extension_proxy_oid = InvalidOid;
			ts_catalog_reset();
			break;
	}
	extstate = newstate;
	return true;
}