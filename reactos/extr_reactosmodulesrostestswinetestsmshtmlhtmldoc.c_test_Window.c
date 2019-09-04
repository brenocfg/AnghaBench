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
typedef  int /*<<< orphan*/  IOleInPlaceActiveObject ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  scalar_t__ HWND ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ E_FAIL ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  IID_IOleInPlaceActiveObject ; 
 scalar_t__ IOleDocumentView_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IOleInPlaceActiveObject_GetWindow (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  IOleInPlaceActiveObject_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IsWindow (scalar_t__) ; 
 scalar_t__ S_OK ; 
 scalar_t__ doc_hwnd ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  view ; 

__attribute__((used)) static void test_Window(IHTMLDocument2 *doc, BOOL expect_success)
{
    IOleInPlaceActiveObject *activeobject = NULL;
    HWND tmp_hwnd;
    HRESULT hres;

    hres = IOleDocumentView_QueryInterface(view, &IID_IOleInPlaceActiveObject, (void**)&activeobject);
    ok(hres == S_OK, "Could not get IOleInPlaceActiveObject interface: %08x\n", hres);
    if(FAILED(hres))
        return;

    hres = IOleInPlaceActiveObject_GetWindow(activeobject, &tmp_hwnd);

    if(expect_success) {
        ok(hres == S_OK, "GetWindow failed: %08x\n", hres);
        ok(tmp_hwnd == doc_hwnd, "tmp_hwnd=%p, expected %p\n", tmp_hwnd, doc_hwnd);
    }else {
        ok(hres == E_FAIL, "GetWindow returned %08x, expected E_FAIL\n", hres);
        ok(IsWindow(doc_hwnd), "hwnd is destroyed\n");
    }

    IOleInPlaceActiveObject_Release(activeobject);
}