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
typedef  int /*<<< orphan*/  IHTMLFrameBase ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ BSTR ;

/* Variables and functions */
 scalar_t__ E_INVALIDARG ; 
 int /*<<< orphan*/  IHTMLFrameBase_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLFrameBase_get_frameBorder (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ IHTMLFrameBase_get_scrolling (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ IHTMLFrameBase_put_frameBorder (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ IHTMLFrameBase_put_scrolling (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  IID_IHTMLFrameBase ; 
 scalar_t__ IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (scalar_t__) ; 
 scalar_t__ a2bstr (char*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  set_framebase_marginheight (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  set_framebase_marginwidth (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strcmp_wa (scalar_t__,char*) ; 
 int /*<<< orphan*/  test_framebase_marginheight (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_framebase_marginwidth (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ wine_dbgstr_w (scalar_t__) ; 

__attribute__((used)) static void test_framebase(IUnknown *unk)
{
    IHTMLFrameBase *fbase;
    BSTR str;
    HRESULT hres;

    /* get/put scrolling */
    hres = IUnknown_QueryInterface(unk, &IID_IHTMLFrameBase, (void**)&fbase);
    ok(hres == S_OK, "Could not get IHTMLFrameBase interface: 0x%08x\n", hres);

    hres = IHTMLFrameBase_get_scrolling(fbase, &str);
    ok(hres == S_OK, "IHTMLFrameBase_get_scrolling failed: 0x%08x\n", hres);
    ok(!strcmp_wa(str, "auto"), "get_scrolling should have given 'auto', gave: %s\n", wine_dbgstr_w(str));
    SysFreeString(str);

    str = a2bstr("no");
    hres = IHTMLFrameBase_put_scrolling(fbase, str);
    ok(hres == S_OK, "IHTMLFrameBase_put_scrolling failed: 0x%08x\n", hres);
    SysFreeString(str);

    hres = IHTMLFrameBase_get_scrolling(fbase, &str);
    ok(hres == S_OK, "IHTMLFrameBase_get_scrolling failed: 0x%08x\n", hres);
    ok(!strcmp_wa(str, "no"), "get_scrolling should have given 'no', gave: %s\n", wine_dbgstr_w(str));
    SysFreeString(str);

    str = a2bstr("junk");
    hres = IHTMLFrameBase_put_scrolling(fbase, str);
    ok(hres == E_INVALIDARG, "IHTMLFrameBase_put_scrolling should have failed "
            "with E_INVALIDARG, instead: 0x%08x\n", hres);
    SysFreeString(str);

    hres = IHTMLFrameBase_get_scrolling(fbase, &str);
    ok(hres == S_OK, "IHTMLFrameBase_get_scrolling failed: 0x%08x\n", hres);
    ok(!strcmp_wa(str, "no"), "get_scrolling should have given 'no', gave: %s\n", wine_dbgstr_w(str));
    SysFreeString(str);

    hres = IHTMLFrameBase_get_frameBorder(fbase, &str);
    ok(hres == S_OK, "get_frameBorder failed: %08x\n", hres);
    ok(!str, "frameBorder = %s\n", wine_dbgstr_w(str));

    str = a2bstr("1");
    hres = IHTMLFrameBase_put_frameBorder(fbase, str);
    ok(hres == S_OK, "put_frameBorder failed: %08x\n", hres);
    SysFreeString(str);

    hres = IHTMLFrameBase_get_frameBorder(fbase, &str);
    ok(hres == S_OK, "get_frameBorder failed: %08x\n", hres);
    ok(!strcmp_wa(str, "1"), "frameBorder = %s, expected \"1\"\n", wine_dbgstr_w(str));

    test_framebase_marginheight(fbase, NULL);
    set_framebase_marginheight(fbase, "1px");
    test_framebase_marginheight(fbase, "1");

    test_framebase_marginwidth(fbase, NULL);
    set_framebase_marginwidth(fbase, "2px");
    test_framebase_marginwidth(fbase, "2");

    IHTMLFrameBase_Release(fbase);
}