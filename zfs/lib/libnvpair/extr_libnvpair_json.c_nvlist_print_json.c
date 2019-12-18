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
typedef  size_t uint_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  uchar_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
typedef  scalar_t__ hrtime_t ;
typedef  int data_type_t ;
typedef  scalar_t__ boolean_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
#define  DATA_TYPE_BOOLEAN 156 
#define  DATA_TYPE_BOOLEAN_ARRAY 155 
#define  DATA_TYPE_BOOLEAN_VALUE 154 
#define  DATA_TYPE_BYTE 153 
#define  DATA_TYPE_BYTE_ARRAY 152 
#define  DATA_TYPE_DONTCARE 151 
#define  DATA_TYPE_DOUBLE 150 
#define  DATA_TYPE_HRTIME 149 
#define  DATA_TYPE_INT16 148 
#define  DATA_TYPE_INT16_ARRAY 147 
#define  DATA_TYPE_INT32 146 
#define  DATA_TYPE_INT32_ARRAY 145 
#define  DATA_TYPE_INT64 144 
#define  DATA_TYPE_INT64_ARRAY 143 
#define  DATA_TYPE_INT8 142 
#define  DATA_TYPE_INT8_ARRAY 141 
#define  DATA_TYPE_NVLIST 140 
#define  DATA_TYPE_NVLIST_ARRAY 139 
#define  DATA_TYPE_STRING 138 
#define  DATA_TYPE_STRING_ARRAY 137 
#define  DATA_TYPE_UINT16 136 
#define  DATA_TYPE_UINT16_ARRAY 135 
#define  DATA_TYPE_UINT32 134 
#define  DATA_TYPE_UINT32_ARRAY 133 
#define  DATA_TYPE_UINT64 132 
#define  DATA_TYPE_UINT64_ARRAY 131 
#define  DATA_TYPE_UINT8 130 
#define  DATA_TYPE_UINT8_ARRAY 129 
#define  DATA_TYPE_UNKNOWN 128 
 int /*<<< orphan*/  FPRINTF (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 scalar_t__ fnvpair_value_boolean_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvpair_value_byte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvpair_value_int16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvpair_value_int32 (int /*<<< orphan*/ *) ; 
 scalar_t__ fnvpair_value_int64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvpair_value_int8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fnvpair_value_nvlist (int /*<<< orphan*/ *) ; 
 char* fnvpair_value_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvpair_value_uint16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvpair_value_uint32 (int /*<<< orphan*/ *) ; 
 scalar_t__ fnvpair_value_uint64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvpair_value_uint8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int nvlist_print_json_string (int /*<<< orphan*/ *,char*) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 int nvpair_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_value_boolean_array (int /*<<< orphan*/ *,scalar_t__**,size_t*) ; 
 int /*<<< orphan*/  nvpair_value_byte_array (int /*<<< orphan*/ *,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  nvpair_value_double (int /*<<< orphan*/ *,double*) ; 
 int /*<<< orphan*/  nvpair_value_hrtime (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  nvpair_value_int16_array (int /*<<< orphan*/ *,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  nvpair_value_int32_array (int /*<<< orphan*/ *,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  nvpair_value_int64_array (int /*<<< orphan*/ *,scalar_t__**,size_t*) ; 
 int /*<<< orphan*/  nvpair_value_int8_array (int /*<<< orphan*/ *,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  nvpair_value_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ***,size_t*) ; 
 int /*<<< orphan*/  nvpair_value_string_array (int /*<<< orphan*/ *,char***,size_t*) ; 
 int /*<<< orphan*/  nvpair_value_uint16_array (int /*<<< orphan*/ *,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  nvpair_value_uint32_array (int /*<<< orphan*/ *,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  nvpair_value_uint64_array (int /*<<< orphan*/ *,scalar_t__**,size_t*) ; 
 int /*<<< orphan*/  nvpair_value_uint8_array (int /*<<< orphan*/ *,int /*<<< orphan*/ **,size_t*) ; 

int
nvlist_print_json(FILE *fp, nvlist_t *nvl)
{
	nvpair_t *curr;
	boolean_t first = B_TRUE;

	FPRINTF(fp, "{");

	for (curr = nvlist_next_nvpair(nvl, NULL); curr;
	    curr = nvlist_next_nvpair(nvl, curr)) {
		data_type_t type = nvpair_type(curr);

		if (!first)
			FPRINTF(fp, ",");
		else
			first = B_FALSE;

		if (nvlist_print_json_string(fp, nvpair_name(curr)) == -1)
			return (-1);
		FPRINTF(fp, ":");

		switch (type) {
		case DATA_TYPE_STRING: {
			char *string = fnvpair_value_string(curr);
			if (nvlist_print_json_string(fp, string) == -1)
				return (-1);
			break;
		}

		case DATA_TYPE_BOOLEAN: {
			FPRINTF(fp, "true");
			break;
		}

		case DATA_TYPE_BOOLEAN_VALUE: {
			FPRINTF(fp, "%s", fnvpair_value_boolean_value(curr) ==
			    B_TRUE ? "true" : "false");
			break;
		}

		case DATA_TYPE_BYTE: {
			FPRINTF(fp, "%hhu", fnvpair_value_byte(curr));
			break;
		}

		case DATA_TYPE_INT8: {
			FPRINTF(fp, "%hhd", fnvpair_value_int8(curr));
			break;
		}

		case DATA_TYPE_UINT8: {
			FPRINTF(fp, "%hhu", fnvpair_value_uint8(curr));
			break;
		}

		case DATA_TYPE_INT16: {
			FPRINTF(fp, "%hd", fnvpair_value_int16(curr));
			break;
		}

		case DATA_TYPE_UINT16: {
			FPRINTF(fp, "%hu", fnvpair_value_uint16(curr));
			break;
		}

		case DATA_TYPE_INT32: {
			FPRINTF(fp, "%d", fnvpair_value_int32(curr));
			break;
		}

		case DATA_TYPE_UINT32: {
			FPRINTF(fp, "%u", fnvpair_value_uint32(curr));
			break;
		}

		case DATA_TYPE_INT64: {
			FPRINTF(fp, "%lld",
			    (long long)fnvpair_value_int64(curr));
			break;
		}

		case DATA_TYPE_UINT64: {
			FPRINTF(fp, "%llu",
			    (unsigned long long)fnvpair_value_uint64(curr));
			break;
		}

		case DATA_TYPE_HRTIME: {
			hrtime_t val;
			VERIFY0(nvpair_value_hrtime(curr, &val));
			FPRINTF(fp, "%llu", (unsigned long long)val);
			break;
		}

		case DATA_TYPE_DOUBLE: {
			double val;
			VERIFY0(nvpair_value_double(curr, &val));
			FPRINTF(fp, "%f", val);
			break;
		}

		case DATA_TYPE_NVLIST: {
			if (nvlist_print_json(fp,
			    fnvpair_value_nvlist(curr)) == -1)
				return (-1);
			break;
		}

		case DATA_TYPE_STRING_ARRAY: {
			char **val;
			uint_t valsz, i;
			VERIFY0(nvpair_value_string_array(curr, &val, &valsz));
			FPRINTF(fp, "[");
			for (i = 0; i < valsz; i++) {
				if (i > 0)
					FPRINTF(fp, ",");
				if (nvlist_print_json_string(fp, val[i]) == -1)
					return (-1);
			}
			FPRINTF(fp, "]");
			break;
		}

		case DATA_TYPE_NVLIST_ARRAY: {
			nvlist_t **val;
			uint_t valsz, i;
			VERIFY0(nvpair_value_nvlist_array(curr, &val, &valsz));
			FPRINTF(fp, "[");
			for (i = 0; i < valsz; i++) {
				if (i > 0)
					FPRINTF(fp, ",");
				if (nvlist_print_json(fp, val[i]) == -1)
					return (-1);
			}
			FPRINTF(fp, "]");
			break;
		}

		case DATA_TYPE_BOOLEAN_ARRAY: {
			boolean_t *val;
			uint_t valsz, i;
			VERIFY0(nvpair_value_boolean_array(curr, &val, &valsz));
			FPRINTF(fp, "[");
			for (i = 0; i < valsz; i++) {
				if (i > 0)
					FPRINTF(fp, ",");
				FPRINTF(fp, val[i] == B_TRUE ?
				    "true" : "false");
			}
			FPRINTF(fp, "]");
			break;
		}

		case DATA_TYPE_BYTE_ARRAY: {
			uchar_t *val;
			uint_t valsz, i;
			VERIFY0(nvpair_value_byte_array(curr, &val, &valsz));
			FPRINTF(fp, "[");
			for (i = 0; i < valsz; i++) {
				if (i > 0)
					FPRINTF(fp, ",");
				FPRINTF(fp, "%hhu", val[i]);
			}
			FPRINTF(fp, "]");
			break;
		}

		case DATA_TYPE_UINT8_ARRAY: {
			uint8_t *val;
			uint_t valsz, i;
			VERIFY0(nvpair_value_uint8_array(curr, &val, &valsz));
			FPRINTF(fp, "[");
			for (i = 0; i < valsz; i++) {
				if (i > 0)
					FPRINTF(fp, ",");
				FPRINTF(fp, "%hhu", val[i]);
			}
			FPRINTF(fp, "]");
			break;
		}

		case DATA_TYPE_INT8_ARRAY: {
			int8_t *val;
			uint_t valsz, i;
			VERIFY0(nvpair_value_int8_array(curr, &val, &valsz));
			FPRINTF(fp, "[");
			for (i = 0; i < valsz; i++) {
				if (i > 0)
					FPRINTF(fp, ",");
				FPRINTF(fp, "%hhd", val[i]);
			}
			FPRINTF(fp, "]");
			break;
		}

		case DATA_TYPE_UINT16_ARRAY: {
			uint16_t *val;
			uint_t valsz, i;
			VERIFY0(nvpair_value_uint16_array(curr, &val, &valsz));
			FPRINTF(fp, "[");
			for (i = 0; i < valsz; i++) {
				if (i > 0)
					FPRINTF(fp, ",");
				FPRINTF(fp, "%hu", val[i]);
			}
			FPRINTF(fp, "]");
			break;
		}

		case DATA_TYPE_INT16_ARRAY: {
			int16_t *val;
			uint_t valsz, i;
			VERIFY0(nvpair_value_int16_array(curr, &val, &valsz));
			FPRINTF(fp, "[");
			for (i = 0; i < valsz; i++) {
				if (i > 0)
					FPRINTF(fp, ",");
				FPRINTF(fp, "%hd", val[i]);
			}
			FPRINTF(fp, "]");
			break;
		}

		case DATA_TYPE_UINT32_ARRAY: {
			uint32_t *val;
			uint_t valsz, i;
			VERIFY0(nvpair_value_uint32_array(curr, &val, &valsz));
			FPRINTF(fp, "[");
			for (i = 0; i < valsz; i++) {
				if (i > 0)
					FPRINTF(fp, ",");
				FPRINTF(fp, "%u", val[i]);
			}
			FPRINTF(fp, "]");
			break;
		}

		case DATA_TYPE_INT32_ARRAY: {
			int32_t *val;
			uint_t valsz, i;
			VERIFY0(nvpair_value_int32_array(curr, &val, &valsz));
			FPRINTF(fp, "[");
			for (i = 0; i < valsz; i++) {
				if (i > 0)
					FPRINTF(fp, ",");
				FPRINTF(fp, "%d", val[i]);
			}
			FPRINTF(fp, "]");
			break;
		}

		case DATA_TYPE_UINT64_ARRAY: {
			uint64_t *val;
			uint_t valsz, i;
			VERIFY0(nvpair_value_uint64_array(curr, &val, &valsz));
			FPRINTF(fp, "[");
			for (i = 0; i < valsz; i++) {
				if (i > 0)
					FPRINTF(fp, ",");
				FPRINTF(fp, "%llu",
				    (unsigned long long)val[i]);
			}
			FPRINTF(fp, "]");
			break;
		}

		case DATA_TYPE_INT64_ARRAY: {
			int64_t *val;
			uint_t valsz, i;
			VERIFY0(nvpair_value_int64_array(curr, &val, &valsz));
			FPRINTF(fp, "[");
			for (i = 0; i < valsz; i++) {
				if (i > 0)
					FPRINTF(fp, ",");
				FPRINTF(fp, "%lld", (long long)val[i]);
			}
			FPRINTF(fp, "]");
			break;
		}

		case DATA_TYPE_UNKNOWN:
		case DATA_TYPE_DONTCARE:
			return (-1);
		}

	}

	FPRINTF(fp, "}");
	return (0);
}