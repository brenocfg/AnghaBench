#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int def_char; } ;
struct sbcs_table {unsigned char* uni2cp_low; unsigned short* uni2cp_high; TYPE_1__ info; } ;
typedef  int WCHAR ;

/* Variables and functions */
 int WC_COMPOSITECHECK ; 
 int WC_DEFAULTCHAR ; 
 int WC_DISCARDNS ; 
 scalar_t__ is_valid_sbcs_mapping (struct sbcs_table const*,int,int,char) ; 
 int wine_compose (int const*) ; 

__attribute__((used)) static int wcstombs_sbcs_slow( const struct sbcs_table *table, int flags,
                               const WCHAR *src, unsigned int srclen,
                               char *dst, unsigned int dstlen,
                               const char *defchar, int *used )
{
    const unsigned char  * const uni2cp_low = table->uni2cp_low;
    const unsigned short * const uni2cp_high = table->uni2cp_high;
    unsigned char def;
    unsigned int len;
    int tmp;
    WCHAR composed;

    if (!defchar)
        def = table->info.def_char & 0xff;
    else
        def = *defchar;

    if (!used) used = &tmp;  /* avoid checking on every char */
    *used = 0;

    for (len = dstlen; srclen && len; dst++, len--, src++, srclen--)
    {
        WCHAR wch = *src;

        if ((flags & WC_COMPOSITECHECK) && (srclen > 1) && (composed = wine_compose(src)))
        {
            /* now check if we can use the composed char */
            *dst = uni2cp_low[uni2cp_high[composed >> 8] + (composed & 0xff)];
            if (is_valid_sbcs_mapping( table, flags, composed, *dst ))
            {
                /* we have a good mapping, use it */
                src++;
                srclen--;
                continue;
            }
            /* no mapping for the composed char, check the other flags */
            if (flags & WC_DEFAULTCHAR) /* use the default char instead */
            {
                *dst = def;
                *used = 1;
                src++;  /* skip the non-spacing char */
                srclen--;
                continue;
            }
            if (flags & WC_DISCARDNS) /* skip the second char of the composition */
            {
                src++;
                srclen--;
            }
            /* WC_SEPCHARS is the default */
        }

        *dst = uni2cp_low[uni2cp_high[wch >> 8] + (wch & 0xff)];
        if (!is_valid_sbcs_mapping( table, flags, wch, *dst ))
        {
            *dst = def;
            *used = 1;
        }
    }
    if (srclen) return -1;  /* overflow */
    return dstlen - len;
}