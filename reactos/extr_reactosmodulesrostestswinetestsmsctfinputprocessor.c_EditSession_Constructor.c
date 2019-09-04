#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int refCount; TYPE_1__ ITfEditSession_iface; } ;
typedef  TYPE_1__ ITfEditSession ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ EditSession ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  EditSession_EditSessionVtbl ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  S_OK ; 

__attribute__((used)) static HRESULT EditSession_Constructor(ITfEditSession **ppOut)
{
    EditSession *This;

    *ppOut = NULL;
    This = HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,sizeof(EditSession));
    if (This == NULL)
        return E_OUTOFMEMORY;

    This->ITfEditSession_iface.lpVtbl = &EditSession_EditSessionVtbl;
    This->refCount = 1;

    *ppOut = &This->ITfEditSession_iface;
    return S_OK;
}