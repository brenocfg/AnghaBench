#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_13__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_12__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_11__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_10__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_14__ {TYPE_7__ IDirectInput7A_iface; TYPE_4__ IDirectInputJoyConfig8_iface; TYPE_3__ IDirectInput8W_iface; TYPE_2__ IDirectInput8A_iface; TYPE_1__ IDirectInput7W_iface; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  TYPE_5__ IDirectInputImpl ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DI_OK ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_5__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  IDirectInput_QueryInterface (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JoyConfig8vt ; 
 int /*<<< orphan*/  ddi7avt ; 
 int /*<<< orphan*/  ddi7wvt ; 
 int /*<<< orphan*/  ddi8avt ; 
 int /*<<< orphan*/  ddi8wvt ; 

__attribute__((used)) static HRESULT create_directinput_instance(REFIID riid, LPVOID *ppDI, IDirectInputImpl **out)
{
    IDirectInputImpl *This = HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(IDirectInputImpl) );
    HRESULT hr;

    if (!This)
        return E_OUTOFMEMORY;

    This->IDirectInput7A_iface.lpVtbl = &ddi7avt;
    This->IDirectInput7W_iface.lpVtbl = &ddi7wvt;
    This->IDirectInput8A_iface.lpVtbl = &ddi8avt;
    This->IDirectInput8W_iface.lpVtbl = &ddi8wvt;
    This->IDirectInputJoyConfig8_iface.lpVtbl = &JoyConfig8vt;

    hr = IDirectInput_QueryInterface( &This->IDirectInput7A_iface, riid, ppDI );
    if (FAILED(hr))
    {
        HeapFree( GetProcessHeap(), 0, This );
        return hr;
    }

    if (out) *out = This;
    return DI_OK;
}