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

Oid
binary_string_get_type(StringInfo buffer)
{
	const char *element_type_namespace = pq_getmsgstring(buffer);
	const char *element_type_name = pq_getmsgstring(buffer);
	Oid namespace_oid;
	Oid type_oid;

	namespace_oid = LookupExplicitNamespace(element_type_namespace, false);

	type_oid = GetSysCacheOid2(TYPENAMENSP,
							   PointerGetDatum(element_type_name),
							   ObjectIdGetDatum(namespace_oid));
	if (!OidIsValid(type_oid))
		elog(ERROR, "could not find type %s.%s", element_type_namespace, element_type_name);

	return type_oid;
}