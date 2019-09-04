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
struct TYPE_5__ {int /*<<< orphan*/  node; } ;
struct TYPE_6__ {TYPE_1__ element; int /*<<< orphan*/  IHTMLFrameBase2_iface; int /*<<< orphan*/  IHTMLFrameBase_iface; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_2__ HTMLFrameBase ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  HTMLElement_QI (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  IID_IHTMLFrameBase ; 
 int /*<<< orphan*/  IID_IHTMLFrameBase2 ; 
 int /*<<< orphan*/  IUnknown_AddRef (int /*<<< orphan*/ *) ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*,void**) ; 

HRESULT HTMLFrameBase_QI(HTMLFrameBase *This, REFIID riid, void **ppv)
{
    if(IsEqualGUID(&IID_IHTMLFrameBase, riid)) {
        TRACE("(%p)->(IID_IHTMLFrameBase %p)\n", This, ppv);
        *ppv = &This->IHTMLFrameBase_iface;
    }else if(IsEqualGUID(&IID_IHTMLFrameBase2, riid)) {
        TRACE("(%p)->(IID_IHTMLFrameBase2 %p)\n", This, ppv);
        *ppv = &This->IHTMLFrameBase2_iface;
    }else {
        return HTMLElement_QI(&This->element.node, riid, ppv);
    }

    IUnknown_AddRef((IUnknown*)*ppv);
    return S_OK;
}