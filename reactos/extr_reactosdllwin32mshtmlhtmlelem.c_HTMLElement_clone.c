#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsIDOMNode ;
struct TYPE_9__ {int /*<<< orphan*/  doc; } ;
struct TYPE_8__ {TYPE_2__ node; int /*<<< orphan*/  IHTMLElement_iface; scalar_t__ filter; } ;
typedef  TYPE_1__ HTMLElement ;
typedef  TYPE_2__ HTMLDOMNode ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HTMLElement_Create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  IHTMLElement_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ heap_strdupW (scalar_t__) ; 
 TYPE_1__* impl_from_HTMLDOMNode (TYPE_2__*) ; 

HRESULT HTMLElement_clone(HTMLDOMNode *iface, nsIDOMNode *nsnode, HTMLDOMNode **ret)
{
    HTMLElement *This = impl_from_HTMLDOMNode(iface);
    HTMLElement *new_elem;
    HRESULT hres;

    hres = HTMLElement_Create(This->node.doc, nsnode, FALSE, &new_elem);
    if(FAILED(hres))
        return hres;

    if(This->filter) {
        new_elem->filter = heap_strdupW(This->filter);
        if(!new_elem->filter) {
            IHTMLElement_Release(&This->IHTMLElement_iface);
            return E_OUTOFMEMORY;
        }
    }

    *ret = &new_elem->node;
    return S_OK;
}