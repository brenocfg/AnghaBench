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
typedef  int /*<<< orphan*/  IOleObject ;
typedef  int /*<<< orphan*/  IHlinkTarget ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ClientSite ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IHTMLDocument2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IHlinkTarget_Navigate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHlinkTarget_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IHlinkTarget ; 
 int /*<<< orphan*/  IID_IOleObject ; 
 int /*<<< orphan*/  IOleDocumentView_CloseView (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOleDocumentView_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOleDocumentView_SetInPlaceSite (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOleDocumentView_Show (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IOleObject_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IOleObject_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IOleObject_SetClientSite (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/ * view ; 

__attribute__((used)) static void set_client_site(IHTMLDocument2 *doc, BOOL set)
{
    IOleObject *oleobj;
    HRESULT hres;

    if(!set && view) {
        IOleDocumentView_Show(view, FALSE);
        IOleDocumentView_CloseView(view, 0);
        IOleDocumentView_SetInPlaceSite(view, NULL);
        IOleDocumentView_Release(view);
        view = NULL;
    }

    hres = IHTMLDocument2_QueryInterface(doc, &IID_IOleObject, (void**)&oleobj);
    ok(hres == S_OK, "Could not et IOleObject: %08x\n", hres);

    hres = IOleObject_SetClientSite(oleobj, set ? &ClientSite : NULL);
    ok(hres == S_OK, "SetClientSite failed: %08x\n", hres);

    if(set) {
        IHlinkTarget *hlink;

        hres = IOleObject_QueryInterface(oleobj, &IID_IHlinkTarget, (void**)&hlink);
        ok(hres == S_OK, "Could not get IHlinkTarget iface: %08x\n", hres);

        hres = IHlinkTarget_Navigate(hlink, 0, NULL);
        ok(hres == S_OK, "Navgate failed: %08x\n", hres);

        IHlinkTarget_Release(hlink);
    }

    IOleObject_Release(oleobj);
}