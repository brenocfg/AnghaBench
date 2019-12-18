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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 size_t hpack_encode_str_raw (int /*<<< orphan*/ *,size_t,char const*) ; 
 size_t hpack_encode_str_raw_lower (int /*<<< orphan*/ *,size_t,char const*) ; 

size_t hpack_encode_hdr_neverindex(uint8_t *restrict buf, size_t size,
                                   const char *name, const char *value)
{
    size_t ret = 1, val;

    if (size > 0)
    {
        *(buf++) = 0x10;
        size--;
    }

    val = hpack_encode_str_raw_lower(buf, size, name);
    if (size >= val)
    {
        buf += val;
        size -= val;
    }
    else
        size = 0;
    ret += val;

    val = hpack_encode_str_raw(buf, size, value);
    if (size >= val)
    {
        buf += val;
        size -= val;
    }
    else
        size = 0;
    ret += val;

    return ret;
}