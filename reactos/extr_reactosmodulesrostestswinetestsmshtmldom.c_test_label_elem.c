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
typedef  int /*<<< orphan*/  IHTMLLabelElement ;
typedef  int /*<<< orphan*/  IHTMLElement ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  IHTMLLabelElement_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLLabelElement_get_htmlFor (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IHTMLLabelElement_put_htmlFor (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * a2bstr (char*) ; 
 int /*<<< orphan*/ * get_label_iface (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  strcmp_wa (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ wine_dbgstr_w (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_label_elem(IHTMLElement *elem)
{
    IHTMLLabelElement *label;
    BSTR str;
    HRESULT hres;

    label = get_label_iface((IUnknown*)elem);

    str = NULL;
    hres = IHTMLLabelElement_get_htmlFor(label, &str);
    ok(hres == S_OK, "get_htmlFor failed: %08x\n", hres);
    ok(!strcmp_wa(str, "in"), "htmlFor = %s\n", wine_dbgstr_w(str));
    SysFreeString(str);

    str = a2bstr("");
    hres = IHTMLLabelElement_put_htmlFor(label, str);
    ok(hres == S_OK, "put_htmlFor failed: %08x\n", hres);
    SysFreeString(str);

    str = (void*)0xdeadbeef;
    hres = IHTMLLabelElement_get_htmlFor(label, &str);
    ok(hres == S_OK, "get_htmlFor failed: %08x\n", hres);
    ok(!strcmp_wa(str, ""), "htmlFor = %s\n", wine_dbgstr_w(str));

    str = a2bstr("abc");
    hres = IHTMLLabelElement_put_htmlFor(label, str);
    ok(hres == S_OK, "put_htmlFor failed: %08x\n", hres);
    SysFreeString(str);

    str = NULL;
    hres = IHTMLLabelElement_get_htmlFor(label, &str);
    ok(hres == S_OK, "get_htmlFor failed: %08x\n", hres);
    ok(!strcmp_wa(str, "abc"), "htmlFor = %s\n", wine_dbgstr_w(str));
    SysFreeString(str);

    IHTMLLabelElement_Release(label);
}