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
typedef  int /*<<< orphan*/  JsonbParseState ;

/* Variables and functions */
 char* DatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* LICENSE_EDITION_COMMUNITY ; 
 char* LICENSE_EDITION_ENTERPRISE ; 
 int /*<<< orphan*/  LICENSE_EDITION_KEY ; 
 int /*<<< orphan*/  LICENSE_END_TIME_KEY ; 
 int /*<<< orphan*/  LICENSE_ID_KEY ; 
 int /*<<< orphan*/  LICENSE_KIND_KEY ; 
 int /*<<< orphan*/  LICENSE_START_TIME_KEY ; 
 int /*<<< orphan*/  TimestampTzGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  license_end_time () ; 
 int /*<<< orphan*/  license_enterprise_enabled () ; 
 char* license_id_str () ; 
 char* license_kind_str () ; 
 int /*<<< orphan*/  license_start_time () ; 
 int /*<<< orphan*/  timestamptz_out ; 
 int /*<<< orphan*/  ts_jsonb_add_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

void
tsl_telemetry_add_license_info(JsonbParseState *parseState)
{
	if (!license_enterprise_enabled())
		ts_jsonb_add_str(parseState, LICENSE_EDITION_KEY, LICENSE_EDITION_COMMUNITY);
	else
	{
		char *start_time = DatumGetCString(
			DirectFunctionCall1(timestamptz_out, TimestampTzGetDatum(license_start_time())));
		char *end_time = DatumGetCString(
			DirectFunctionCall1(timestamptz_out, TimestampTzGetDatum(license_end_time())));

		ts_jsonb_add_str(parseState, LICENSE_EDITION_KEY, LICENSE_EDITION_ENTERPRISE);
		ts_jsonb_add_str(parseState, LICENSE_KIND_KEY, license_kind_str());
		ts_jsonb_add_str(parseState, LICENSE_ID_KEY, license_id_str());
		ts_jsonb_add_str(parseState, LICENSE_START_TIME_KEY, start_time);
		ts_jsonb_add_str(parseState, LICENSE_END_TIME_KEY, end_time);
	}
}