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
 unsigned int wine_decompose (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int mbstowcs_dbcs_decompose( const struct dbcs_table *table,
                                    const unsigned char *src, unsigned int srclen,
                                    WCHAR *dst, unsigned int dstlen )
{
    const WCHAR * const cp2uni = table->cp2uni;
    const unsigned char * const cp2uni_lb = table->cp2uni_leadbytes;
    unsigned int len, res;
    WCHAR ch;

    if (!dstlen)  /* compute length */
    {
        WCHAR dummy[4]; /* no decomposition is larger than 4 chars */
        for (len = 0; srclen; srclen--, src++)
        {
            unsigned char off = cp2uni_lb[*src];
            if (off && srclen > 1 && src[1])
            {
                src++;
                srclen--;
                ch = cp2uni[(off << 8) + *src];
            }
            else ch = cp2uni[*src];
            len += wine_decompose( ch, dummy, 4 );
        }
        return len;
    }

    for (len = dstlen; srclen && len; srclen--, src++)
    {
        unsigned char off = cp2uni_lb[*src];
        if (off && srclen > 1 && src[1])
        {
            src++;
            srclen--;
            ch = cp2uni[(off << 8) + *src];
        }
        else ch = cp2uni[*src];
        if (!(res = wine_decompose( ch, dst, len ))) break;
        dst += res;
        len -= res;
    }
    if (srclen) return -1;  /* overflow */
    return dstlen - len;
}