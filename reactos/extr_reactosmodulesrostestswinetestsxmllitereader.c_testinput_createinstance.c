#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int ref; TYPE_1__ IUnknown_iface; } ;
typedef  TYPE_2__ testinput ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_2__* heap_alloc (int) ; 
 int /*<<< orphan*/  testinput_vtbl ; 

__attribute__((used)) static HRESULT testinput_createinstance(void **ppObj)
{
    testinput *input;

    input = heap_alloc(sizeof(*input));
    if(!input) return E_OUTOFMEMORY;

    input->IUnknown_iface.lpVtbl = &testinput_vtbl;
    input->ref = 1;

    *ppObj = &input->IUnknown_iface;

    return S_OK;
}