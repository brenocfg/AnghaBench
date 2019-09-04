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
typedef  int /*<<< orphan*/  ULONG_PTR ;
typedef  int /*<<< orphan*/  ULONGLONG ;
typedef  int /*<<< orphan*/ * PUSHORT ;
typedef  int /*<<< orphan*/ * PULONGLONG ;
typedef  int /*<<< orphan*/ * PULONG ;
typedef  int /*<<< orphan*/ * PUCHAR ;
typedef  int LONG ;

/* Variables and functions */
 int /*<<< orphan*/  KdpPhysMap (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static
ULONGLONG
KdpPhysRead(ULONG_PTR PhysAddr, LONG Len)
{
    ULONG_PTR Addr;
    ULONGLONG Result = 0;

    Addr = KdpPhysMap(PhysAddr, Len);

    switch (Len)
    {
    case 8:
        Result = *((PULONGLONG)Addr);
        break;
    case 4:
        Result = *((PULONG)Addr);
        break;
    case 2:
        Result = *((PUSHORT)Addr);
        break;
    case 1:
        Result = *((PUCHAR)Addr);
        break;
    }

    return Result;
}