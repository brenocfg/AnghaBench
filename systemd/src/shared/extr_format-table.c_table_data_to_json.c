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
struct TYPE_3__ {int type; size_t timestamp; size_t timespan; size_t size; size_t uint_val; size_t uint8; size_t uint16; size_t uint32; size_t uint64; int /*<<< orphan*/  address; int /*<<< orphan*/  ifindex; int /*<<< orphan*/  percent; int /*<<< orphan*/  int64; int /*<<< orphan*/  int32; int /*<<< orphan*/  int16; int /*<<< orphan*/  int8; int /*<<< orphan*/  int_val; int /*<<< orphan*/  boolean; int /*<<< orphan*/  string; } ;
typedef  TYPE_1__ TableData ;
typedef  int /*<<< orphan*/  JsonVariant ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int EINVAL ; 
 int /*<<< orphan*/  FAMILY_ADDRESS_SIZE (int /*<<< orphan*/ ) ; 
#define  TABLE_BOOLEAN 151 
#define  TABLE_BPS 150 
#define  TABLE_EMPTY 149 
#define  TABLE_IFINDEX 148 
#define  TABLE_IN6_ADDR 147 
#define  TABLE_INT 146 
#define  TABLE_INT16 145 
#define  TABLE_INT32 144 
#define  TABLE_INT64 143 
#define  TABLE_INT8 142 
#define  TABLE_IN_ADDR 141 
#define  TABLE_PERCENT 140 
#define  TABLE_SIZE 139 
#define  TABLE_STRING 138 
#define  TABLE_TIMESPAN 137 
#define  TABLE_TIMESPAN_MSEC 136 
#define  TABLE_TIMESTAMP 135 
#define  TABLE_TIMESTAMP_RELATIVE 134 
#define  TABLE_TIMESTAMP_UTC 133 
#define  TABLE_UINT 132 
#define  TABLE_UINT16 131 
#define  TABLE_UINT32 130 
#define  TABLE_UINT64 129 
#define  TABLE_UINT8 128 
 size_t USEC_INFINITY ; 
 int json_variant_new_array_bytes (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int json_variant_new_boolean (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int json_variant_new_integer (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int json_variant_new_null (int /*<<< orphan*/ **) ; 
 int json_variant_new_string (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int json_variant_new_unsigned (int /*<<< orphan*/ **,size_t) ; 

__attribute__((used)) static int table_data_to_json(TableData *d, JsonVariant **ret) {

        switch (d->type) {

        case TABLE_EMPTY:
                return json_variant_new_null(ret);

        case TABLE_STRING:
                return json_variant_new_string(ret, d->string);

        case TABLE_BOOLEAN:
                return json_variant_new_boolean(ret, d->boolean);

        case TABLE_TIMESTAMP:
        case TABLE_TIMESTAMP_UTC:
        case TABLE_TIMESTAMP_RELATIVE:
                if (d->timestamp == USEC_INFINITY)
                        return json_variant_new_null(ret);

                return json_variant_new_unsigned(ret, d->timestamp);

        case TABLE_TIMESPAN:
        case TABLE_TIMESPAN_MSEC:
                if (d->timespan == USEC_INFINITY)
                        return json_variant_new_null(ret);

                return json_variant_new_unsigned(ret, d->timespan);

        case TABLE_SIZE:
        case TABLE_BPS:
                if (d->size == (size_t) -1)
                        return json_variant_new_null(ret);

                return json_variant_new_unsigned(ret, d->size);

        case TABLE_INT:
                return json_variant_new_integer(ret, d->int_val);

        case TABLE_INT8:
                return json_variant_new_integer(ret, d->int8);

        case TABLE_INT16:
                return json_variant_new_integer(ret, d->int16);

        case TABLE_INT32:
                return json_variant_new_integer(ret, d->int32);

        case TABLE_INT64:
                return json_variant_new_integer(ret, d->int64);

        case TABLE_UINT:
                return json_variant_new_unsigned(ret, d->uint_val);

        case TABLE_UINT8:
                return json_variant_new_unsigned(ret, d->uint8);

        case TABLE_UINT16:
                return json_variant_new_unsigned(ret, d->uint16);

        case TABLE_UINT32:
                return json_variant_new_unsigned(ret, d->uint32);

        case TABLE_UINT64:
                return json_variant_new_unsigned(ret, d->uint64);

        case TABLE_PERCENT:
                return json_variant_new_integer(ret, d->percent);

        case TABLE_IFINDEX:
                return json_variant_new_integer(ret, d->ifindex);

        case TABLE_IN_ADDR:
                return json_variant_new_array_bytes(ret, &d->address, FAMILY_ADDRESS_SIZE(AF_INET));

        case TABLE_IN6_ADDR:
                return json_variant_new_array_bytes(ret, &d->address, FAMILY_ADDRESS_SIZE(AF_INET6));

        default:
                return -EINVAL;
        }
}