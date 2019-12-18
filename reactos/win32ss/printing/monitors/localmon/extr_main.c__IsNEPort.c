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
typedef  int* PCWSTR ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 

__attribute__((used)) static __inline BOOL
_IsNEPort(PCWSTR pwszPortName)
{
    PCWSTR p = pwszPortName;

    // First character needs to be 'N' (uppercase or lowercase)
    if (*p != L'N' && *p != L'n')
        return FALSE;

    // Next character needs to be 'E' (uppercase or lowercase)
    p++;
    if (*p != L'E' && *p != L'e')
        return FALSE;

    // An optional hyphen may follow now.
    p++;
    if (*p == L'-')
        p++;

    // Now an arbitrary number of digits may follow.
    while (*p >= L'0' && *p <= L'9')
        p++;

    // Finally, the virtual Ne port must be terminated by a colon.
    if (*p != ':')
        return FALSE;

    // If this is the end of the string, we have a virtual Ne port.
    p++;
    return (*p == L'\0');
}