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
typedef  int /*<<< orphan*/  IHTMLElement3 ;
typedef  char* HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  IHTMLElement3_Release (int /*<<< orphan*/ *) ; 
 char* IHTMLElement3_get_contentEditable (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* IHTMLElement3_put_contentEditable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a2bstr (char*) ; 
 int /*<<< orphan*/ * get_elem3_iface (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,char*,...) ; 
 int /*<<< orphan*/  strcmp_wa (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_contenteditable(IUnknown *unk)
{
    IHTMLElement3 *elem3 = get_elem3_iface(unk);
    HRESULT hres;
    BSTR str, strDefault;

    hres = IHTMLElement3_get_contentEditable(elem3, &strDefault);
    ok(hres == S_OK, "get_contentEditable failed: 0x%08x\n", hres);

    str = a2bstr("true");
    hres = IHTMLElement3_put_contentEditable(elem3, str);
    ok(hres == S_OK, "put_contentEditable(%s) failed: 0x%08x\n", wine_dbgstr_w(str), hres);
    SysFreeString(str);
    hres = IHTMLElement3_get_contentEditable(elem3, &str);
    ok(hres == S_OK, "get_contentEditable failed: 0x%08x\n", hres);
    ok(!strcmp_wa(str, "true"), "Got %s, expected %s\n", wine_dbgstr_w(str), "true");

    /* Restore origin contentEditable */
    hres = IHTMLElement3_put_contentEditable(elem3, strDefault);
    ok(hres == S_OK, "put_contentEditable(%s) failed: 0x%08x\n", wine_dbgstr_w(strDefault), hres);
    SysFreeString(strDefault);

    IHTMLElement3_Release(elem3);
}