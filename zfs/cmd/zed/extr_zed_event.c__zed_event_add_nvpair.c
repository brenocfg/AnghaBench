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
typedef  int /*<<< orphan*/  zed_strings_t ;
typedef  char* uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  char* uint32_t ;
typedef  char* uint16_t ;
typedef  char* u_longlong_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  char* longlong_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
typedef  int /*<<< orphan*/  hrtime_t ;
typedef  int data_type_t ;
typedef  int /*<<< orphan*/  boolean_t ;
typedef  int /*<<< orphan*/  alt ;

/* Variables and functions */
#define  DATA_TYPE_BOOLEAN 154 
#define  DATA_TYPE_BOOLEAN_ARRAY 153 
#define  DATA_TYPE_BOOLEAN_VALUE 152 
#define  DATA_TYPE_BYTE 151 
#define  DATA_TYPE_BYTE_ARRAY 150 
#define  DATA_TYPE_DOUBLE 149 
#define  DATA_TYPE_HRTIME 148 
#define  DATA_TYPE_INT16 147 
#define  DATA_TYPE_INT16_ARRAY 146 
#define  DATA_TYPE_INT32 145 
#define  DATA_TYPE_INT32_ARRAY 144 
#define  DATA_TYPE_INT64 143 
#define  DATA_TYPE_INT64_ARRAY 142 
#define  DATA_TYPE_INT8 141 
#define  DATA_TYPE_INT8_ARRAY 140 
#define  DATA_TYPE_NVLIST 139 
#define  DATA_TYPE_NVLIST_ARRAY 138 
#define  DATA_TYPE_STRING 137 
#define  DATA_TYPE_STRING_ARRAY 136 
#define  DATA_TYPE_UINT16 135 
#define  DATA_TYPE_UINT16_ARRAY 134 
#define  DATA_TYPE_UINT32 133 
#define  DATA_TYPE_UINT32_ARRAY 132 
#define  DATA_TYPE_UINT64 131 
#define  DATA_TYPE_UINT64_ARRAY 130 
#define  DATA_TYPE_UINT8 129 
#define  DATA_TYPE_UINT8_ARRAY 128 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  FM_EREPORT_PAYLOAD_ZFS_POOL_STATE ; 
 int /*<<< orphan*/  FM_EREPORT_PAYLOAD_ZFS_VDEV_LASTSTATE ; 
 int /*<<< orphan*/  FM_EREPORT_PAYLOAD_ZFS_VDEV_STATE ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  VDEV_AUX_NONE ; 
 char* ZEVENT_VAR_PREFIX ; 
 int /*<<< orphan*/  _zed_event_add_int16_array (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zed_event_add_int32_array (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zed_event_add_int64_array (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zed_event_add_int8_array (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zed_event_add_string_array (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zed_event_add_uint16_array (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zed_event_add_uint32_array (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zed_event_add_uint64_array (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zed_event_add_uint8_array (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zed_event_add_var (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,char const*,char*,...) ; 
 int /*<<< orphan*/  _zed_event_value_is_hex (char const*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 int nvpair_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_value_boolean_value (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_value_byte (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  nvpair_value_double (int /*<<< orphan*/ *,double*) ; 
 int /*<<< orphan*/  nvpair_value_hrtime (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_value_int16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_value_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_value_int64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_value_int8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_value_string (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  nvpair_value_uint16 (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  nvpair_value_uint32 (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  nvpair_value_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_value_uint8 (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zed_log_msg (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ,unsigned int) ; 
 char* zpool_pool_state_to_name (int /*<<< orphan*/ ) ; 
 char* zpool_state_to_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_zed_event_add_nvpair(uint64_t eid, zed_strings_t *zsp, nvpair_t *nvp)
{
	const char *name;
	data_type_t type;
	const char *prefix = ZEVENT_VAR_PREFIX;
	boolean_t b;
	double d;
	uint8_t i8;
	uint16_t i16;
	uint32_t i32;
	uint64_t i64;
	char *str;

	assert(zsp != NULL);
	assert(nvp != NULL);

	name = nvpair_name(nvp);
	type = nvpair_type(nvp);

	switch (type) {
	case DATA_TYPE_BOOLEAN:
		_zed_event_add_var(eid, zsp, prefix, name, "%s", "1");
		break;
	case DATA_TYPE_BOOLEAN_VALUE:
		(void) nvpair_value_boolean_value(nvp, &b);
		_zed_event_add_var(eid, zsp, prefix, name, "%s", b ? "1" : "0");
		break;
	case DATA_TYPE_BYTE:
		(void) nvpair_value_byte(nvp, &i8);
		_zed_event_add_var(eid, zsp, prefix, name, "%d", i8);
		break;
	case DATA_TYPE_INT8:
		(void) nvpair_value_int8(nvp, (int8_t *)&i8);
		_zed_event_add_var(eid, zsp, prefix, name, "%d", i8);
		break;
	case DATA_TYPE_UINT8:
		(void) nvpair_value_uint8(nvp, &i8);
		_zed_event_add_var(eid, zsp, prefix, name, "%u", i8);
		break;
	case DATA_TYPE_INT16:
		(void) nvpair_value_int16(nvp, (int16_t *)&i16);
		_zed_event_add_var(eid, zsp, prefix, name, "%d", i16);
		break;
	case DATA_TYPE_UINT16:
		(void) nvpair_value_uint16(nvp, &i16);
		_zed_event_add_var(eid, zsp, prefix, name, "%u", i16);
		break;
	case DATA_TYPE_INT32:
		(void) nvpair_value_int32(nvp, (int32_t *)&i32);
		_zed_event_add_var(eid, zsp, prefix, name, "%d", i32);
		break;
	case DATA_TYPE_UINT32:
		(void) nvpair_value_uint32(nvp, &i32);
		_zed_event_add_var(eid, zsp, prefix, name, "%u", i32);
		break;
	case DATA_TYPE_INT64:
		(void) nvpair_value_int64(nvp, (int64_t *)&i64);
		_zed_event_add_var(eid, zsp, prefix, name,
		    "%lld", (longlong_t)i64);
		break;
	case DATA_TYPE_UINT64:
		(void) nvpair_value_uint64(nvp, &i64);
		_zed_event_add_var(eid, zsp, prefix, name,
		    (_zed_event_value_is_hex(name) ? "0x%.16llX" : "%llu"),
		    (u_longlong_t)i64);
		/*
		 * shadow readable strings for vdev state pairs
		 */
		if (strcmp(name, FM_EREPORT_PAYLOAD_ZFS_VDEV_STATE) == 0 ||
		    strcmp(name, FM_EREPORT_PAYLOAD_ZFS_VDEV_LASTSTATE) == 0) {
			char alt[32];

			(void) snprintf(alt, sizeof (alt), "%s_str", name);
			_zed_event_add_var(eid, zsp, prefix, alt, "%s",
			    zpool_state_to_name(i64, VDEV_AUX_NONE));
		} else
		/*
		 * shadow readable strings for pool state
		 */
		if (strcmp(name, FM_EREPORT_PAYLOAD_ZFS_POOL_STATE) == 0) {
			char alt[32];

			(void) snprintf(alt, sizeof (alt), "%s_str", name);
			_zed_event_add_var(eid, zsp, prefix, alt, "%s",
			    zpool_pool_state_to_name(i64));
		}
		break;
	case DATA_TYPE_DOUBLE:
		(void) nvpair_value_double(nvp, &d);
		_zed_event_add_var(eid, zsp, prefix, name, "%g", d);
		break;
	case DATA_TYPE_HRTIME:
		(void) nvpair_value_hrtime(nvp, (hrtime_t *)&i64);
		_zed_event_add_var(eid, zsp, prefix, name,
		    "%llu", (u_longlong_t)i64);
		break;
	case DATA_TYPE_NVLIST:
		_zed_event_add_var(eid, zsp, prefix, name,
		    "%s", "_NOT_IMPLEMENTED_");			/* FIXME */
		break;
	case DATA_TYPE_STRING:
		(void) nvpair_value_string(nvp, &str);
		_zed_event_add_var(eid, zsp, prefix, name,
		    "%s", (str ? str : "<NULL>"));
		break;
	case DATA_TYPE_BOOLEAN_ARRAY:
		_zed_event_add_var(eid, zsp, prefix, name,
		    "%s", "_NOT_IMPLEMENTED_");			/* FIXME */
		break;
	case DATA_TYPE_BYTE_ARRAY:
		_zed_event_add_var(eid, zsp, prefix, name,
		    "%s", "_NOT_IMPLEMENTED_");			/* FIXME */
		break;
	case DATA_TYPE_INT8_ARRAY:
		_zed_event_add_int8_array(eid, zsp, prefix, nvp);
		break;
	case DATA_TYPE_UINT8_ARRAY:
		_zed_event_add_uint8_array(eid, zsp, prefix, nvp);
		break;
	case DATA_TYPE_INT16_ARRAY:
		_zed_event_add_int16_array(eid, zsp, prefix, nvp);
		break;
	case DATA_TYPE_UINT16_ARRAY:
		_zed_event_add_uint16_array(eid, zsp, prefix, nvp);
		break;
	case DATA_TYPE_INT32_ARRAY:
		_zed_event_add_int32_array(eid, zsp, prefix, nvp);
		break;
	case DATA_TYPE_UINT32_ARRAY:
		_zed_event_add_uint32_array(eid, zsp, prefix, nvp);
		break;
	case DATA_TYPE_INT64_ARRAY:
		_zed_event_add_int64_array(eid, zsp, prefix, nvp);
		break;
	case DATA_TYPE_UINT64_ARRAY:
		_zed_event_add_uint64_array(eid, zsp, prefix, nvp);
		break;
	case DATA_TYPE_STRING_ARRAY:
		_zed_event_add_string_array(eid, zsp, prefix, nvp);
		break;
	case DATA_TYPE_NVLIST_ARRAY:
		_zed_event_add_var(eid, zsp, prefix, name,
		    "%s", "_NOT_IMPLEMENTED_");			/* FIXME */
		break;
	default:
		errno = EINVAL;
		zed_log_msg(LOG_WARNING,
		    "Failed to convert nvpair \"%s\" for eid=%llu: "
		    "Unrecognized type=%u", name, eid, (unsigned int) type);
		break;
	}
}