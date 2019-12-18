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
typedef  scalar_t__* PBYTE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */

__attribute__((used)) static __inline void
_FixStringA(PBYTE String, DWORD cbString)
{
    const PBYTE pLastCharacter = &String[cbString / sizeof(BYTE) - 1];
    PBYTE p = String;

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