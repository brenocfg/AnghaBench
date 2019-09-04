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
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetSysCacheOid2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LookupExplicitNamespace (char const*,int) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (char const*) ; 
 int /*<<< orphan*/  TYPENAMENSP ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 char* pq_getmsgstring (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Oid
polydatum_deserialize_type(StringInfo buf)
{
	const char *schema_name = pq_getmsgstring(buf);
	const char *type_name = pq_getmsgstring(buf);
	Oid schema_oid = LookupExplicitNamespace(schema_name, false);
	Oid type_oid =
		GetSysCacheOid2(TYPENAMENSP, PointerGetDatum(type_name), ObjectIdGetDatum(schema_oid));
	if (!OidIsValid(type_oid))
		elog(ERROR, "cache lookup failed for type %s.%s", schema_name, type_name);

	return type_oid;
}