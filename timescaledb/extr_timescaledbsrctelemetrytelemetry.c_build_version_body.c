#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {char* sysname; char* version; char* release; char* pretty_version; scalar_t__ has_pretty_version; } ;
typedef  TYPE_3__ VersionOSInfo ;
struct TYPE_16__ {int /*<<< orphan*/  root; } ;
struct TYPE_12__ {void* len; void* val; } ;
struct TYPE_13__ {TYPE_1__ string; } ;
struct TYPE_15__ {TYPE_2__ val; void* type; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_4__ JsonbValue ;
typedef  int /*<<< orphan*/  JsonbParseState ;
typedef  TYPE_5__ Jsonb ;

/* Variables and functions */
 char* BUILD_OS_NAME ; 
 char* BUILD_OS_VERSION ; 
 char* DatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JsonbToCString (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_5__* JsonbValueToJsonb (TYPE_4__*) ; 
 char* PACKAGE_VERSION ; 
 int /*<<< orphan*/  REQ_BUILD_OS ; 
 int /*<<< orphan*/  REQ_BUILD_OS_VERSION ; 
 int /*<<< orphan*/  REQ_DATA_VOLUME ; 
 int /*<<< orphan*/  REQ_DB_UUID ; 
 int /*<<< orphan*/  REQ_EXPORTED_DB_UUID ; 
 int /*<<< orphan*/  REQ_INSTALL_METHOD ; 
 int /*<<< orphan*/  REQ_INSTALL_TIME ; 
 void* REQ_INSTANCE_METADATA ; 
 void* REQ_LICENSE_INFO ; 
 int /*<<< orphan*/  REQ_NUM_CONTINUOUS_AGGS ; 
 int /*<<< orphan*/  REQ_NUM_DROP_CHUNKS_POLICIES ; 
 int /*<<< orphan*/  REQ_NUM_HYPERTABLES ; 
 int /*<<< orphan*/  REQ_NUM_REORDER_POLICIES ; 
 int /*<<< orphan*/  REQ_OS ; 
 int /*<<< orphan*/  REQ_OS_RELEASE ; 
 int /*<<< orphan*/  REQ_OS_VERSION ; 
 int /*<<< orphan*/  REQ_OS_VERSION_PRETTY ; 
 int /*<<< orphan*/  REQ_PS_VERSION ; 
 void* REQ_RELATED_EXTENSIONS ; 
 void* REQ_TELEMETRY_METADATA ; 
 int /*<<< orphan*/  REQ_TS_LAST_TUNE_TIME ; 
 int /*<<< orphan*/  REQ_TS_LAST_TUNE_VERSION ; 
 int /*<<< orphan*/  REQ_TS_TELEMETRY_CLOUD ; 
 int /*<<< orphan*/  REQ_TS_VERSION ; 
 char* TIMESCALEDB_INSTALL_METHOD ; 
 char* TIMESCALEDB_VERSION_MOD ; 
 int /*<<< orphan*/  VARSIZE (TYPE_5__*) ; 
 int /*<<< orphan*/  WJB_BEGIN_OBJECT ; 
 int /*<<< orphan*/  WJB_END_OBJECT ; 
 int /*<<< orphan*/  WJB_KEY ; 
 int /*<<< orphan*/  add_license_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_related_extensions (int /*<<< orphan*/ *) ; 
 char* get_database_size () ; 
 char* get_num_continuous_aggs () ; 
 char* get_num_drop_chunks_policies () ; 
 char* get_num_hypertables () ; 
 char* get_num_reorder_policies () ; 
 void* jbvString ; 
 int /*<<< orphan*/  makeStringInfo () ; 
 TYPE_4__* pushJsonbValue (int /*<<< orphan*/ **,int /*<<< orphan*/ ,TYPE_4__*) ; 
 void* strlen (void*) ; 
 int /*<<< orphan*/  timestamptz_out ; 
 int /*<<< orphan*/  ts_jsonb_add_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 char* ts_last_tune_time ; 
 char* ts_last_tune_version ; 
 int /*<<< orphan*/  ts_metadata_add_values (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_metadata_get_exported_uuid () ; 
 int /*<<< orphan*/  ts_metadata_get_install_timestamp () ; 
 int /*<<< orphan*/  ts_metadata_get_uuid () ; 
 char* ts_telemetry_cloud ; 
 scalar_t__ ts_version_get_os_info (TYPE_3__*) ; 
 int /*<<< orphan*/  uuid_out ; 

__attribute__((used)) static StringInfo
build_version_body(void)
{
	JsonbValue ext_key;
	JsonbValue license_info_key;
	JsonbValue *result;
	Jsonb *jb;
	StringInfo jtext;
	VersionOSInfo osinfo;
	JsonbParseState *parseState = NULL;

	pushJsonbValue(&parseState, WJB_BEGIN_OBJECT, NULL);

	ts_jsonb_add_str(parseState,
					 REQ_DB_UUID,
					 DatumGetCString(DirectFunctionCall1(uuid_out, ts_metadata_get_uuid())));
	ts_jsonb_add_str(parseState,
					 REQ_EXPORTED_DB_UUID,
					 DatumGetCString(
						 DirectFunctionCall1(uuid_out, ts_metadata_get_exported_uuid())));
	ts_jsonb_add_str(parseState,
					 REQ_INSTALL_TIME,
					 DatumGetCString(DirectFunctionCall1(timestamptz_out,
														 ts_metadata_get_install_timestamp())));

	ts_jsonb_add_str(parseState, REQ_INSTALL_METHOD, TIMESCALEDB_INSTALL_METHOD);

	if (ts_version_get_os_info(&osinfo))
	{
		ts_jsonb_add_str(parseState, REQ_OS, osinfo.sysname);
		ts_jsonb_add_str(parseState, REQ_OS_VERSION, osinfo.version);
		ts_jsonb_add_str(parseState, REQ_OS_RELEASE, osinfo.release);
		if (osinfo.has_pretty_version)
			ts_jsonb_add_str(parseState, REQ_OS_VERSION_PRETTY, osinfo.pretty_version);
	}
	else
		ts_jsonb_add_str(parseState, REQ_OS, "Unknown");

	/*
	 * PACKAGE_VERSION does not include extra details that some systems (e.g.,
	 * Ubuntu) sometimes include in PG_VERSION
	 */
	ts_jsonb_add_str(parseState, REQ_PS_VERSION, PACKAGE_VERSION);
	ts_jsonb_add_str(parseState, REQ_TS_VERSION, TIMESCALEDB_VERSION_MOD);
	ts_jsonb_add_str(parseState, REQ_BUILD_OS, BUILD_OS_NAME);
	ts_jsonb_add_str(parseState, REQ_BUILD_OS_VERSION, BUILD_OS_VERSION);
	ts_jsonb_add_str(parseState, REQ_DATA_VOLUME, get_database_size());
	ts_jsonb_add_str(parseState, REQ_NUM_HYPERTABLES, get_num_hypertables());
	ts_jsonb_add_str(parseState, REQ_NUM_CONTINUOUS_AGGS, get_num_continuous_aggs());
	ts_jsonb_add_str(parseState, REQ_NUM_REORDER_POLICIES, get_num_reorder_policies());
	ts_jsonb_add_str(parseState, REQ_NUM_DROP_CHUNKS_POLICIES, get_num_drop_chunks_policies());

	/* Add related extensions, which is a nested JSON */
	ext_key.type = jbvString;
	ext_key.val.string.val = REQ_RELATED_EXTENSIONS;
	ext_key.val.string.len = strlen(REQ_RELATED_EXTENSIONS);
	pushJsonbValue(&parseState, WJB_KEY, &ext_key);
	add_related_extensions(parseState);

	/* add license info, which is a nested JSON */
	license_info_key.type = jbvString;
	license_info_key.val.string.val = REQ_LICENSE_INFO;
	license_info_key.val.string.len = strlen(REQ_LICENSE_INFO);
	pushJsonbValue(&parseState, WJB_KEY, &license_info_key);
	add_license_info(parseState);

	/* add tuned info, which is optional */
	if (ts_last_tune_time != NULL)
		ts_jsonb_add_str(parseState, REQ_TS_LAST_TUNE_TIME, ts_last_tune_time);

	if (ts_last_tune_version != NULL)
		ts_jsonb_add_str(parseState, REQ_TS_LAST_TUNE_VERSION, ts_last_tune_version);

	/* add cloud to telemetry when set */
	if (ts_telemetry_cloud != NULL)
	{
		ext_key.type = jbvString;
		ext_key.val.string.val = REQ_INSTANCE_METADATA;
		ext_key.val.string.len = strlen(REQ_INSTANCE_METADATA);
		pushJsonbValue(&parseState, WJB_KEY, &ext_key);

		pushJsonbValue(&parseState, WJB_BEGIN_OBJECT, NULL);
		ts_jsonb_add_str(parseState, REQ_TS_TELEMETRY_CLOUD, ts_telemetry_cloud);
		pushJsonbValue(&parseState, WJB_END_OBJECT, NULL);
	}

	/* Add additional content from telemetry_metadata */
	ext_key.type = jbvString;
	ext_key.val.string.val = REQ_TELEMETRY_METADATA;
	ext_key.val.string.len = strlen(REQ_TELEMETRY_METADATA);
	pushJsonbValue(&parseState, WJB_KEY, &ext_key);
	pushJsonbValue(&parseState, WJB_BEGIN_OBJECT, NULL);
	ts_metadata_add_values(parseState);
	pushJsonbValue(&parseState, WJB_END_OBJECT, NULL);

	/* end of telemetry object */
	result = pushJsonbValue(&parseState, WJB_END_OBJECT, NULL);
	jb = JsonbValueToJsonb(result);
	jtext = makeStringInfo();
	JsonbToCString(jtext, &jb->root, VARSIZE(jb));

	return jtext;
}