#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct IUnknown {int dummy; } ;
struct TYPE_16__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_13__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_12__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_11__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_14__ {int ref; int /*<<< orphan*/  web_browser; scalar_t__ ole_obj; TYPE_8__ IOleClientSite_iface; int /*<<< orphan*/  hwndWindow; TYPE_3__ IDocHostUIHandler_iface; TYPE_2__ IOleInPlaceFrame_iface; TYPE_1__ IOleInPlaceSite_iface; } ;
typedef  TYPE_4__ WebBrowserContainer ;
struct TYPE_15__ {TYPE_4__* web_browser; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  IOleInPlaceObject ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_5__ HHInfo ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_WebBrowser ; 
 int /*<<< orphan*/  DocHostUIHandlerVtbl ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IOleInPlaceObject ; 
 int /*<<< orphan*/  IID_IOleObject ; 
 int /*<<< orphan*/  IID_IWebBrowser2 ; 
 int /*<<< orphan*/  IOleInPlaceObject_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOleInPlaceObject_SetObjectRects (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOleObject_DoVerb (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_8__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOleObject_QueryInterface (scalar_t__,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  MyIStorage ; 
 int /*<<< orphan*/  OLEIVERB_SHOW ; 
 int /*<<< orphan*/  OLERENDER_DRAW ; 
 int /*<<< orphan*/  OleClientSiteVtbl ; 
 int /*<<< orphan*/  OleCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  OleInPlaceFrameVtbl ; 
 int /*<<< orphan*/  OleInPlaceSiteVtbl ; 
 int /*<<< orphan*/  OleSetContainedObject (struct IUnknown*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseWebBrowser (TYPE_5__*) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_4__* heap_alloc_zero (int) ; 

BOOL InitWebBrowser(HHInfo *info, HWND hwndParent)
{
    WebBrowserContainer *container;
    IOleInPlaceObject *inplace;
    HRESULT hr;
    RECT rc;

    container = heap_alloc_zero(sizeof(*container));
    if (!container)
        return FALSE;

    container->IOleClientSite_iface.lpVtbl = &OleClientSiteVtbl;
    container->IOleInPlaceSite_iface.lpVtbl = &OleInPlaceSiteVtbl;
    container->IOleInPlaceFrame_iface.lpVtbl = &OleInPlaceFrameVtbl;
    container->IDocHostUIHandler_iface.lpVtbl = &DocHostUIHandlerVtbl;
    container->ref = 1;
    container->hwndWindow = hwndParent;

    info->web_browser = container;

    hr = OleCreate(&CLSID_WebBrowser, &IID_IOleObject, OLERENDER_DRAW, 0,
                   &container->IOleClientSite_iface, &MyIStorage,
                   (void **)&container->ole_obj);

    if (FAILED(hr)) goto error;

    GetClientRect(hwndParent, &rc);

    hr = OleSetContainedObject((struct IUnknown *)container->ole_obj, TRUE);
    if (FAILED(hr)) goto error;

    hr = IOleObject_DoVerb(container->ole_obj, OLEIVERB_SHOW, NULL,
                           &container->IOleClientSite_iface, -1, hwndParent, &rc);
    if (FAILED(hr)) goto error;

    hr = IOleObject_QueryInterface(container->ole_obj, &IID_IOleInPlaceObject, (void**)&inplace);
    if (FAILED(hr)) goto error;

    IOleInPlaceObject_SetObjectRects(inplace, &rc, &rc);
    IOleInPlaceObject_Release(inplace);

    hr = IOleObject_QueryInterface(container->ole_obj, &IID_IWebBrowser2, (void **)&container->web_browser);
    if (SUCCEEDED(hr))
        return TRUE;

error:
    ReleaseWebBrowser(info);
    return FALSE;
}