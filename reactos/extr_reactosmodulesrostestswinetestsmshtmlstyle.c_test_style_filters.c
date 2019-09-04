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
typedef  int /*<<< orphan*/  IHTMLStyle ;
typedef  int /*<<< orphan*/  IHTMLElement2 ;
typedef  int /*<<< orphan*/  IHTMLElement ;
typedef  int /*<<< orphan*/  IHTMLCurrentStyle2 ;
typedef  int /*<<< orphan*/  IHTMLCurrentStyle ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  IHTMLCurrentStyle2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHTMLElement2_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLElement2_get_currentStyle (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IHTMLElement_get_style (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IHTMLStyle_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  VARIANT_FALSE ; 
 int /*<<< orphan*/  VARIANT_TRUE ; 
 int /*<<< orphan*/ * get_current_style2_iface (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_elem2_iface (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  set_style_filter (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_current_style_filter (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_style_filter (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_style_remove_attribute (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_style_filters(IHTMLElement *elem)
{
    IHTMLElement2 *elem2 = get_elem2_iface((IUnknown*)elem);
    IHTMLCurrentStyle2 *current_style2;
    IHTMLCurrentStyle *current_style;
    IHTMLStyle *style;
    HRESULT hres;

    hres = IHTMLElement_get_style(elem, &style);
    ok(hres == S_OK, "get_style failed: %08x\n", hres);

    hres = IHTMLElement2_get_currentStyle(elem2, &current_style);
    ok(hres == S_OK, "get_style failed: %08x\n", hres);

    current_style2 = get_current_style2_iface((IUnknown*)current_style);

    test_style_filter(style, NULL);
    test_current_style_filter(current_style2, NULL);
    set_style_filter(style, "alpha(opacity=50.0040)");
    test_current_style_filter(current_style2, "alpha(opacity=50.0040)");
    set_style_filter(style, "alpha(opacity=100)");

    IHTMLStyle_Release(style);

    hres = IHTMLElement_get_style(elem, &style);
    ok(hres == S_OK, "get_style failed: %08x\n", hres);

    test_style_filter(style, "alpha(opacity=100)");
    set_style_filter(style, "xxx(a,b,c) alpha(opacity=100)");
    set_style_filter(style, NULL);
    set_style_filter(style, "alpha(opacity=100)");
    test_style_remove_attribute(style, "filter", VARIANT_TRUE);
    test_style_remove_attribute(style, "filter", VARIANT_FALSE);
    test_style_filter(style, NULL);


    IHTMLCurrentStyle2_Release(current_style2);
    IHTMLStyle_Release(style);
    IHTMLElement2_Release(elem2);
}