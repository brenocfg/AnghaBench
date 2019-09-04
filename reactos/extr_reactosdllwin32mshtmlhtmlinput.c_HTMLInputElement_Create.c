#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ nsresult ;
typedef  int /*<<< orphan*/  nsIDOMHTMLElement ;
struct TYPE_11__ {int /*<<< orphan*/ * vtbl; } ;
struct TYPE_13__ {TYPE_3__ node; } ;
struct TYPE_10__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_9__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_12__ {TYPE_5__ element; int /*<<< orphan*/  nsinput; TYPE_2__ IHTMLInputTextElement_iface; TYPE_1__ IHTMLInputElement_iface; } ;
typedef  TYPE_4__ HTMLInputElement ;
typedef  TYPE_5__ HTMLElement ;
typedef  int /*<<< orphan*/  HTMLDocumentNode ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  HTMLElement_Init (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HTMLInputElementImplVtbl ; 
 int /*<<< orphan*/  HTMLInputElementVtbl ; 
 int /*<<< orphan*/  HTMLInputElement_dispex ; 
 int /*<<< orphan*/  HTMLInputTextElementVtbl ; 
 int /*<<< orphan*/  IID_nsIDOMHTMLInputElement ; 
 scalar_t__ NS_OK ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_4__* heap_alloc_zero (int) ; 
 scalar_t__ nsIDOMHTMLElement_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 

HRESULT HTMLInputElement_Create(HTMLDocumentNode *doc, nsIDOMHTMLElement *nselem, HTMLElement **elem)
{
    HTMLInputElement *ret;
    nsresult nsres;

    ret = heap_alloc_zero(sizeof(HTMLInputElement));
    if(!ret)
        return E_OUTOFMEMORY;

    ret->IHTMLInputElement_iface.lpVtbl = &HTMLInputElementVtbl;
    ret->IHTMLInputTextElement_iface.lpVtbl = &HTMLInputTextElementVtbl;
    ret->element.node.vtbl = &HTMLInputElementImplVtbl;

    HTMLElement_Init(&ret->element, doc, nselem, &HTMLInputElement_dispex);

    nsres = nsIDOMHTMLElement_QueryInterface(nselem, &IID_nsIDOMHTMLInputElement, (void**)&ret->nsinput);
    assert(nsres == NS_OK);

    *elem = &ret->element;
    return S_OK;
}