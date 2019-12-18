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
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  CSTRINGOID ; 
 int /*<<< orphan*/  CStringGetDatum (char const*) ; 
 int /*<<< orphan*/  UUIDOID ; 
 int /*<<< orphan*/  UUIDPGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_metadata_get_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ts_metadata_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ts_uuid_create () ; 

__attribute__((used)) static Datum
get_uuid_by_key(const char *key)
{
	bool isnull;
	Datum uuid;

	uuid = ts_metadata_get_value(CStringGetDatum(key), CSTRINGOID, UUIDOID, &isnull);

	if (isnull)
		uuid = ts_metadata_insert(CStringGetDatum(key),
								  CSTRINGOID,
								  UUIDPGetDatum(ts_uuid_create()),
								  UUIDOID,
								  true);
	return uuid;
}