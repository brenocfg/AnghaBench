#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* DebugInfo; } ;
struct TYPE_10__ {int /*<<< orphan*/  base; TYPE_5__ csState; int /*<<< orphan*/ * pMemory; } ;
struct TYPE_9__ {scalar_t__* Spare; } ;
typedef  TYPE_2__ StdMemAllocator ;
typedef  TYPE_2__* LPVOID ;
typedef  scalar_t__ LPUNKNOWN ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  BaseMemAllocator_Init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CLASS_E_NOAGGREGATION ; 
 TYPE_2__* CoTaskMemAlloc (int) ; 
 int /*<<< orphan*/  CoTaskMemFree (TYPE_2__*) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_5__*) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StdMemAllocator_Alloc ; 
 int /*<<< orphan*/  StdMemAllocator_Destroy ; 
 int /*<<< orphan*/  StdMemAllocator_Free ; 

HRESULT StdMemAllocator_create(LPUNKNOWN lpUnkOuter, LPVOID * ppv)
{
    StdMemAllocator * pMemAlloc;
    HRESULT hr;

    *ppv = NULL;
    
    if (lpUnkOuter)
        return CLASS_E_NOAGGREGATION;

    if (!(pMemAlloc = CoTaskMemAlloc(sizeof(*pMemAlloc))))
        return E_OUTOFMEMORY;

    InitializeCriticalSection(&pMemAlloc->csState);
    pMemAlloc->csState.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": StdMemAllocator.csState");

    pMemAlloc->pMemory = NULL;

    if (SUCCEEDED(hr = BaseMemAllocator_Init(StdMemAllocator_Alloc, StdMemAllocator_Free, NULL, NULL, NULL, StdMemAllocator_Destroy, &pMemAlloc->csState, &pMemAlloc->base)))
        *ppv = pMemAlloc;
    else
        CoTaskMemFree(pMemAlloc);

    return hr;
}