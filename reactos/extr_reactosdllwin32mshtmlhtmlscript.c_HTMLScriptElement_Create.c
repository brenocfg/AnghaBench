#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ nsresult ;
typedef  int /*<<< orphan*/  nsIDOMHTMLElement ;
struct TYPE_8__ {int /*<<< orphan*/ * vtbl; } ;
struct TYPE_11__ {TYPE_1__ node; } ;
struct TYPE_9__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_10__ {TYPE_4__ element; int /*<<< orphan*/  nsscript; TYPE_2__ IHTMLScriptElement_iface; } ;
typedef  TYPE_3__ HTMLScriptElement ;
typedef  TYPE_4__ HTMLElement ;
typedef  int /*<<< orphan*/  HTMLDocumentNode ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  HTMLElement_Init (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HTMLScriptElementImplVtbl ; 
 int /*<<< orphan*/  HTMLScriptElementVtbl ; 
 int /*<<< orphan*/  HTMLScriptElement_dispex ; 
 int /*<<< orphan*/  IID_nsIDOMHTMLScriptElement ; 
 scalar_t__ NS_OK ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_3__* heap_alloc_zero (int) ; 
 scalar_t__ nsIDOMHTMLElement_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 

HRESULT HTMLScriptElement_Create(HTMLDocumentNode *doc, nsIDOMHTMLElement *nselem, HTMLElement **elem)
{
    HTMLScriptElement *ret;
    nsresult nsres;

    ret = heap_alloc_zero(sizeof(HTMLScriptElement));
    if(!ret)
        return E_OUTOFMEMORY;

    ret->IHTMLScriptElement_iface.lpVtbl = &HTMLScriptElementVtbl;
    ret->element.node.vtbl = &HTMLScriptElementImplVtbl;

    HTMLElement_Init(&ret->element, doc, nselem, &HTMLScriptElement_dispex);

    nsres = nsIDOMHTMLElement_QueryInterface(nselem, &IID_nsIDOMHTMLScriptElement, (void**)&ret->nsscript);
    assert(nsres == NS_OK);

    *elem = &ret->element;
    return S_OK;
}