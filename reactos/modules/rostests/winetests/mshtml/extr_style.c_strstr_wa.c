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
typedef  scalar_t__* BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  SysFreeString (scalar_t__*) ; 
 scalar_t__* a2bstr (char const*) ; 

__attribute__((used)) static const WCHAR *strstr_wa(const WCHAR *str, const char *suba)
{
    BSTR sub;
    const WCHAR *ret = NULL;
    sub = a2bstr(suba);
    while (*str)
    {
        const WCHAR *p1 = str, *p2 = sub;
        while (*p1 && *p2 && *p1 == *p2) { p1++; p2++; }
        if (!*p2) {ret = str; break;}
        str++;
    }
    SysFreeString(sub);
    return ret;
}