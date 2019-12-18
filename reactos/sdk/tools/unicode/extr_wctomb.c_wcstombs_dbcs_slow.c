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
 int WC_COMPOSITECHECK ; 
 int WC_DEFAULTCHAR ; 
 int WC_DISCARDNS ; 
 int get_defchar_dbcs (struct dbcs_table const*,char const*) ; 
 scalar_t__ is_valid_dbcs_mapping (struct dbcs_table const*,int,int,unsigned short) ; 
 int wine_compose (int const*) ; 

__attribute__((used)) static int wcstombs_dbcs_slow( const struct dbcs_table *table, int flags,
                               const WCHAR *src, unsigned int srclen,
                               char *dst, unsigned int dstlen,
                               const char *defchar, int *used )
{
    const unsigned short * const uni2cp_low = table->uni2cp_low;
    const unsigned short * const uni2cp_high = table->uni2cp_high;
    WCHAR defchar_value = get_defchar_dbcs( table, defchar );
    WCHAR composed;
    int len, tmp;

    if (!used) used = &tmp;  /* avoid checking on every char */
    *used = 0;

    for (len = dstlen; srclen && len; len--, srclen--, src++)
    {
        unsigned short res;
        WCHAR wch = *src;

        if ((flags & WC_COMPOSITECHECK) && (srclen > 1) && (composed = wine_compose(src)))
        {
            /* now check if we can use the composed char */
            res = uni2cp_low[uni2cp_high[composed >> 8] + (composed & 0xff)];

            if (is_valid_dbcs_mapping( table, flags, composed, res ))
            {
                /* we have a good mapping for the composed char, use it */
                src++;
                srclen--;
                goto output_char;
            }
            /* no mapping for the composed char, check the other flags */
            if (flags & WC_DEFAULTCHAR) /* use the default char instead */
            {
                res = defchar_value;
                *used = 1;
                src++;  /* skip the non-spacing char */
                srclen--;
                goto output_char;
            }
            if (flags & WC_DISCARDNS) /* skip the second char of the composition */
            {
                src++;
                srclen--;
            }
            /* WC_SEPCHARS is the default */
        }

        res = uni2cp_low[uni2cp_high[wch >> 8] + (wch & 0xff)];
        if (!is_valid_dbcs_mapping( table, flags, wch, res ))
        {
            res = defchar_value;
            *used = 1;
        }

    output_char:
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