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
typedef  scalar_t__ PCWSTR ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 scalar_t__ wcscmp (scalar_t__,scalar_t__) ; 

__attribute__((used)) static __inline BOOL
_EqualStrings(PCWSTR pwszA, PCWSTR pwszB)
{
    if (!pwszA && !pwszB)
        return TRUE;

    if (pwszA && !pwszB)
        return FALSE;

    if (!pwszA && pwszB)
        return FALSE;

    return (wcscmp(pwszA, pwszB) == 0);
}