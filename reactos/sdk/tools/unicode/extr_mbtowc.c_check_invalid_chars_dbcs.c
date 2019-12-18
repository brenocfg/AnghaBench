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
struct TYPE_2__ {int def_unicode_char; } ;
struct dbcs_table {int* cp2uni; unsigned char* cp2uni_leadbytes; unsigned short* uni2cp_low; int const* uni2cp_high; TYPE_1__ info; } ;
typedef  int WCHAR ;

/* Variables and functions */
 scalar_t__ is_private_use_area_char (int const) ; 

__attribute__((used)) static inline int check_invalid_chars_dbcs( const struct dbcs_table *table,
                                            const unsigned char *src, unsigned int srclen )
{
    const WCHAR * const cp2uni = table->cp2uni;
    const unsigned char * const cp2uni_lb = table->cp2uni_leadbytes;
    const WCHAR def_unicode_char = table->info.def_unicode_char;
    const unsigned short def_char = table->uni2cp_low[table->uni2cp_high[def_unicode_char >> 8]
                                                      + (def_unicode_char & 0xff)];
    while (srclen)
    {
        unsigned char off = cp2uni_lb[*src];
        if (off)  /* multi-byte char */
        {
            if (srclen == 1) break;  /* partial char, error */
            if (cp2uni[(off << 8) + src[1]] == def_unicode_char &&
                ((src[0] << 8) | src[1]) != def_char) break;
            src++;
            srclen--;
        }
        else if ((cp2uni[*src] == def_unicode_char && *src != def_char) ||
                 is_private_use_area_char(cp2uni[*src])) break;
        src++;
        srclen--;
    }
    return srclen;
}