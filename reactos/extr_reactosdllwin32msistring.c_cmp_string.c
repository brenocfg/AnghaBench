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
typedef  scalar_t__ WCHAR ;

/* Variables and functions */

__attribute__((used)) static inline int cmp_string( const WCHAR *str1, int len1, const WCHAR *str2, int len2 )
{
    if (len1 < len2) return -1;
    else if (len1 > len2) return 1;
    while (len1)
    {
        if (*str1 == *str2) { str1++; str2++; }
        else return *str1 - *str2;
        len1--;
    }
    return 0;
}