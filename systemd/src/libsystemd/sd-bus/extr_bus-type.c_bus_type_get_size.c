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
#define  SD_BUS_TYPE_BOOLEAN 137 
#define  SD_BUS_TYPE_BYTE 136 
#define  SD_BUS_TYPE_DOUBLE 135 
#define  SD_BUS_TYPE_INT16 134 
#define  SD_BUS_TYPE_INT32 133 
#define  SD_BUS_TYPE_INT64 132 
#define  SD_BUS_TYPE_UINT16 131 
#define  SD_BUS_TYPE_UINT32 130 
#define  SD_BUS_TYPE_UINT64 129 
#define  SD_BUS_TYPE_UNIX_FD 128 

int bus_type_get_size(char c) {

        switch (c) {
        case SD_BUS_TYPE_BYTE:
                return 1;

        case SD_BUS_TYPE_INT16:
        case SD_BUS_TYPE_UINT16:
                return 2;

        case SD_BUS_TYPE_BOOLEAN:
        case SD_BUS_TYPE_INT32:
        case SD_BUS_TYPE_UINT32:
        case SD_BUS_TYPE_UNIX_FD:
                return 4;

        case SD_BUS_TYPE_INT64:
        case SD_BUS_TYPE_UINT64:
        case SD_BUS_TYPE_DOUBLE:
                return 8;
        }

        return -EINVAL;
}