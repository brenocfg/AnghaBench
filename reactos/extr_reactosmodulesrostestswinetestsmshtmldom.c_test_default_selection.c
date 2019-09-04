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
typedef  int /*<<< orphan*/  IHTMLTxtRange ;
typedef  int /*<<< orphan*/  IHTMLSelectionObject ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 scalar_t__ IDispatch_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLDocument2_get_selection (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IHTMLSelectionObject_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLSelectionObject_createRange (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IHTMLSelectionObject_get_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHTMLTxtRange_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IHTMLTxtRange ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  strcmp_wa (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test_range_text (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ wine_dbgstr_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_default_selection(IHTMLDocument2 *doc)
{
    IHTMLSelectionObject *selection;
    IHTMLTxtRange *range;
    IDispatch *disp;
    BSTR str;
    HRESULT hres;

    hres = IHTMLDocument2_get_selection(doc, &selection);
    ok(hres == S_OK, "get_selection failed: %08x\n", hres);

    hres = IHTMLSelectionObject_get_type(selection, &str);
    ok(hres == S_OK, "get_type failed: %08x\n", hres);
    ok(!strcmp_wa(str, "None"), "type = %s\n", wine_dbgstr_w(str));
    SysFreeString(str);

    hres = IHTMLSelectionObject_createRange(selection, &disp);
    IHTMLSelectionObject_Release(selection);
    ok(hres == S_OK, "createRange failed: %08x\n", hres);

    hres = IDispatch_QueryInterface(disp, &IID_IHTMLTxtRange, (void**)&range);
    IDispatch_Release(disp);
    ok(hres == S_OK, "Could not get IHTMLTxtRange interface: %08x\n", hres);

    test_range_text(range, NULL);
    IHTMLTxtRange_Release(range);
}