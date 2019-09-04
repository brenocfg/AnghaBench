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
struct sbcs_table {int* cp2uni_glyphs; int* cp2uni; unsigned char* uni2cp_low; int const* uni2cp_high; TYPE_1__ info; } ;
typedef  int WCHAR ;

/* Variables and functions */
 int MB_USEGLYPHCHARS ; 
 scalar_t__ is_private_use_area_char (int const) ; 

__attribute__((used)) static inline int check_invalid_chars_sbcs( const struct sbcs_table *table, int flags,
                                            const unsigned char *src, unsigned int srclen )
{
    const WCHAR * const cp2uni = (flags & MB_USEGLYPHCHARS) ? table->cp2uni_glyphs : table->cp2uni;
    const WCHAR def_unicode_char = table->info.def_unicode_char;
    const unsigned char def_char = table->uni2cp_low[table->uni2cp_high[def_unicode_char >> 8]
                                                     + (def_unicode_char & 0xff)];
    while (srclen)
    {
        if ((cp2uni[*src] == def_unicode_char && *src != def_char) ||
            is_private_use_area_char(cp2uni[*src])) break;
        src++;
        srclen--;
    }
    return srclen;
}