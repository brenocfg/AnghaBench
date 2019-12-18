#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {char* sysname; char* version; char* release; char* pretty_version; scalar_t__ has_pretty_version; } ;
typedef  TYPE_3__ VersionOSInfo ;
struct TYPE_17__ {int /*<<< orphan*/  uncompressed_toast_size; int /*<<< orphan*/  uncompressed_index_size; int /*<<< orphan*/  uncompressed_heap_size; int /*<<< orphan*/  compressed_toast_size; int /*<<< orphan*/  compressed_index_size; int /*<<< orphan*/  compressed_heap_size; } ;
typedef  TYPE_4__ TotalSizes ;
struct TYPE_19__ {int /*<<< orphan*/  root; } ;
struct TYPE_14__ {void* len; void* val; } ;
struct TYPE_15__ {TYPE_1__ string; } ;
struct TYPE_18__ {TYPE_2__ val; void* type; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_5__ JsonbValue ;
typedef  int /*<<< orphan*/  JsonbParseState ;
typedef  TYPE_6__ Jsonb ;

/* Variables and functions */
 char* BUILD_OS_NAME ; 
 char* BUILD_OS_VERSION ; 
 char* BUILD_PROCESSOR ; 
 char* DatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JsonbToCString (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_6__* JsonbValueToJsonb (TYPE_5__*) ; 
 int /*<<< orphan*/  REQ_BUILD_ARCHITECTURE ; 
 int /*<<< orphan*/  REQ_BUILD_ARCHITECTURE_BIT_SIZE ; 
 int /*<<< orphan*/  REQ_BUILD_OS ; 
 int /*<<< orphan*/  REQ_BUILD_OS_VERSION ; 
 int /*<<< orphan*/  REQ_COMPRESSED_HEAP_SIZE ; 
 int /*<<< orphan*/  REQ_COMPRESSED_INDEX_SIZE ; 
 int /*<<< orphan*/  REQ_COMPRESSED_TOAST_SIZE ; 
 int /*<<< orphan*/  REQ_DATA_VOLUME ; 
 int /*<<< orphan*/  REQ_DB_UUID ; 
 int /*<<< orphan*/  REQ_EXPORTED_DB_UUID ; 
 int /*<<< orphan*/  REQ_INSTALL_METHOD ; 
 int /*<<< orphan*/  REQ_INSTALL_TIME ; 
 void* REQ_INSTANCE_METADATA ; 
 void* REQ_LICENSE_INFO ; 
 void* REQ_METADATA ; 
 int /*<<< orphan*/  REQ_NUM_COMPRESSED_HYPERTABLES ; 
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
 int /*<<< orphan*/  REQ_TS_LAST_TUNE_TIME ; 
 int /*<<< orphan*/  REQ_TS_LAST_TUNE_VERSION ; 
 int /*<<< orphan*/  REQ_TS_TELEMETRY_CLOUD ; 
 int /*<<< orphan*/  REQ_TS_VERSION ; 
 int /*<<< orphan*/  REQ_UNCOMPRESSED_HEAP_SIZE ; 
 int /*<<< orphan*/  REQ_UNCOMPRESSED_INDEX_SIZE ; 
 int /*<<< orphan*/  REQ_UNCOMPRESSED_TOAST_SIZE ; 
 char* TIMESCALEDB_INSTALL_METHOD ; 
 char* TIMESCALEDB_VERSION_MOD ; 
 int /*<<< orphan*/  VARSIZE (TYPE_6__*) ; 
 int /*<<< orphan*/  WJB_BEGIN_OBJECT ; 
 int /*<<< orphan*/  WJB_END_OBJECT ; 
 int /*<<< orphan*/  WJB_KEY ; 
 int /*<<< orphan*/  add_license_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_related_extensions (int /*<<< orphan*/ *) ; 
 char* get_architecture_bit_size () ; 
 char* get_database_size () ; 
 char* get_num_compressed_hypertables () ; 
 char* get_num_continuous_aggs () ; 
 char* get_num_drop_chunks_policies () ; 
 char* get_num_hypertables () ; 
 char* get_num_reorder_policies () ; 
 char* get_pgversion_string () ; 
 char* get_size (int /*<<< orphan*/ ) ; 
 void* jbvString ; 
 int /*<<< orphan*/  makeStringInfo () ; 
 TYPE_5__* pushJsonbValue (int /*<<< orphan*/ **,int /*<<< orphan*/ ,TYPE_5__*) ; 
 void* strlen (void*) ; 
 int /*<<< orphan*/  timestamptz_out ; 
 TYPE_4__ ts_compression_chunk_size_totals () ; 
 int /*<<< orphan*/  ts_jsonb_add_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 char* ts_last_tune_time ; 
 char* ts_last_tune_version ; 
 char* ts_telemetry_cloud ; 
 int /*<<< orphan*/  ts_telemetry_metadata_add_values (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_telemetry_metadata_get_exported_uuid () ; 
 int /*<<< orphan*/  ts_telemetry_metadata_get_install_timestamp () ; 
 int /*<<< orphan*/  ts_telemetry_metadata_get_uuid () ; 
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
	TotalSizes sizes = ts_compression_chunk_size_totals();

	pushJsonbValue(&parseState, WJB_BEGIN_OBJECT, NULL);

	ts_jsonb_add_str(parseState,
					 REQ_DB_UUID,
					 DatumGetCString(
						 DirectFunctionCall1(uuid_out, ts_telemetry_metadata_get_uuid())));
	ts_jsonb_add_str(parseState,
					 REQ_EXPORTED_DB_UUID,
					 DatumGetCString(
						 DirectFunctionCall1(uuid_out, ts_telemetry_metadata_get_exported_uuid())));
	ts_jsonb_add_str(parseState,
					 REQ_INSTALL_TIME,
					 DatumGetCString(
						 DirectFunctionCall1(timestamptz_out,
											 ts_telemetry_metadata_get_install_timestamp())));

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

	ts_jsonb_add_str(parseState, REQ_PS_VERSION, get_pgversion_string());
	ts_jsonb_add_str(parseState, REQ_TS_VERSION, TIMESCALEDB_VERSION_MOD);
	ts_jsonb_add_str(parseState, REQ_BUILD_OS, BUILD_OS_NAME);
	ts_jsonb_add_str(parseState, REQ_BUILD_OS_VERSION, BUILD_OS_VERSION);
	ts_jsonb_add_str(parseState, REQ_BUILD_ARCHITECTURE, BUILD_PROCESSOR);
	ts_jsonb_add_str(parseState, REQ_BUILD_ARCHITECTURE_BIT_SIZE, get_architecture_bit_size());
	ts_jsonb_add_str(parseState, REQ_DATA_VOLUME, get_database_size());
	ts_jsonb_add_str(parseState, REQ_NUM_HYPERTABLES, get_num_hypertables());
	ts_jsonb_add_str(parseState, REQ_NUM_COMPRESSED_HYPERTABLES, get_num_compressed_hypertables());
	ts_jsonb_add_str(parseState, REQ_NUM_CONTINUOUS_AGGS, get_num_continuous_aggs());
	ts_jsonb_add_str(parseState, REQ_NUM_REORDER_POLICIES, get_num_reorder_policies());
	ts_jsonb_add_str(parseState, REQ_NUM_DROP_CHUNKS_POLICIES, get_num_drop_chunks_policies());

	ts_jsonb_add_str(parseState, REQ_COMPRESSED_HEAP_SIZE, get_size(sizes.compressed_heap_size));
	ts_jsonb_add_str(parseState, REQ_COMPRESSED_INDEX_SIZE, get_size(sizes.compressed_index_size));
	ts_jsonb_add_str(parseState, REQ_COMPRESSED_TOAST_SIZE, get_size(sizes.compressed_toast_size));
	ts_jsonb_add_str(parseState,
					 REQ_UNCOMPRESSED_HEAP_SIZE,
					 get_size(sizes.uncompressed_heap_size));
	ts_jsonb_add_str(parseState,
					 REQ_UNCOMPRESSED_INDEX_SIZE,
					 get_size(sizes.uncompressed_index_size));
	ts_jsonb_add_str(parseState,
					 REQ_UNCOMPRESSED_TOAST_SIZE,
					 get_size(sizes.uncompressed_toast_size));

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

	/* Add additional content from metadata */
	ext_key.type = jbvString;
	ext_key.val.string.val = REQ_METADATA;
	ext_key.val.string.len = strlen(REQ_METADATA);
	pushJsonbValue(&parseState, WJB_KEY, &ext_key);
	pushJsonbValue(&parseState, WJB_BEGIN_OBJECT, NULL);
	ts_telemetry_metadata_add_values(parseState);
	pushJsonbValue(&parseState, WJB_END_OBJECT, NULL);

	/* end of telemetry object */
	result = pushJsonbValue(&parseState, WJB_END_OBJECT, NULL);
	jb = JsonbValueToJsonb(result);
	jtext = makeStringInfo();
	JsonbToCString(jtext, &jb->root, VARSIZE(jb));

	return jtext;
}