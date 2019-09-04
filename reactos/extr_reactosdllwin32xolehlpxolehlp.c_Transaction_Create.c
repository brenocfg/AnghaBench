#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_7__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int /*<<< orphan*/  isoFlags; int /*<<< orphan*/  isoLevel; } ;
struct TYPE_6__ {int ref; TYPE_2__ ITransaction_iface; TYPE_3__ info; } ;
typedef  TYPE_1__ Transaction ;
typedef  int /*<<< orphan*/  ITransactionOptions ;
typedef  TYPE_2__ ITransaction ;
typedef  int /*<<< orphan*/  ISOLEVEL ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  Transaction_Vtbl ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_3__*,int) ; 

__attribute__((used)) static HRESULT Transaction_Create(ISOLEVEL isoLevel, ULONG isoFlags,
        ITransactionOptions *pOptions, ITransaction **ppv)
{
    Transaction *This;

    if (!ppv) return E_INVALIDARG;

    This = HeapAlloc(GetProcessHeap(), 0, sizeof(Transaction));
    if (!This) return E_OUTOFMEMORY;
    ZeroMemory(&This->info, sizeof(This->info));

    This->ITransaction_iface.lpVtbl = &Transaction_Vtbl;
    This->ref = 1;
    This->info.isoLevel = isoLevel;
    This->info.isoFlags = isoFlags;

    *ppv = &This->ITransaction_iface;

    return S_OK;
}