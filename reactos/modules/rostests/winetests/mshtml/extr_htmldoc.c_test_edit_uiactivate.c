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
typedef  int /*<<< orphan*/  IOleDocumentView ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_CALLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IOleDocumentView ; 
 int /*<<< orphan*/  IOleDocumentView_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IOleDocumentView_UIActivate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IOleObject_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  InPlaceFrame_SetBorderSpace ; 
 int /*<<< orphan*/  InPlaceUIWindow_SetActiveObject ; 
 int /*<<< orphan*/  OnFocus_TRUE ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SetActiveObject ; 
 int /*<<< orphan*/  ShowUI ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * expect_status_text ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_edit_uiactivate(IOleObject *oleobj)
{
    IOleDocumentView *docview;
    HRESULT hres;

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