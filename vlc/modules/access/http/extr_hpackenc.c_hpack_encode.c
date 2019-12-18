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
 size_t hpack_encode_hdr_neverindex (int /*<<< orphan*/ *,size_t,char const* const,char const* const) ; 

size_t hpack_encode(uint8_t *restrict buf, size_t size,
                    const char *const headers[][2], unsigned count)
{
    size_t ret = 0;

    while (count > 0)
    {
        size_t val = hpack_encode_hdr_neverindex(buf, size, headers[0][0],
                                                 headers[0][1]);
        if (size >= val)
        {
            buf += val;
            size -= val;
        }
        else
            size = 0;

        ret += val;
        headers++;
        count--;
    }
    return ret;
}