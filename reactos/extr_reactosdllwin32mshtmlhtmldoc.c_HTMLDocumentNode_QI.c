#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  node; int /*<<< orphan*/  IInternetHostSecurityManager_iface; int /*<<< orphan*/  basedoc; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_1__ HTMLDocumentNode ;
typedef  int /*<<< orphan*/  HTMLDOMNode ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_NOINTERFACE ; 
 int /*<<< orphan*/  HTMLDOMNode_QI (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  IID_IInternetHostSecurityManager ; 
 int /*<<< orphan*/  IUnknown_AddRef (int /*<<< orphan*/ *) ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  debugstr_mshtml_guid (int /*<<< orphan*/ ) ; 
 scalar_t__ htmldoc_qi (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**) ; 
 TYPE_1__* impl_from_HTMLDOMNode (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT HTMLDocumentNode_QI(HTMLDOMNode *iface, REFIID riid, void **ppv)
{
    HTMLDocumentNode *This = impl_from_HTMLDOMNode(iface);

    TRACE("(%p)->(%s %p)\n", This, debugstr_mshtml_guid(riid), ppv);

    if(htmldoc_qi(&This->basedoc, riid, ppv))
        return *ppv ? S_OK : E_NOINTERFACE;

    if(IsEqualGUID(&IID_IInternetHostSecurityManager, riid))
        *ppv = &This->IInternetHostSecurityManager_iface;
    else
        return HTMLDOMNode_QI(&This->node, riid, ppv);

    IUnknown_AddRef((IUnknown*)*ppv);
    return S_OK;
}