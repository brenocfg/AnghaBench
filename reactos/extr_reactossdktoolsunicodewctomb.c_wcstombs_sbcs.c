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
struct sbcs_table {unsigned char* uni2cp_low; unsigned short* uni2cp_high; } ;
typedef  int WCHAR ;

/* Variables and functions */

__attribute__((used)) static inline int wcstombs_sbcs( const struct sbcs_table *table,
                                 const WCHAR *src, unsigned int srclen,
                                 char *dst, unsigned int dstlen )
{
    const unsigned char  * const uni2cp_low = table->uni2cp_low;
    const unsigned short * const uni2cp_high = table->uni2cp_high;
    int ret = srclen;

    if (dstlen < srclen)
    {
        /* buffer too small: fill it up to dstlen and return error */
        srclen = dstlen;
        ret = -1;
    }

    while (srclen >= 16)
    {
        dst[0]  = uni2cp_low[uni2cp_high[src[0]  >> 8] + (src[0]  & 0xff)];
        dst[1]  = uni2cp_low[uni2cp_high[src[1]  >> 8] + (src[1]  & 0xff)];
        dst[2]  = uni2cp_low[uni2cp_high[src[2]  >> 8] + (src[2]  & 0xff)];
        dst[3]  = uni2cp_low[uni2cp_high[src[3]  >> 8] + (src[3]  & 0xff)];
        dst[4]  = uni2cp_low[uni2cp_high[src[4]  >> 8] + (src[4]  & 0xff)];
        dst[5]  = uni2cp_low[uni2cp_high[src[5]  >> 8] + (src[5]  & 0xff)];
        dst[6]  = uni2cp_low[uni2cp_high[src[6]  >> 8] + (src[6]  & 0xff)];
        dst[7]  = uni2cp_low[uni2cp_high[src[7]  >> 8] + (src[7]  & 0xff)];
        dst[8]  = uni2cp_low[uni2cp_high[src[8]  >> 8] + (src[8]  & 0xff)];
        dst[9]  = uni2cp_low[uni2cp_high[src[9]  >> 8] + (src[9]  & 0xff)];
        dst[10] = uni2cp_low[uni2cp_high[src[10] >> 8] + (src[10] & 0xff)];
        dst[11] = uni2cp_low[uni2cp_high[src[11] >> 8] + (src[11] & 0xff)];
        dst[12] = uni2cp_low[uni2cp_high[src[12] >> 8] + (src[12] & 0xff)];
        dst[13] = uni2cp_low[uni2cp_high[src[13] >> 8] + (src[13] & 0xff)];
        dst[14] = uni2cp_low[uni2cp_high[src[14] >> 8] + (src[14] & 0xff)];
        dst[15] = uni2cp_low[uni2cp_high[src[15] >> 8] + (src[15] & 0xff)];
        src += 16;
        dst += 16;
        srclen -= 16;
    }

    /* now handle remaining characters */
    src += srclen;
    dst += srclen;
    switch(srclen)
    {
    case 15: dst[-15] = uni2cp_low[uni2cp_high[src[-15] >> 8] + (src[-15] & 0xff)];
    case 14: dst[-14] = uni2cp_low[uni2cp_high[src[-14] >> 8] + (src[-14] & 0xff)];
    case 13: dst[-13] = uni2cp_low[uni2cp_high[src[-13] >> 8] + (src[-13] & 0xff)];
    case 12: dst[-12] = uni2cp_low[uni2cp_high[src[-12] >> 8] + (src[-12] & 0xff)];
    case 11: dst[-11] = uni2cp_low[uni2cp_high[src[-11] >> 8] + (src[-11] & 0xff)];
    case 10: dst[-10] = uni2cp_low[uni2cp_high[src[-10] >> 8] + (src[-10] & 0xff)];
    case 9:  dst[-9]  = uni2cp_low[uni2cp_high[src[-9]  >> 8] + (src[-9]  & 0xff)];
    case 8:  dst[-8]  = uni2cp_low[uni2cp_high[src[-8]  >> 8] + (src[-8]  & 0xff)];
    case 7:  dst[-7]  = uni2cp_low[uni2cp_high[src[-7]  >> 8] + (src[-7]  & 0xff)];
    case 6:  dst[-6]  = uni2cp_low[uni2cp_high[src[-6]  >> 8] + (src[-6]  & 0xff)];
    case 5:  dst[-5]  = uni2cp_low[uni2cp_high[src[-5]  >> 8] + (src[-5]  & 0xff)];
    case 4:  dst[-4]  = uni2cp_low[uni2cp_high[src[-4]  >> 8] + (src[-4]  & 0xff)];
    case 3:  dst[-3]  = uni2cp_low[uni2cp_high[src[-3]  >> 8] + (src[-3]  & 0xff)];
    case 2:  dst[-2]  = uni2cp_low[uni2cp_high[src[-2]  >> 8] + (src[-2]  & 0xff)];
    case 1:  dst[-1]  = uni2cp_low[uni2cp_high[src[-1]  >> 8] + (src[-1]  & 0xff)];
    case 0: break;
    }
    return ret;
}