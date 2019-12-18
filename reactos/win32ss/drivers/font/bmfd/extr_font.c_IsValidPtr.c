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
typedef  scalar_t__ ULONG_PTR ;
typedef  scalar_t__ ULONG ;
typedef  scalar_t__ PVOID ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static
BOOLEAN
IsValidPtr(
    PVOID p,
    ULONG cjSize,
    PVOID pStart,
    PVOID pEnd,
    ULONG cjAlign)
{
    if ((ULONG_PTR)p < (ULONG_PTR)pStart ||
        (ULONG_PTR)p + cjSize >= (ULONG_PTR)pEnd ||
        (ULONG_PTR)p & (cjAlign -1))
    {
        return FALSE;
    }
    return TRUE;
}