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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assert_not_reached (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int signature_element_length (char const*,size_t*) ; 

int bus_gvariant_get_alignment(const char *signature) {
        size_t alignment = 1;
        const char *p;
        int r;

        p = signature;
        while (*p != 0 && alignment < 8) {
                size_t n;
                int a;

                r = signature_element_length(p, &n);
                if (r < 0)
                        return r;

                switch (*p) {

                case SD_BUS_TYPE_BYTE:
                case SD_BUS_TYPE_BOOLEAN:
                case SD_BUS_TYPE_STRING:
                case SD_BUS_TYPE_OBJECT_PATH:
                case SD_BUS_TYPE_SIGNATURE:
                        a = 1;
                        break;

                case SD_BUS_TYPE_INT16:
                case SD_BUS_TYPE_UINT16:
                        a = 2;
                        break;

                case SD_BUS_TYPE_INT32:
                case SD_BUS_TYPE_UINT32:
                case SD_BUS_TYPE_UNIX_FD:
                        a = 4;
                        break;

                case SD_BUS_TYPE_INT64:
                case SD_BUS_TYPE_UINT64:
                case SD_BUS_TYPE_DOUBLE:
                case SD_BUS_TYPE_VARIANT:
                        a = 8;
                        break;

                case SD_BUS_TYPE_ARRAY: {
                        char t[n];

                        memcpy(t, p + 1, n - 1);
                        t[n - 1] = 0;

                        a = bus_gvariant_get_alignment(t);
                        break;
                }

                case SD_BUS_TYPE_STRUCT_BEGIN:
                case SD_BUS_TYPE_DICT_ENTRY_BEGIN: {
                        char t[n-1];

                        memcpy(t, p + 1, n - 2);
                        t[n - 2] = 0;

                        a = bus_gvariant_get_alignment(t);
                        break;
                }

                default:
                        assert_not_reached("Unknown signature type");
                }

                if (a < 0)
                        return a;

                assert(a > 0 && a <= 8);
                if ((size_t) a > alignment)
                        alignment = (size_t) a;

                p += n;
        }

        return alignment;
}