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
typedef  scalar_t__ INT ;

/* Variables and functions */
 scalar_t__ lstrlenW (scalar_t__ const*) ; 

__attribute__((used)) static INT
GetMultiSzLength(const WCHAR *pszz)
{
    INT Len, TotalLen = 0;
    for (;;)
    {
        Len = lstrlenW(pszz);
        TotalLen += Len + 1;
        pszz += Len + 1;
        if (*pszz == 0)
            break;
    }
    ++TotalLen;
    return TotalLen;
}