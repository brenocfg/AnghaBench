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
struct dbcs_table {unsigned short* uni2cp_low; unsigned short* uni2cp_high; } ;
typedef  int WCHAR ;

/* Variables and functions */

__attribute__((used)) static inline int wcstombs_dbcs( const struct dbcs_table *table,
                                 const WCHAR *src, unsigned int srclen,
                                 char *dst, unsigned int dstlen )
{
    const unsigned short * const uni2cp_low = table->uni2cp_low;
    const unsigned short * const uni2cp_high = table->uni2cp_high;
    int len;

    for (len = dstlen; srclen && len; len--, srclen--, src++)
    {
        unsigned short res = uni2cp_low[uni2cp_high[*src >> 8] + (*src & 0xff)];
        if (res & 0xff00)
        {
            if (len == 1) break;  /* do not output a partial char */
            len--;
            *dst++ = res >> 8;
        }
        *dst++ = (char)res;
    }
    if (srclen) return -1;  /* overflow */
    return dstlen - len;
}