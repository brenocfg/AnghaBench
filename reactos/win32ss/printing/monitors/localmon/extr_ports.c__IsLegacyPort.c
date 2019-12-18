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
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ _wcsnicmp (int*,int*,int const) ; 

__attribute__((used)) static __inline BOOL
_IsLegacyPort(PCWSTR pwszPortName, PCWSTR pwszPortType)
{
    const DWORD cchPortType = 3;
    PCWSTR p = pwszPortName;

    // The port name must begin with pwszPortType.
    if (_wcsnicmp(p, pwszPortType, cchPortType) != 0)
        return FALSE;

    p += cchPortType;

    // Now an arbitrary number of digits may follow.
    while (*p >= L'0' && *p <= L'9')
        p++;

    // Finally, the legacy port must be terminated by a colon.
    if (*p != ':')
        return FALSE;

    // If this is the end of the string, we have a legacy port.
    p++;
    return (*p == L'\0');
}