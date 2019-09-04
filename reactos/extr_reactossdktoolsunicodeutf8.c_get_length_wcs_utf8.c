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
typedef  int WCHAR ;

/* Variables and functions */
 int WC_ERR_INVALID_CHARS ; 
 unsigned int get_surrogate_value (int const*,unsigned int) ; 

__attribute__((used)) static inline int get_length_wcs_utf8( int flags, const WCHAR *src, unsigned int srclen )
{
    int len;
    unsigned int val;

    for (len = 0; srclen; srclen--, src++)
    {
        if (*src < 0x80)  /* 0x00-0x7f: 1 byte */
        {
            len++;
            continue;
        }
        if (*src < 0x800)  /* 0x80-0x7ff: 2 bytes */
        {
            len += 2;
            continue;
        }
        if (!(val = get_surrogate_value( src, srclen )))
        {
            if (flags & WC_ERR_INVALID_CHARS) return -2;
            continue;
        }
        if (val < 0x10000)  /* 0x800-0xffff: 3 bytes */
            len += 3;
        else   /* 0x10000-0x10ffff: 4 bytes */
        {
            len += 4;
            src++;
            srclen--;
        }
    }
    return len;
}