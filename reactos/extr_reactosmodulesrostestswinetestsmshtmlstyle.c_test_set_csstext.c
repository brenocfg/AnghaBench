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
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  IHTMLStyle ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ IHTMLStyle_get_backgroundColor (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 scalar_t__ VT_BSTR ; 
 int /*<<< orphan*/  V_BSTR (int /*<<< orphan*/ *) ; 
 scalar_t__ V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  strcmp_wa (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test_style_set_csstext (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ wine_dbgstr_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_set_csstext(IHTMLStyle *style)
{
    VARIANT v;
    HRESULT hres;

    test_style_set_csstext(style, "background-color: black;");

    hres = IHTMLStyle_get_backgroundColor(style, &v);
    ok(hres == S_OK, "get_backgroundColor: %08x\n", hres);
    ok(V_VT(&v) == VT_BSTR, "type failed: %d\n", V_VT(&v));
    ok(!strcmp_wa(V_BSTR(&v), "black"), "str=%s\n", wine_dbgstr_w(V_BSTR(&v)));
    VariantClear(&v);
}