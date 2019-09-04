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
typedef  int UINT ;
typedef  scalar_t__* LPWSTR ;

/* Variables and functions */

WCHAR* lstrcpynW(WCHAR* lpString1, const WCHAR* lpString2, int iMaxLength)
{
    LPWSTR d = lpString1;
    const WCHAR* s = lpString2;
    UINT count = iMaxLength;

    while ((count > 1) && *s)
    {
        count--;
        *d++ = *s++;
    }

    if (count)
        *d = 0;

    return lpString1;
}