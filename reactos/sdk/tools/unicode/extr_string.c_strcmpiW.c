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
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int tolowerW (int /*<<< orphan*/  const) ; 

int strcmpiW( const WCHAR *str1, const WCHAR *str2 )
{
    for (;;)
    {
        int ret = tolowerW(*str1) - tolowerW(*str2);
        if (ret || !*str1) return ret;
        str1++;
        str2++;
    }
}