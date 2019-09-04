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
struct sbcs_table {int /*<<< orphan*/ * cp2uni; int /*<<< orphan*/ * cp2uni_glyphs; } ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int MB_USEGLYPHCHARS ; 

__attribute__((used)) static inline int mbstowcs_sbcs( const struct sbcs_table *table, int flags,
                                 const unsigned char *src, unsigned int srclen,
                                 WCHAR *dst, unsigned int dstlen )
{
    const WCHAR * const cp2uni = (flags & MB_USEGLYPHCHARS) ? table->cp2uni_glyphs : table->cp2uni;
    int ret = srclen;

    if (dstlen < srclen)
    {
        /* buffer too small: fill it up to dstlen and return error */
        srclen = dstlen;
        ret = -1;
    }

    for (;;)
    {
        switch(srclen)
        {
        default:
        case 16: dst[15] = cp2uni[src[15]];
        case 15: dst[14] = cp2uni[src[14]];
        case 14: dst[13] = cp2uni[src[13]];
        case 13: dst[12] = cp2uni[src[12]];
        case 12: dst[11] = cp2uni[src[11]];
        case 11: dst[10] = cp2uni[src[10]];
        case 10: dst[9]  = cp2uni[src[9]];
        case 9:  dst[8]  = cp2uni[src[8]];
        case 8:  dst[7]  = cp2uni[src[7]];
        case 7:  dst[6]  = cp2uni[src[6]];
        case 6:  dst[5]  = cp2uni[src[5]];
        case 5:  dst[4]  = cp2uni[src[4]];
        case 4:  dst[3]  = cp2uni[src[3]];
        case 3:  dst[2]  = cp2uni[src[2]];
        case 2:  dst[1]  = cp2uni[src[1]];
        case 1:  dst[0]  = cp2uni[src[0]];
        case 0: break;
        }
        if (srclen < 16) return ret;
        dst += 16;
        src += 16;
        srclen -= 16;
    }
}