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
 int ALIGN_TO (int,int) ; 
 int EINVAL ; 
#define  SD_BUS_TYPE_ARRAY 144 
#define  SD_BUS_TYPE_BOOLEAN 143 
#define  SD_BUS_TYPE_BYTE 142 
#define  SD_BUS_TYPE_DICT_ENTRY_BEGIN 141 
#define  SD_BUS_TYPE_DOUBLE 140 
#define  SD_BUS_TYPE_INT16 139 
#define  SD_BUS_TYPE_INT32 138 
#define  SD_BUS_TYPE_INT64 137 
#define  SD_BUS_TYPE_OBJECT_PATH 136 
#define  SD_BUS_TYPE_SIGNATURE 135 
#define  SD_BUS_TYPE_STRING 134 
#define  SD_BUS_TYPE_STRUCT_BEGIN 133 
#define  SD_BUS_TYPE_UINT16 132 
#define  SD_BUS_TYPE_UINT32 131 
#define  SD_BUS_TYPE_UINT64 130 
#define  SD_BUS_TYPE_UNIX_FD 129 
#define  SD_BUS_TYPE_VARIANT 128 
 int /*<<< orphan*/  assert_not_reached (char*) ; 
 int bus_gvariant_get_alignment (char const*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int signature_element_length (char const*,size_t*) ; 

int bus_gvariant_get_size(const char *signature) {
        const char *p;
        int sum = 0, r;

        /* For fixed size structs. Fails for variable size structs. */

        p = signature;
        while (*p != 0) {
                size_t n;

                r = signature_element_length(p, &n);
                if (r < 0)
                        return r;
                else {
                        char t[n+1];

                        memcpy(t, p, n);
                        t[n] = 0;

                        r = bus_gvariant_get_alignment(t);
                        if (r < 0)
                                return r;

                        sum = ALIGN_TO(sum, r);
                }

                switch (*p) {

                case SD_BUS_TYPE_BOOLEAN:
                case SD_BUS_TYPE_BYTE:
                        sum += 1;
                        break;

                case SD_BUS_TYPE_INT16:
                case SD_BUS_TYPE_UINT16:
                        sum += 2;
                        break;

                case SD_BUS_TYPE_INT32:
                case SD_BUS_TYPE_UINT32:
                case SD_BUS_TYPE_UNIX_FD:
                        sum += 4;
                        break;

                case SD_BUS_TYPE_INT64:
                case SD_BUS_TYPE_UINT64:
                case SD_BUS_TYPE_DOUBLE:
                        sum += 8;
                        break;

                case SD_BUS_TYPE_STRUCT_BEGIN:
                case SD_BUS_TYPE_DICT_ENTRY_BEGIN: {
                        if (n == 2) {
                                /* unary type () has fixed size of 1 */
                                r = 1;
                        } else {
                                char t[n-1];

                                memcpy(t, p + 1, n - 2);
                                t[n - 2] = 0;

                                r = bus_gvariant_get_size(t);
                                if (r < 0)
                                        return r;
                        }

                        sum += r;
                        break;
                }

                case SD_BUS_TYPE_STRING:
                case SD_BUS_TYPE_OBJECT_PATH:
                case SD_BUS_TYPE_SIGNATURE:
                case SD_BUS_TYPE_ARRAY:
                case SD_BUS_TYPE_VARIANT:
                        return -EINVAL;

                default:
                        assert_not_reached("Unknown signature type");
                }

                p += n;
        }

        r = bus_gvariant_get_alignment(signature);
        if (r < 0)
                return r;

        return ALIGN_TO(sum, r);
}