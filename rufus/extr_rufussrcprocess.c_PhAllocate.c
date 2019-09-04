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
typedef  int /*<<< orphan*/  SIZE_T ;
typedef  int /*<<< orphan*/ * PVOID ;

/* Variables and functions */
 int /*<<< orphan*/  Ntdll ; 
 int /*<<< orphan*/  PF_INIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PhHeapHandle ; 
 int /*<<< orphan*/  RtlAllocateHeap ; 
 int /*<<< orphan*/ * pfRtlAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PVOID PhAllocate(SIZE_T Size)
{
	PF_INIT(RtlAllocateHeap, Ntdll);
	if (pfRtlAllocateHeap == NULL)
		return NULL;

	return pfRtlAllocateHeap(PhHeapHandle, 0, Size);
}