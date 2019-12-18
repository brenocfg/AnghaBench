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

/* Variables and functions */

int _ismbcgraph(unsigned int ch)
{
    //wchar_t wch = msvcrt_mbc_to_wc( ch );
    //return (get_char_typeW( wch ) & (C1_UPPER | C1_LOWER | C1_DIGIT | C1_PUNCT | C1_ALPHA));
    return 0;
}