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
struct TYPE_2__ {unsigned short def_char; } ;
struct dbcs_table {unsigned char* cp2uni_leadbytes; scalar_t__* cp2uni; TYPE_1__ info; } ;
typedef  scalar_t__ WCHAR ;

/* Variables and functions */
 int WC_NO_BEST_FIT_CHARS ; 

__attribute__((used)) static inline int is_valid_dbcs_mapping( const struct dbcs_table *table, int flags,
                                         WCHAR wch, unsigned short ch )
{
    if ((flags & WC_NO_BEST_FIT_CHARS) || ch == table->info.def_char)
    {
        /* check if char maps back to the same Unicode value */
        if (ch & 0xff00)
        {
            unsigned char off = table->cp2uni_leadbytes[ch >> 8];
            return (table->cp2uni[(off << 8) + (ch & 0xff)] == wch);
        }
        return (table->cp2uni[ch & 0xff] == wch);
    }
    return 1;
}