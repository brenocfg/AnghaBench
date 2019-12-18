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
typedef  int /*<<< orphan*/  IHTMLFormElement ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  IHTMLFormElement_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHTMLFormElement_get_target (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHTMLFormElement_put_target (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a2bstr (char const*) ; 
 int /*<<< orphan*/ * get_form_iface (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,char const*,...) ; 
 int /*<<< orphan*/  strcmp_wa (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_form_target(IUnknown *unk)
{
    IHTMLFormElement *form = get_form_iface(unk);
    HRESULT hres;
    BSTR str;
    static const char target[] = "_blank";

    str = a2bstr(target);
    hres = IHTMLFormElement_put_target(form, str);
    ok(hres == S_OK, "put_target(%s) failed: %08x\n", target, hres);
    SysFreeString(str);

    hres = IHTMLFormElement_get_target(form, &str);
    ok(hres == S_OK, "get_target failed: %08x\n", hres);
    ok(!strcmp_wa(str, target), "Expected %s, got %s\n", target, wine_dbgstr_w(str));
    SysFreeString(str);

    IHTMLFormElement_Release(form);
}