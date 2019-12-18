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
typedef  int /*<<< orphan*/  usec_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct in_addr {int dummy; } ;
struct in6_addr {int dummy; } ;
typedef  int TableDataType ;

/* Variables and functions */
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
 int /*<<< orphan*/  assert_not_reached (char*) ; 
 int /*<<< orphan*/  strlen (void const*) ; 

__attribute__((used)) static size_t table_data_size(TableDataType type, const void *data) {

        switch (type) {

        case TABLE_EMPTY:
                return 0;

        case TABLE_STRING:
                return strlen(data) + 1;

        case TABLE_BOOLEAN:
                return sizeof(bool);

        case TABLE_TIMESTAMP:
        case TABLE_TIMESTAMP_UTC:
        case TABLE_TIMESTAMP_RELATIVE:
        case TABLE_TIMESPAN:
        case TABLE_TIMESPAN_MSEC:
                return sizeof(usec_t);

        case TABLE_SIZE:
        case TABLE_INT64:
        case TABLE_UINT64:
        case TABLE_BPS:
                return sizeof(uint64_t);

        case TABLE_INT32:
        case TABLE_UINT32:
                return sizeof(uint32_t);

        case TABLE_INT16:
        case TABLE_UINT16:
                return sizeof(uint16_t);

        case TABLE_INT8:
        case TABLE_UINT8:
                return sizeof(uint8_t);

        case TABLE_INT:
        case TABLE_UINT:
        case TABLE_PERCENT:
        case TABLE_IFINDEX:
                return sizeof(int);

        case TABLE_IN_ADDR:
                return sizeof(struct in_addr);

        case TABLE_IN6_ADDR:
                return sizeof(struct in6_addr);

        default:
                assert_not_reached("Uh? Unexpected cell type");
        }
}