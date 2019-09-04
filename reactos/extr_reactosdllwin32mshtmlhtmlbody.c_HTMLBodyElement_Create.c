#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsIDOMHTMLElement ;
struct TYPE_10__ {int /*<<< orphan*/ * vtbl; } ;
struct TYPE_11__ {TYPE_2__ node; } ;
struct TYPE_13__ {TYPE_3__ element; } ;
struct TYPE_9__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_12__ {TYPE_7__ textcont; int /*<<< orphan*/  nsbody; TYPE_1__ IHTMLBodyElement_iface; } ;
typedef  TYPE_3__ HTMLElement ;
typedef  int /*<<< orphan*/  HTMLDocumentNode ;
typedef  TYPE_4__ HTMLBodyElement ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  HTMLBodyElementImplVtbl ; 
 int /*<<< orphan*/  HTMLBodyElementVtbl ; 
 int /*<<< orphan*/  HTMLBodyElement_dispex ; 
 int /*<<< orphan*/  HTMLTextContainer_Init (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_nsIDOMHTMLBodyElement ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_4__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  heap_free (TYPE_4__*) ; 
 int /*<<< orphan*/  nsIDOMHTMLElement_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 

HRESULT HTMLBodyElement_Create(HTMLDocumentNode *doc, nsIDOMHTMLElement *nselem, HTMLElement **elem)
{
    HTMLBodyElement *ret;
    nsresult nsres;

    ret = heap_alloc_zero(sizeof(HTMLBodyElement));
    if(!ret)
        return E_OUTOFMEMORY;

    ret->IHTMLBodyElement_iface.lpVtbl = &HTMLBodyElementVtbl;
    ret->textcont.element.node.vtbl = &HTMLBodyElementImplVtbl;

    nsres = nsIDOMHTMLElement_QueryInterface(nselem, &IID_nsIDOMHTMLBodyElement, (void**)&ret->nsbody);
    if(NS_FAILED(nsres)) {
        ERR("Could not get nsDOMHTMLBodyElement: %08x\n", nsres);
        heap_free(ret);
        return E_OUTOFMEMORY;
    }

    HTMLTextContainer_Init(&ret->textcont, doc, nselem, &HTMLBodyElement_dispex);

    *elem = &ret->textcont.element;
    return S_OK;
}