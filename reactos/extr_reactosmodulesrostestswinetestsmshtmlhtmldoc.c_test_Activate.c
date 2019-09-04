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
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IOleObject ;
typedef  int /*<<< orphan*/  IOleDocumentView ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_CALLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLSID_HTMLDocument ; 
 scalar_t__ CallUIActivate_AfterShow ; 
 scalar_t__ E_INVALIDARG ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IHTMLDocument2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IOleDocumentView ; 
 int /*<<< orphan*/  IID_IOleObject ; 
 int /*<<< orphan*/  IOleDocumentView_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IOleDocumentView_UIActivate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IOleObject_GetUserClassID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IOleObject_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IOleObject_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InPlaceFrame_SetBorderSpace ; 
 int /*<<< orphan*/  InPlaceUIWindow_SetActiveObject ; 
 int /*<<< orphan*/  IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OnFocus_TRUE ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SetActiveObject ; 
 int /*<<< orphan*/  ShowUI ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ call_UIActivate ; 
 int /*<<< orphan*/  doc_hwnd ; 
 int /*<<< orphan*/ * expect_status_text ; 
 int /*<<< orphan*/  last_hwnd ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  test_ClientSite (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_DoVerb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_InPlaceDeactivate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_OnFrameWindowActivate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * view ; 

__attribute__((used)) static void test_Activate(IHTMLDocument2 *doc, DWORD flags)
{
    IOleObject *oleobj = NULL;
    IOleDocumentView *docview;
    GUID guid;
    HRESULT hres;

    last_hwnd = doc_hwnd;

    if(view)
        IOleDocumentView_Release(view);
    view = NULL;

    hres = IHTMLDocument2_QueryInterface(doc, &IID_IOleObject, (void**)&oleobj);
    ok(hres == S_OK, "QueryInterface(IID_IOleObject) failed: %08x\n", hres);

    hres = IOleObject_GetUserClassID(oleobj, NULL);
    ok(hres == E_INVALIDARG, "GetUserClassID returned: %08x, expected E_INVALIDARG\n", hres);

    hres = IOleObject_GetUserClassID(oleobj, &guid);
    ok(hres == S_OK, "GetUserClassID failed: %08x\n", hres);
    ok(IsEqualGUID(&guid, &CLSID_HTMLDocument), "guid != CLSID_HTMLDocument\n");

    test_OnFrameWindowActivate((IUnknown*)doc);

    test_ClientSite(oleobj, flags);
    test_InPlaceDeactivate(doc, FALSE);
    test_DoVerb(oleobj);

    if(call_UIActivate == CallUIActivate_AfterShow) {
        hres = IOleObject_QueryInterface(oleobj, &IID_IOleDocumentView, (void **)&docview);
        ok(hres == S_OK, "IOleObject_QueryInterface failed with error 0x%08x\n", hres);

        SET_EXPECT(OnFocus_TRUE);
        SET_EXPECT(SetActiveObject);
        SET_EXPECT(ShowUI);
        SET_EXPECT(InPlaceUIWindow_SetActiveObject);
        SET_EXPECT(InPlaceFrame_SetBorderSpace);
        expect_status_text = NULL;

        hres = IOleDocumentView_UIActivate(docview, TRUE);
        ok(hres == S_OK, "IOleDocumentView_UIActivate failed with error 0x%08x\n", hres);

        CHECK_CALLED(OnFocus_TRUE);
        CHECK_CALLED(SetActiveObject);
        CHECK_CALLED(ShowUI);
        CHECK_CALLED(InPlaceUIWindow_SetActiveObject);
        CHECK_CALLED(InPlaceFrame_SetBorderSpace);

        IOleDocumentView_Release(docview);
    }

    IOleObject_Release(oleobj);

    test_OnFrameWindowActivate((IUnknown*)doc);
}