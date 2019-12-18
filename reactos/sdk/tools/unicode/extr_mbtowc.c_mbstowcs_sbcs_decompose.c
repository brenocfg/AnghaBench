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
 unsigned int wine_decompose (int /*<<< orphan*/  const,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int mbstowcs_sbcs_decompose( const struct sbcs_table *table, int flags,
                                    const unsigned char *src, unsigned int srclen,
                                    WCHAR *dst, unsigned int dstlen )
{
    const WCHAR * const cp2uni = (flags & MB_USEGLYPHCHARS) ? table->cp2uni_glyphs : table->cp2uni;
    unsigned int len;

    if (!dstlen)  /* compute length */
    {
        WCHAR dummy[4]; /* no decomposition is larger than 4 chars */
        for (len = 0; srclen; srclen--, src++)
            len += wine_decompose( cp2uni[*src], dummy, 4 );
        return len;
    }

    for (len = dstlen; srclen && len; srclen--, src++)
    {
        unsigned int res = wine_decompose( cp2uni[*src], dst, len );
        if (!res) break;
        len -= res;
        dst += res;
    }
    if (srclen) return -1;  /* overflow */
    return dstlen - len;
}