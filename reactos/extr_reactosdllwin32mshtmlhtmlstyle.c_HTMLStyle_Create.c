#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsIDOMCSSStyleDeclaration ;
struct TYPE_7__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int ref; TYPE_1__ IHTMLStyle_iface; int /*<<< orphan*/  dispex; int /*<<< orphan*/ * elem; int /*<<< orphan*/ * nsstyle; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_2__ HTMLStyle ;
typedef  int /*<<< orphan*/  HTMLElement ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HTMLStyle2_Init (TYPE_2__*) ; 
 int /*<<< orphan*/  HTMLStyle3_Init (TYPE_2__*) ; 
 int /*<<< orphan*/  HTMLStyleVtbl ; 
 int /*<<< orphan*/  HTMLStyle_dispex ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  get_style_from_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 TYPE_2__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  init_dispex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMCSSStyleDeclaration_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMCSSStyleDeclaration_Release (int /*<<< orphan*/ *) ; 

HRESULT HTMLStyle_Create(HTMLElement *elem, HTMLStyle **ret)
{
    nsIDOMCSSStyleDeclaration *nsstyle;
    HTMLStyle *style;
    HRESULT hres;

    hres = get_style_from_elem(elem, &nsstyle);
    if(FAILED(hres))
        return hres;

    style = heap_alloc_zero(sizeof(HTMLStyle));
    if(!style) {
        nsIDOMCSSStyleDeclaration_Release(nsstyle);
        return E_OUTOFMEMORY;
    }

    style->IHTMLStyle_iface.lpVtbl = &HTMLStyleVtbl;
    style->ref = 1;
    style->nsstyle = nsstyle;
    style->elem = elem;
    HTMLStyle2_Init(style);
    HTMLStyle3_Init(style);

    nsIDOMCSSStyleDeclaration_AddRef(nsstyle);

    init_dispex(&style->dispex, (IUnknown*)&style->IHTMLStyle_iface, &HTMLStyle_dispex);

    *ret = style;
    return S_OK;
}