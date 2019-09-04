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
typedef  int /*<<< orphan*/  SIZE_T ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int /*<<< orphan*/ * PRTL_DEBUG_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_RELEASE ; 
 int /*<<< orphan*/  NtCurrentProcess () ; 
 int /*<<< orphan*/  NtFreeVirtualMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlDestroyQueryDebugBuffer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static VOID
TH32FreeAllocatedResources(PRTL_DEBUG_INFORMATION HeapDebug,
                           PRTL_DEBUG_INFORMATION ModuleDebug,
                           PVOID ProcThrdInfo,
                           SIZE_T ProcThrdInfoSize)
{
  if(HeapDebug != NULL)
  {
    RtlDestroyQueryDebugBuffer(HeapDebug);
  }
  if(ModuleDebug != NULL)
  {
    RtlDestroyQueryDebugBuffer(ModuleDebug);
  }

  if(ProcThrdInfo != NULL)
  {
    NtFreeVirtualMemory(NtCurrentProcess(),
                        &ProcThrdInfo,
                        &ProcThrdInfoSize,
                        MEM_RELEASE);
  }
}