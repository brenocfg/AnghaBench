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
struct TYPE_6__ {int ref; TYPE_1__ IHTMLScreen_iface; int /*<<< orphan*/  dispex; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_1__ IHTMLScreen ;
typedef  TYPE_2__ HTMLScreen ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  HTMLScreen_dispex ; 
 int /*<<< orphan*/  HTMLSreenVtbl ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_2__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  init_dispex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

HRESULT HTMLScreen_Create(IHTMLScreen **ret)
{
    HTMLScreen *screen;

    screen = heap_alloc_zero(sizeof(HTMLScreen));
    if(!screen)
        return E_OUTOFMEMORY;

    screen->IHTMLScreen_iface.lpVtbl = &HTMLSreenVtbl;
    screen->ref = 1;

    init_dispex(&screen->dispex, (IUnknown*)&screen->IHTMLScreen_iface, &HTMLScreen_dispex);

    *ret = &screen->IHTMLScreen_iface;
    return S_OK;
}