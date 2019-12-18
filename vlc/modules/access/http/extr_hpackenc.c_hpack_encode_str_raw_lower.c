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
typedef  char uint8_t ;

/* Variables and functions */
 size_t hpack_encode_int (char*,size_t,size_t,int) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static size_t hpack_encode_str_raw_lower(uint8_t *restrict buf, size_t size,
                                         const char *str)
{
    size_t len = strlen(str);

    if (size > 0)
        *buf = 0;

    size_t ret = hpack_encode_int(buf, size, len, 7);
    if (ret < size)
    {
        buf += ret;
        size -= ret;

        for (size_t i = 0; i < len && i < size; i++)
            if (str[i] < 'A' || str[i] > 'Z')
                buf[i] = str[i];
            else
                buf[i] = str[i] - 'A' + 'a';
    }
    ret += len;
    return ret;
}