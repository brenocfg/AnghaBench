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
typedef  int /*<<< orphan*/  LicenseInfo ;
typedef  int /*<<< orphan*/  Jsonb ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  CStringGetDatum (char*) ; 
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EmitErrorReport () ; 
 int /*<<< orphan*/  PG_CATCH () ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 char* base64_decode (char*) ; 
 int /*<<< orphan*/  jsonb_in ; 
 int /*<<< orphan*/  license_info_init_from_jsonb (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
license_info_init_from_base64(char *license_key, LicenseInfo *out)
{
	char *expanded = base64_decode(license_key);

	if (expanded == NULL)
		return false;

	PG_TRY();
	{
		Datum json_key = DirectFunctionCall1(jsonb_in, CStringGetDatum(expanded));

		license_info_init_from_jsonb((Jsonb *) DatumGetPointer(json_key), out);
	}
	PG_CATCH();
	{
#ifdef TS_DEBUG
		EmitErrorReport();
#endif
		return false;
	}
	PG_END_TRY();
	return true;
}