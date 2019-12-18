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

/* Variables and functions */
 int EINVAL ; 
#define  SD_BUS_TYPE_ARRAY 146 
#define  SD_BUS_TYPE_BOOLEAN 145 
#define  SD_BUS_TYPE_BYTE 144 
#define  SD_BUS_TYPE_DICT_ENTRY 143 
#define  SD_BUS_TYPE_DICT_ENTRY_BEGIN 142 
#define  SD_BUS_TYPE_DOUBLE 141 
#define  SD_BUS_TYPE_INT16 140 
#define  SD_BUS_TYPE_INT32 139 
#define  SD_BUS_TYPE_INT64 138 
#define  SD_BUS_TYPE_OBJECT_PATH 137 
#define  SD_BUS_TYPE_SIGNATURE 136 
#define  SD_BUS_TYPE_STRING 135 
#define  SD_BUS_TYPE_STRUCT 134 
#define  SD_BUS_TYPE_STRUCT_BEGIN 133 
#define  SD_BUS_TYPE_UINT16 132 
#define  SD_BUS_TYPE_UINT32 131 
#define  SD_BUS_TYPE_UINT64 130 
#define  SD_BUS_TYPE_UNIX_FD 129 
#define  SD_BUS_TYPE_VARIANT 128 

int bus_type_get_alignment(char c) {

        switch (c) {
        case SD_BUS_TYPE_BYTE:
        case SD_BUS_TYPE_SIGNATURE:
        case SD_BUS_TYPE_VARIANT:
                return 1;

        case SD_BUS_TYPE_INT16:
        case SD_BUS_TYPE_UINT16:
                return 2;

        case SD_BUS_TYPE_BOOLEAN:
        case SD_BUS_TYPE_INT32:
        case SD_BUS_TYPE_UINT32:
        case SD_BUS_TYPE_STRING:
        case SD_BUS_TYPE_OBJECT_PATH:
        case SD_BUS_TYPE_ARRAY:
        case SD_BUS_TYPE_UNIX_FD:
                return 4;

        case SD_BUS_TYPE_INT64:
        case SD_BUS_TYPE_UINT64:
        case SD_BUS_TYPE_DOUBLE:
        case SD_BUS_TYPE_STRUCT:
        case SD_BUS_TYPE_STRUCT_BEGIN:
        case SD_BUS_TYPE_DICT_ENTRY:
        case SD_BUS_TYPE_DICT_ENTRY_BEGIN:
                return 8;
        }

        return -EINVAL;
}