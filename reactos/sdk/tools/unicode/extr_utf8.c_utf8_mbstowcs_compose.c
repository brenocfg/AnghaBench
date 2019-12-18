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
typedef  char WCHAR ;

/* Variables and functions */
 int MB_ERR_INVALID_CHARS ; 
 unsigned int decode_utf8_char (unsigned char,char const**,char const*) ; 
 int get_length_mbs_utf8_compose (int,char const*,int) ; 
 char wine_compose (char*) ; 

__attribute__((used)) static int utf8_mbstowcs_compose( int flags, const char *src, int srclen, WCHAR *dst, int dstlen )
{
    unsigned int res;
    const char *srcend = src + srclen;
    WCHAR composed[2];
    WCHAR *dstend = dst + dstlen;

    if (!dstlen) return get_length_mbs_utf8_compose( flags, src, srclen );

    composed[0] = 0;
    while (src < srcend)
    {
        unsigned char ch = *src++;
        if (ch < 0x80)  /* special fast case for 7-bit ASCII */
        {
            if (dst >= dstend) return -1;  /* overflow */
            *dst++ = composed[0] = ch;
            continue;
        }
        if ((res = decode_utf8_char( ch, &src, srcend )) <= 0xffff)
        {
            if (composed[0])
            {
                composed[1] = res;
                if ((composed[0] = wine_compose( composed )))
                {
                    dst[-1] = composed[0];
                    continue;
                }
            }
            if (dst >= dstend) return -1;  /* overflow */
            *dst++ = composed[0] = res;
        }
        else if (res <= 0x10ffff) /* we need surrogates */
        {
            if (dst >= dstend - 1) return -1;  /* overflow */
            res -= 0x10000;
            *dst++ = 0xd800 | (res >> 10);
            *dst++ = 0xdc00 | (res & 0x3ff);
            composed[0] = 0;  /* no composition for surrogates */
        }
        else if (flags & MB_ERR_INVALID_CHARS) return -2;  /* bad char */
        /* otherwise ignore it */
    }
    return dstlen - (dstend - dst);
}