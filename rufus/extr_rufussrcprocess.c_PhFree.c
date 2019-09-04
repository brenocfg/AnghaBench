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
typedef  int /*<<< orphan*/  PVOID ;

/* Variables and functions */
 int /*<<< orphan*/  Ntdll ; 
 int /*<<< orphan*/  PF_INIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PhHeapHandle ; 
 int /*<<< orphan*/  RtlFreeHeap ; 
 int /*<<< orphan*/  pfRtlFreeHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VOID PhFree(PVOID Memory)
{
	PF_INIT(RtlFreeHeap, Ntdll);

	if (pfRtlFreeHeap != NULL)
		pfRtlFreeHeap(PhHeapHandle, 0, Memory);
}