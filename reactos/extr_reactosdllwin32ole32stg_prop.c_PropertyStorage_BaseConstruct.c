#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_2__* DebugInfo; } ;
struct TYPE_13__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_15__ {int ref; TYPE_9__ cs; int /*<<< orphan*/  grfMode; struct TYPE_15__* fmtid; int /*<<< orphan*/ * stm; TYPE_1__ IPropertyStorage_iface; } ;
struct TYPE_14__ {scalar_t__* Spare; } ;
typedef  TYPE_3__** REFFMTID ;
typedef  TYPE_3__ PropertyStorage_impl ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD_PTR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteCriticalSection (TYPE_9__*) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_3__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  IPropertyStorage_Vtbl ; 
 int /*<<< orphan*/  IStream_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_9__*) ; 
 int /*<<< orphan*/  PropertyStorage_CreateDictionaries (TYPE_3__*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  assert (TYPE_3__**) ; 

__attribute__((used)) static HRESULT PropertyStorage_BaseConstruct(IStream *stm,
 REFFMTID rfmtid, DWORD grfMode, PropertyStorage_impl **pps)
{
    HRESULT hr = S_OK;

    assert(pps);
    assert(rfmtid);
    *pps = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof **pps);
    if (!*pps)
        return E_OUTOFMEMORY;

    (*pps)->IPropertyStorage_iface.lpVtbl = &IPropertyStorage_Vtbl;
    (*pps)->ref = 1;
    InitializeCriticalSection(&(*pps)->cs);
    (*pps)->cs.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": PropertyStorage_impl.cs");
    (*pps)->stm = stm;
    (*pps)->fmtid = *rfmtid;
    (*pps)->grfMode = grfMode;

    hr = PropertyStorage_CreateDictionaries(*pps);
    if (FAILED(hr))
    {
        (*pps)->cs.DebugInfo->Spare[0] = 0;
        DeleteCriticalSection(&(*pps)->cs);
        HeapFree(GetProcessHeap(), 0, *pps);
        *pps = NULL;
    }
    else IStream_AddRef( stm );

    return hr;
}