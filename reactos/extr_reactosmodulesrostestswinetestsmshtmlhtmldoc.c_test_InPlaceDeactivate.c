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
typedef  int /*<<< orphan*/  IOleInPlaceObjectWindowless ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_CALLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLEAR_CALLED (int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ IHTMLDocument2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IOleInPlaceObjectWindowless ; 
 scalar_t__ IOleInPlaceObjectWindowless_InPlaceDeactivate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOleInPlaceObjectWindowless_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OnFocus_FALSE ; 
 int /*<<< orphan*/  OnInPlaceDeactivate ; 
 int /*<<< orphan*/  OnInPlaceDeactivateEx ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SetStatusText ; 
 scalar_t__ ipsex ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_InPlaceDeactivate(IHTMLDocument2 *doc, BOOL expect_call)
{
    IOleInPlaceObjectWindowless *windowlessobj = NULL;
    HRESULT hres;

    hres = IHTMLDocument2_QueryInterface(doc, &IID_IOleInPlaceObjectWindowless,
            (void**)&windowlessobj);
    ok(hres == S_OK, "QueryInterface(IID_IOleInPlaceObjectWindowless) failed: %08x\n", hres);
    if(FAILED(hres))
        return;

    if(expect_call) {
        SET_EXPECT(SetStatusText);
        SET_EXPECT(OnFocus_FALSE);
        if(ipsex)
            SET_EXPECT(OnInPlaceDeactivateEx);
        else
            SET_EXPECT(OnInPlaceDeactivate);
    }
    hres = IOleInPlaceObjectWindowless_InPlaceDeactivate(windowlessobj);
    ok(hres == S_OK, "InPlaceDeactivate failed: %08x\n", hres);
    if(expect_call) {
        CLEAR_CALLED(SetStatusText); /* Called by IE9 */
        CHECK_CALLED(OnFocus_FALSE);
        if(ipsex)
            CHECK_CALLED(OnInPlaceDeactivateEx);
        else
            CHECK_CALLED(OnInPlaceDeactivate);
    }

    IOleInPlaceObjectWindowless_Release(windowlessobj);
}