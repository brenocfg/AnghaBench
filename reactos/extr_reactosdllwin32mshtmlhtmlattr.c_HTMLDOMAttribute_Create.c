#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_16__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_15__ {int /*<<< orphan*/  IHTMLAttributeCollection_iface; } ;
struct TYPE_11__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_14__ {int ref; TYPE_7__ IHTMLDOMAttribute_iface; int /*<<< orphan*/  name; int /*<<< orphan*/  entry; int /*<<< orphan*/  dispex; TYPE_3__* elem; int /*<<< orphan*/  dispid; TYPE_1__ IHTMLDOMAttribute2_iface; } ;
struct TYPE_13__ {TYPE_2__* attrs; int /*<<< orphan*/  node; } ;
struct TYPE_12__ {int /*<<< orphan*/  attrs; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_3__ HTMLElement ;
typedef  TYPE_4__ HTMLDOMAttribute ;
typedef  TYPE_5__ HTMLAttributeCollection ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DISPID ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HTMLDOMAttribute2Vtbl ; 
 int /*<<< orphan*/  HTMLDOMAttributeVtbl ; 
 int /*<<< orphan*/  HTMLDOMAttribute_dispex ; 
 int /*<<< orphan*/  HTMLElement_get_attr_col (int /*<<< orphan*/ *,TYPE_5__**) ; 
 int /*<<< orphan*/  IHTMLAttributeCollection_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHTMLDOMAttribute_Release (TYPE_7__*) ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_4__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  heap_strdupW (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  init_dispex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

HRESULT HTMLDOMAttribute_Create(const WCHAR *name, HTMLElement *elem, DISPID dispid, HTMLDOMAttribute **attr)
{
    HTMLAttributeCollection *col;
    HTMLDOMAttribute *ret;
    HRESULT hres;

    ret = heap_alloc_zero(sizeof(*ret));
    if(!ret)
        return E_OUTOFMEMORY;

    ret->IHTMLDOMAttribute_iface.lpVtbl = &HTMLDOMAttributeVtbl;
    ret->IHTMLDOMAttribute2_iface.lpVtbl = &HTMLDOMAttribute2Vtbl;
    ret->ref = 1;
    ret->dispid = dispid;
    ret->elem = elem;

    init_dispex(&ret->dispex, (IUnknown*)&ret->IHTMLDOMAttribute_iface,
            &HTMLDOMAttribute_dispex);

    /* For attributes attached to an element, (elem,dispid) pair should be valid used for its operation. */
    if(elem) {
        hres = HTMLElement_get_attr_col(&elem->node, &col);
        if(FAILED(hres)) {
            IHTMLDOMAttribute_Release(&ret->IHTMLDOMAttribute_iface);
            return hres;
        }
        IHTMLAttributeCollection_Release(&col->IHTMLAttributeCollection_iface);

        list_add_tail(&elem->attrs->attrs, &ret->entry);
    }

    /* For detached attributes we may still do most operations if we have its name available. */
    if(name) {
        ret->name = heap_strdupW(name);
        if(!ret->name) {
            IHTMLDOMAttribute_Release(&ret->IHTMLDOMAttribute_iface);
            return E_OUTOFMEMORY;
        }
    }

    *attr = ret;
    return S_OK;
}