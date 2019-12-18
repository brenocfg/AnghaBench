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
struct dbcs_table {unsigned char* cp2uni_leadbytes; int /*<<< orphan*/ * cp2uni; } ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int get_length_dbcs (struct dbcs_table const*,unsigned char const*,unsigned int) ; 

__attribute__((used)) static inline int mbstowcs_dbcs( const struct dbcs_table *table,
                                 const unsigned char *src, unsigned int srclen,
                                 WCHAR *dst, unsigned int dstlen )
{
    const WCHAR * const cp2uni = table->cp2uni;
    const unsigned char * const cp2uni_lb = table->cp2uni_leadbytes;
    unsigned int len;

    if (!dstlen) return get_length_dbcs( table, src, srclen );

    for (len = dstlen; srclen && len; len--, srclen--, src++, dst++)
    {
        unsigned char off = cp2uni_lb[*src];
        if (off && srclen > 1 && src[1])
        {
            src++;
            srclen--;
            *dst = cp2uni[(off << 8) + *src];
        }
        else *dst = cp2uni[*src];
    }
    if (srclen) return -1;  /* overflow */
    return dstlen - len;
}