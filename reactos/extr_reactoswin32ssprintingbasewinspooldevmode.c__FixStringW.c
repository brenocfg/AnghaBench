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
typedef  scalar_t__* PWSTR ;
typedef  int DWORD ;

/* Variables and functions */

__attribute__((used)) static __inline void
_FixStringW(PWSTR String, DWORD cbString)
{
    const PWSTR pLastCharacter = &String[cbString / sizeof(WCHAR) - 1];
    PWSTR p = String;

    while (*p)
    {
        if (p == pLastCharacter)
        {
            *p = 0;
            break;
        }

        p++;
    }
}