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
typedef  int /*<<< orphan*/  nsIDOMHTMLElement ;
struct TYPE_9__ {int /*<<< orphan*/ * vtbl; } ;
struct TYPE_11__ {TYPE_2__ node; } ;
struct TYPE_8__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_10__ {TYPE_4__ element; TYPE_1__ IHTMLTitleElement_iface; } ;
typedef  TYPE_3__ HTMLTitleElement ;
typedef  TYPE_4__ HTMLElement ;
typedef  int /*<<< orphan*/  HTMLDocumentNode ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  HTMLElement_Init (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HTMLTitleElementImplVtbl ; 
 int /*<<< orphan*/  HTMLTitleElementVtbl ; 
 int /*<<< orphan*/  HTMLTitleElement_dispex ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_3__* heap_alloc_zero (int) ; 

HRESULT HTMLTitleElement_Create(HTMLDocumentNode *doc, nsIDOMHTMLElement *nselem, HTMLElement **elem)
{
    HTMLTitleElement *ret;

    ret = heap_alloc_zero(sizeof(*ret));
    if(!ret)
        return E_OUTOFMEMORY;

    ret->IHTMLTitleElement_iface.lpVtbl = &HTMLTitleElementVtbl;
    ret->element.node.vtbl = &HTMLTitleElementImplVtbl;

    HTMLElement_Init(&ret->element, doc, nselem, &HTMLTitleElement_dispex);

    *elem = &ret->element;
    return S_OK;
}