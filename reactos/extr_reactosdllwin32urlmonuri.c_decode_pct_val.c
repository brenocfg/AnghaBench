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
typedef  char WCHAR ;
typedef  int INT ;

/* Variables and functions */
 int hex_to_int (char const) ; 
 scalar_t__ is_hexdigit (char const) ; 

__attribute__((used)) static WCHAR decode_pct_val(const WCHAR *ptr) {
    WCHAR ret = '\0';

    if(*ptr == '%' && is_hexdigit(*(ptr + 1)) && is_hexdigit(*(ptr + 2))) {
        INT a = hex_to_int(*(ptr + 1));
        INT b = hex_to_int(*(ptr + 2));

        ret = a << 4;
        ret += b;
    }

    return ret;
}