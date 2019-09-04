#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_9__ {TYPE_1__* DebugInfo; } ;
struct TYPE_8__ {int ref; TYPE_4__ IWICFormatConverter_iface; TYPE_3__ lock; int /*<<< orphan*/ * palette; int /*<<< orphan*/ * source; } ;
struct TYPE_7__ {scalar_t__* Spare; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ FormatConverter ;
typedef  scalar_t__ DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FormatConverter_Vtbl ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IWICFormatConverter_QueryInterface (TYPE_4__*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  IWICFormatConverter_Release (TYPE_4__*) ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_3__*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ ) ; 

HRESULT FormatConverter_CreateInstance(REFIID iid, void** ppv)
{
    FormatConverter *This;
    HRESULT ret;

    TRACE("(%s,%p)\n", debugstr_guid(iid), ppv);

    *ppv = NULL;

    This = HeapAlloc(GetProcessHeap(), 0, sizeof(FormatConverter));
    if (!This) return E_OUTOFMEMORY;

    This->IWICFormatConverter_iface.lpVtbl = &FormatConverter_Vtbl;
    This->ref = 1;
    This->source = NULL;
    This->palette = NULL;
    InitializeCriticalSection(&This->lock);
    This->lock.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": FormatConverter.lock");

    ret = IWICFormatConverter_QueryInterface(&This->IWICFormatConverter_iface, iid, ppv);
    IWICFormatConverter_Release(&This->IWICFormatConverter_iface);

    return ret;
}