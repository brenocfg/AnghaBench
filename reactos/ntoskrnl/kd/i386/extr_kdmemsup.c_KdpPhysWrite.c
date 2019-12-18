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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  ULONG_PTR ;
typedef  void* ULONGLONG ;
typedef  void** PUSHORT ;
typedef  void** PULONGLONG ;
typedef  void** PULONG ;
typedef  void** PUCHAR ;
typedef  int LONG ;

/* Variables and functions */
 int /*<<< orphan*/  KdpPhysMap (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static
VOID
KdpPhysWrite(ULONG_PTR PhysAddr, LONG Len, ULONGLONG Value)
{
    ULONG_PTR Addr;

    Addr = KdpPhysMap(PhysAddr, Len);

    switch (Len)
    {
    case 8:
        *((PULONGLONG)Addr) = Value;
        break;
    case 4:
        *((PULONG)Addr) = Value;
        break;
    case 2:
        *((PUSHORT)Addr) = Value;
        break;
    case 1:
        *((PUCHAR)Addr) = Value;
        break;
    }
}