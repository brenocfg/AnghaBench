#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ClientSite ; 
 int /*<<< orphan*/  Dispatch ; 
 int /*<<< orphan*/  DocHostUIHandler ; 
 int /*<<< orphan*/  DocumentSite ; 
 int /*<<< orphan*/  E_NOINTERFACE ; 
 int /*<<< orphan*/  IID_IDispatch ; 
 int /*<<< orphan*/  IID_IDocHostShowUI ; 
 int /*<<< orphan*/  IID_IDocHostUIHandler ; 
 int /*<<< orphan*/  IID_IDocHostUIHandler2 ; 
 int /*<<< orphan*/  IID_IDocHostUIHandlerPriv ; 
 int /*<<< orphan*/  IID_IOleClientSite ; 
 int /*<<< orphan*/  IID_IOleCommandTarget ; 
 int /*<<< orphan*/  IID_IOleContainer ; 
 int /*<<< orphan*/  IID_IOleControlSite ; 
 int /*<<< orphan*/  IID_IOleDocumentSite ; 
 int /*<<< orphan*/  IID_IOleInPlaceSite ; 
 int /*<<< orphan*/  IID_IOleInPlaceSiteEx ; 
 int /*<<< orphan*/  IID_IOleInPlaceSiteWindowless ; 
 int /*<<< orphan*/  IID_IOleWindow ; 
 int /*<<< orphan*/  IID_IProxyManager ; 
 int /*<<< orphan*/  IID_IRenMailEditor ; 
 int /*<<< orphan*/  IID_IServiceProvider ; 
 int /*<<< orphan*/  IID_IThumbnailView ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IID_unk1 ; 
 int /*<<< orphan*/  IID_unk4 ; 
 int /*<<< orphan*/  IID_unk5 ; 
 int /*<<< orphan*/  InPlaceSiteWindowless ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OleCommandTarget ; 
 int /*<<< orphan*/  OleContainer ; 
 int /*<<< orphan*/  OleControlSite ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  ServiceProvider ; 
 scalar_t__ ipsex ; 
 scalar_t__ ipsw ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wine_dbgstr_guid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT QueryInterface(REFIID riid, void **ppv)
{
    *ppv = NULL;

    if(IsEqualGUID(&IID_IUnknown, riid) || IsEqualGUID(&IID_IOleClientSite, riid))
        *ppv = &ClientSite;
    else if(IsEqualGUID(&IID_IOleDocumentSite, riid))
        *ppv = &DocumentSite;
    else if(IsEqualGUID(&IID_IDocHostUIHandler, riid) || IsEqualGUID(&IID_IDocHostUIHandler2, riid))
        *ppv = &DocHostUIHandler;
    else if(IsEqualGUID(&IID_IOleContainer, riid))
        *ppv = &OleContainer;
    else if(IsEqualGUID(&IID_IOleWindow, riid) || IsEqualGUID(&IID_IOleInPlaceSite, riid))
        *ppv = &InPlaceSiteWindowless;
    else if(IsEqualGUID(&IID_IOleCommandTarget , riid))
        *ppv = &OleCommandTarget;
    else if(IsEqualGUID(&IID_IDispatch, riid))
        *ppv = &Dispatch;
    else if(IsEqualGUID(&IID_IServiceProvider, riid))
        *ppv = &ServiceProvider;
    else if(IsEqualGUID(&IID_IOleInPlaceSiteEx, riid))
        *ppv = ipsex ? &InPlaceSiteWindowless : NULL;
    else if(IsEqualGUID(&IID_IOleInPlaceSiteWindowless, riid))
        *ppv = ipsw ? &InPlaceSiteWindowless : NULL;
    else if(IsEqualGUID(&IID_IOleControlSite, riid))
        *ppv = &OleControlSite;
    else if(IsEqualGUID(&IID_IDocHostShowUI, riid))
        return E_NOINTERFACE; /* TODO */
    else if(IsEqualGUID(&IID_IProxyManager, riid))
        return E_NOINTERFACE; /* ? */
    else if(IsEqualGUID(&IID_unk1, riid))
        return E_NOINTERFACE; /* HTMLWindow2 ? */
    else if(IsEqualGUID(&IID_IThumbnailView, riid))
        return E_NOINTERFACE; /* ? */
    else if(IsEqualGUID(&IID_IRenMailEditor, riid))
        return E_NOINTERFACE; /* ? */
    else if(IsEqualGUID(&IID_unk4, riid))
        return E_NOINTERFACE; /* ? */
    else if(IsEqualGUID(&IID_unk5, riid))
        return E_NOINTERFACE; /* IE10 */
    else if(IsEqualGUID(&IID_IDocHostUIHandlerPriv, riid))
        return E_NOINTERFACE; /* ? */
    else
        trace("QI(%s)\n", wine_dbgstr_guid(riid));

    if(*ppv)
        return S_OK;
    return E_NOINTERFACE;
}