#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* DebugInfo; } ;
struct TYPE_9__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {TYPE_4__ IReferenceClock_iface; TYPE_5__ safe; int /*<<< orphan*/  lastTimeTickCount; scalar_t__ ref; } ;
struct TYPE_7__ {scalar_t__* Spare; } ;
typedef  TYPE_2__ SystemClockImpl ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD_PTR ;

/* Variables and functions */
 TYPE_2__* CoTaskMemAlloc (int) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetTickCount () ; 
 int /*<<< orphan*/  IID_IReferenceClock ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_5__*) ; 
 int /*<<< orphan*/  SystemClockImpl_QueryInterface (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SystemClock_Vtbl ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 

HRESULT QUARTZ_CreateSystemClock(IUnknown * pUnkOuter, LPVOID * ppv) {
  SystemClockImpl* obj = NULL;
  
  TRACE("(%p,%p)\n", ppv, pUnkOuter);
  
  obj = CoTaskMemAlloc(sizeof(SystemClockImpl));
  if (NULL == obj) 	{
    *ppv = NULL;
    return E_OUTOFMEMORY;
  }
  ZeroMemory(obj, sizeof(SystemClockImpl));

  obj->IReferenceClock_iface.lpVtbl = &SystemClock_Vtbl;
  obj->ref = 0;  /* will be inited by QueryInterface */

  obj->lastTimeTickCount = GetTickCount();
  InitializeCriticalSection(&obj->safe);
  obj->safe.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": SystemClockImpl.safe");

  return SystemClockImpl_QueryInterface(&obj->IReferenceClock_iface, &IID_IReferenceClock, ppv);
}