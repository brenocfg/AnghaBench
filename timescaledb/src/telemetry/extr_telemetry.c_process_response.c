#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  versionstr; int /*<<< orphan*/  errhint; } ;
typedef  TYPE_1__ VersionResult ;

/* Variables and functions */
 int /*<<< orphan*/  CStringGetTextDatum (char const*) ; 
 int DatumGetBool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXTENSION_NAME ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  NOTICE ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMESCALEDB_VERSION_MOD ; 
 char* TS_IS_UPTODATE_JSON_FIELD ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  cstring_to_text (char*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_object_field_text ; 
 int /*<<< orphan*/  texteq ; 
 int /*<<< orphan*/  ts_validate_server_version (char const*,TYPE_1__*) ; 

__attribute__((used)) static void
process_response(const char *json)
{
	VersionResult result;
	bool is_uptodate =
		DatumGetBool(DirectFunctionCall2(texteq,
										 DirectFunctionCall2(json_object_field_text,
															 CStringGetTextDatum(json),
															 PointerGetDatum(cstring_to_text(
																 TS_IS_UPTODATE_JSON_FIELD))),
										 PointerGetDatum(cstring_to_text("true"))));

	if (is_uptodate)
		elog(NOTICE, "the \"%s\" extension is up-to-date", EXTENSION_NAME);
	else
	{
		if (!ts_validate_server_version(json, &result))
		{
			elog(WARNING, "server did not return a valid TimescaleDB version: %s", result.errhint);
			return;
		}

		ereport(LOG,
				(errmsg("the \"%s\" extension is not up-to-date", EXTENSION_NAME),
				 errhint("The most up-to-date version is %s, the installed version is %s",
						 result.versionstr,
						 TIMESCALEDB_VERSION_MOD)));
	}
}