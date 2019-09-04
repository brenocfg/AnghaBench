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
typedef  int /*<<< orphan*/  IHTMLStyleSheetRulesCollection ;
typedef  int /*<<< orphan*/  IHTMLStyleSheet ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  DIID_DispHTMLStyleSheet ; 
 int /*<<< orphan*/  DIID_DispHTMLStyleSheetRulesCollection ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IDispatch_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IHTMLStyleSheetRulesCollection_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHTMLStyleSheet_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLStyleSheet_get_href (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IHTMLStyleSheet_get_rules (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IID_IHTMLStyleSheet ; 
 int /*<<< orphan*/  IID_IHTMLStyleSheetRulesCollection ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  set_stylesheet_csstext (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_disp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_stylesheet_csstext (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_stylesheet(IDispatch *disp)
{
    IHTMLStyleSheetRulesCollection *col = NULL;
    IHTMLStyleSheet *stylesheet;
    HRESULT hres;
    BSTR href;

    test_disp2((IUnknown*)disp, &DIID_DispHTMLStyleSheet, &IID_IHTMLStyleSheet, "[object]");

    hres = IDispatch_QueryInterface(disp, &IID_IHTMLStyleSheet, (void**)&stylesheet);
    ok(hres == S_OK, "Could not get IHTMLStyleSheet: %08x\n", hres);

    hres = IHTMLStyleSheet_get_rules(stylesheet, &col);
    ok(hres == S_OK, "get_rules failed: %08x\n", hres);
    ok(col != NULL, "col == NULL\n");

    test_disp2((IUnknown*)col, &DIID_DispHTMLStyleSheetRulesCollection, &IID_IHTMLStyleSheetRulesCollection, "[object]");
    IHTMLStyleSheetRulesCollection_Release(col);

    href = (void*)0xdeadbeef;
    hres = IHTMLStyleSheet_get_href(stylesheet, &href);
    ok(hres == S_OK, "get_href failed: %08x\n", hres);
    ok(href == NULL, "got href != NULL\n");
    SysFreeString(href);

    test_stylesheet_csstext(stylesheet, ".body {", FALSE);
    set_stylesheet_csstext(stylesheet, ".div { margin-right: 1px; }\n.body { margin-right: 2px; }", TRUE);
    test_stylesheet_csstext(stylesheet, ".div {", TRUE);
    set_stylesheet_csstext(stylesheet, "", FALSE);
    test_stylesheet_csstext(stylesheet, NULL, FALSE);
    set_stylesheet_csstext(stylesheet, ".div { margin-right: 1px; }", FALSE);
    test_stylesheet_csstext(stylesheet, ".div {", FALSE);

    IHTMLStyleSheet_Release(stylesheet);
}