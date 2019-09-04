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
struct TYPE_6__ {int ref; TYPE_1__ IHTMLOptionElementFactory_iface; int /*<<< orphan*/  dispex; int /*<<< orphan*/ * window; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_2__ HTMLOptionElementFactory ;
typedef  int /*<<< orphan*/  HTMLInnerWindow ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  HTMLOptionElementFactoryVtbl ; 
 int /*<<< orphan*/  HTMLOptionElementFactory_dispex ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_2__* heap_alloc (int) ; 
 int /*<<< orphan*/  init_dispex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

HRESULT HTMLOptionElementFactory_Create(HTMLInnerWindow *window, HTMLOptionElementFactory **ret_ptr)
{
    HTMLOptionElementFactory *ret;

    ret = heap_alloc(sizeof(*ret));
    if(!ret)
        return E_OUTOFMEMORY;

    ret->IHTMLOptionElementFactory_iface.lpVtbl = &HTMLOptionElementFactoryVtbl;
    ret->ref = 1;
    ret->window = window;

    init_dispex(&ret->dispex, (IUnknown*)&ret->IHTMLOptionElementFactory_iface,
            &HTMLOptionElementFactory_dispex);

    *ret_ptr = ret;
    return S_OK;
}