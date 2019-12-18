#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ type_oid; size_t type_name; int /*<<< orphan*/  schema_name; } ;
typedef  scalar_t__ Oid ;
typedef  TYPE_1__ CustomTypeInfo ;
typedef  size_t CustomType ;

/* Variables and functions */
 int /*<<< orphan*/  CStringGetDatum (size_t) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GetSysCacheOid2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidOid ; 
 scalar_t__ LookupExplicitNamespace (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 int /*<<< orphan*/  OidIsValid (scalar_t__) ; 
 int /*<<< orphan*/  TYPENAMENSP ; 
 size_t _CUSTOM_TYPE_MAX_INDEX ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,size_t) ; 
 TYPE_1__* typeinfo ; 

extern CustomTypeInfo *
ts_custom_type_cache_get(CustomType type)
{
	CustomTypeInfo *tinfo;

	if (type >= _CUSTOM_TYPE_MAX_INDEX)
		elog(ERROR, "invalid timescaledb type %d", type);

	tinfo = &typeinfo[type];

	if (tinfo->type_oid == InvalidOid)
	{
		Oid schema_oid = LookupExplicitNamespace(tinfo->schema_name, false);
		Oid type_oid = GetSysCacheOid2(TYPENAMENSP,
									   CStringGetDatum(tinfo->type_name),
									   ObjectIdGetDatum(schema_oid));
		if (!OidIsValid(type_oid))
			elog(ERROR, "unknown timescaledb type %s", tinfo->type_name);

		tinfo->type_oid = type_oid;
	}

	return tinfo;
}