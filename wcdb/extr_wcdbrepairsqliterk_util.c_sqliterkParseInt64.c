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
typedef  int uint32_t ;
typedef  int int8_t ;
typedef  int int64_t ;

/* Variables and functions */
 int SQLITERK_MISUSE ; 
 int SQLITERK_OK ; 

int sqliterkParseInt64(const unsigned char *data,
                       int offset,
                       int length,
                       int64_t *value)
{
    if (!data || !value)
        return SQLITERK_MISUSE;

    const unsigned char *p = data + offset;
    int64_t out;

    switch (length) {
        case 1:
            out = (int8_t) p[0];
            break;
        case 2:
            out = (((int8_t) p[0]) * 256) | p[1];
            break;
        case 3:
            out = (((int8_t) p[0]) * 65536) | (p[1] << 8) | p[2];
            break;
        case 4:
            out = (((int8_t) p[0]) * 16777216) | (p[1] << 16) | (p[2] << 8) |
                  p[3];
            break;
        case 6:
            out = (((int8_t) p[0]) * 256) | p[1];
            out *= ((int64_t) 1) << 32;
            out +=
                (((uint32_t) p[2]) << 24) | (p[3] << 16) | (p[4] << 8) | p[5];
            break;
        case 8:
            out = (((int8_t) p[0]) * 16777216) | (p[1] << 16) | (p[2] << 8) |
                  p[3];
            out *= ((int64_t) 1) << 32;
            out +=
                (((uint32_t) p[4]) << 24) | (p[5] << 16) | (p[6] << 8) | p[7];
            break;
        default:
            return SQLITERK_MISUSE;
    }

    *value = out;
    return SQLITERK_OK;
}