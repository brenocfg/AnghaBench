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
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_CALLED (int /*<<< orphan*/ ) ; 
 scalar_t__ CallUIActivate_AfterShow ; 
 scalar_t__ CallUIActivate_None ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HideUI ; 
 scalar_t__ IOleDocumentView_UIActivate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InPlaceUIWindow_SetActiveObject ; 
 int /*<<< orphan*/  OnUIDeactivate ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SetActiveObject_null ; 
 scalar_t__ call_UIActivate ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  view ; 

__attribute__((used)) static void test_UIDeactivate(void)
{
    HRESULT hres;

    if(call_UIActivate == CallUIActivate_AfterShow) {
        SET_EXPECT(InPlaceUIWindow_SetActiveObject);
    }
    if(call_UIActivate != CallUIActivate_None) {
        SET_EXPECT(SetActiveObject_null);
        SET_EXPECT(HideUI);
        SET_EXPECT(OnUIDeactivate);
    }

    hres = IOleDocumentView_UIActivate(view, FALSE);
    ok(hres == S_OK, "UIActivate failed: %08x\n", hres);

    if(call_UIActivate != CallUIActivate_None) {
        CHECK_CALLED(SetActiveObject_null);
        CHECK_CALLED(HideUI);
        CHECK_CALLED(OnUIDeactivate);
    }
    if(call_UIActivate == CallUIActivate_AfterShow) {
        CHECK_CALLED(InPlaceUIWindow_SetActiveObject);
    }
}