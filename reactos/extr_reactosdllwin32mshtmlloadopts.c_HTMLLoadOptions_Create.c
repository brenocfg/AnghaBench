#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int ref; TYPE_3__ IHtmlLoadOptions_iface; int /*<<< orphan*/ * opts; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_1__ HTMLLoadOptions ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  HtmlLoadOptionsVtbl ; 
 int /*<<< orphan*/  IHtmlLoadOptions_QueryInterface (TYPE_3__*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  IHtmlLoadOptions_Release (TYPE_3__*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  debugstr_mshtml_guid (int /*<<< orphan*/ ) ; 
 TYPE_1__* heap_alloc (int) ; 

HRESULT HTMLLoadOptions_Create(IUnknown *pUnkOuter, REFIID riid, void** ppv)
{
    HTMLLoadOptions *ret;
    HRESULT hres;

    TRACE("(%p %s %p)\n", pUnkOuter, debugstr_mshtml_guid(riid), ppv);

    ret = heap_alloc(sizeof(HTMLLoadOptions));
    if(!ret)
        return E_OUTOFMEMORY;

    ret->IHtmlLoadOptions_iface.lpVtbl = &HtmlLoadOptionsVtbl;
    ret->ref = 1;
    ret->opts = NULL;

    hres = IHtmlLoadOptions_QueryInterface(&ret->IHtmlLoadOptions_iface, riid, ppv);
    IHtmlLoadOptions_Release(&ret->IHtmlLoadOptions_iface);
    return hres;
}