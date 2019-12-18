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
struct TYPE_2__ {scalar_t__ def_char; } ;
struct sbcs_table {scalar_t__* cp2uni; TYPE_1__ info; } ;
typedef  scalar_t__ WCHAR ;

/* Variables and functions */
 int WC_NO_BEST_FIT_CHARS ; 

__attribute__((used)) static inline int is_valid_sbcs_mapping( const struct sbcs_table *table, int flags,
                                         WCHAR wch, unsigned char ch )
{
    if ((flags & WC_NO_BEST_FIT_CHARS) || ch == (unsigned char)table->info.def_char)
        return (table->cp2uni[ch] == wch);
    return 1;
}