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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 size_t hpack_encode_int (scalar_t__*,size_t,size_t,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static size_t hpack_encode_str_raw(uint8_t *restrict buf, size_t size,
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

        memcpy(buf, str, (len <= size) ? len : size);
    }
    ret += len;
    return ret;
}