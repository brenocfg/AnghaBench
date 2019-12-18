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
typedef  int uint8_t ;
typedef  int int64_t ;

/* Variables and functions */
 int INT64_MAX ; 

__attribute__((used)) static inline int64_t read_utf8(const uint8_t *p_buf, int *pi_read)
{
    /* Max coding bits is 56 - 8 */
    /* Value max precision is 36 bits */
    int64_t i_result = 0;
    unsigned i;

    if (!(p_buf[0] & 0x80)) { /* 0xxxxxxx */
        i_result = p_buf[0];
        i = 0;
    } else if (p_buf[0] & 0xC0 && !(p_buf[0] & 0x20)) { /* 110xxxxx */
        i_result = p_buf[0] & 0x1F;
        i = 1;
    } else if (p_buf[0] & 0xE0 && !(p_buf[0] & 0x10)) { /* 1110xxxx */
        i_result = p_buf[0] & 0x0F;
        i = 2;
    } else if (p_buf[0] & 0xF0 && !(p_buf[0] & 0x08)) { /* 11110xxx */
        i_result = p_buf[0] & 0x07;
        i = 3;
    } else if (p_buf[0] & 0xF8 && !(p_buf[0] & 0x04)) { /* 111110xx */
        i_result = p_buf[0] & 0x03;
        i = 4;
    } else if (p_buf[0] & 0xFC && !(p_buf[0] & 0x02)) { /* 1111110x */
        i_result = p_buf[0] & 0x01;
        i = 5;
    } else if (p_buf[0] & 0xFE && !(p_buf[0] & 0x01)) { /* 11111110 */
        i_result = 0;
        i = 6;
    } else {
        return INT64_MAX;
    }

    for (unsigned j = 1; j <= i; j++) {
        if (!(p_buf[j] & 0x80) || (p_buf[j] & 0x40)) { /* 10xxxxxx */
            return INT64_MAX;
        }
        i_result <<= 6;
        i_result |= (p_buf[j] & 0x3F);
    }

    *pi_read = i;
    return i_result;
}