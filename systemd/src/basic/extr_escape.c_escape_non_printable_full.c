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
 char* utf8_escape_non_printable_full (char const*,size_t) ; 
 char* xescape_full (char const*,char*,size_t,int) ; 

char *escape_non_printable_full(const char *str, size_t console_width, bool eight_bit) {
        if (eight_bit)
                return xescape_full(str, "", console_width, true);
        else
                return utf8_escape_non_printable_full(str, console_width);
}