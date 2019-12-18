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
typedef  int /*<<< orphan*/  IHTMLStyle ;
typedef  int /*<<< orphan*/  IHTMLElement ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  int /*<<< orphan*/  IHTMLCurrentStyle ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  IHTMLCurrentStyle_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLDocument2_get_body (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IHTMLElement_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLElement_get_style (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IHTMLStyle_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/ * get_current_style (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_element_by_id (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  test_body_style (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_current_style (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_set_csstext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_style_filters (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void basic_style_test(IHTMLDocument2 *doc)
{
    IHTMLCurrentStyle *cstyle;
    IHTMLElement *elem;
    IHTMLStyle *style;
    HRESULT hres;

    hres = IHTMLDocument2_get_body(doc, &elem);
    ok(hres == S_OK, "get_body failed: %08x\n", hres);

    hres = IHTMLElement_get_style(elem, &style);
    ok(hres == S_OK, "get_style failed: %08x\n", hres);

    test_body_style(style);

    cstyle = get_current_style(elem);
    test_current_style(cstyle);
    IHTMLCurrentStyle_Release(cstyle);
    IHTMLElement_Release(elem);

    elem = get_element_by_id(doc, "divid");
    test_style_filters(elem);

    test_set_csstext(style);
    IHTMLStyle_Release(style);
    IHTMLElement_Release(elem);
}