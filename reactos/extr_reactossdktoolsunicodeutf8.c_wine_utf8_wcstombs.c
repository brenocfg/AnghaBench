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
 int get_length_wcs_utf8 (int,int const*,int) ; 
 unsigned int get_surrogate_value (int const*,int) ; 

int wine_utf8_wcstombs( int flags, const WCHAR *src, int srclen, char *dst, int dstlen )
{
    int len;

    if (!dstlen) return get_length_wcs_utf8( flags, src, srclen );

    for (len = dstlen; srclen; srclen--, src++)
    {
        WCHAR ch = *src;
        unsigned int val;

        if (ch < 0x80)  /* 0x00-0x7f: 1 byte */
        {
            if (!len--) return -1;  /* overflow */
            *dst++ = ch;
            continue;
        }

        if (ch < 0x800)  /* 0x80-0x7ff: 2 bytes */
        {
            if ((len -= 2) < 0) return -1;  /* overflow */
            dst[1] = 0x80 | (ch & 0x3f);
            ch >>= 6;
            dst[0] = 0xc0 | ch;
            dst += 2;
            continue;
        }

        if (!(val = get_surrogate_value( src, srclen )))
        {
            if (flags & WC_ERR_INVALID_CHARS) return -2;
            continue;
        }

        if (val < 0x10000)  /* 0x800-0xffff: 3 bytes */
        {
            if ((len -= 3) < 0) return -1;  /* overflow */
            dst[2] = 0x80 | (val & 0x3f);
            val >>= 6;
            dst[1] = 0x80 | (val & 0x3f);
            val >>= 6;
            dst[0] = 0xe0 | val;
            dst += 3;
        }
        else   /* 0x10000-0x10ffff: 4 bytes */
        {
            if ((len -= 4) < 0) return -1;  /* overflow */
            dst[3] = 0x80 | (val & 0x3f);
            val >>= 6;
            dst[2] = 0x80 | (val & 0x3f);
            val >>= 6;
            dst[1] = 0x80 | (val & 0x3f);
            val >>= 6;
            dst[0] = 0xf0 | val;
            dst += 4;
            src++;
            srclen--;
        }
    }
    return dstlen - len;
}