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
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IHTMLXMLHttpRequestFactory ;
typedef  int /*<<< orphan*/  IHTMLXMLHttpRequest ;
typedef  int /*<<< orphan*/  IHTMLWindow5 ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DIID_DispHTMLXMLHttpRequest ; 
 scalar_t__ IDispatch_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IHTMLWindow5_get_XMLHttpRequest (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHTMLXMLHttpRequestFactory_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLXMLHttpRequestFactory_create (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IHTMLXMLHttpRequest_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IHTMLXMLHttpRequestFactory ; 
 scalar_t__ S_OK ; 
 scalar_t__ VT_DISPATCH ; 
 int /*<<< orphan*/  V_DISPATCH (int /*<<< orphan*/ *) ; 
 scalar_t__ V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_variant (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  test_disp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void test_xmlhttprequest(IHTMLWindow5 *window)
{
    HRESULT hres;
    VARIANT var;
    IHTMLXMLHttpRequestFactory *factory;
    IHTMLXMLHttpRequest *xml;

    hres = IHTMLWindow5_get_XMLHttpRequest(window, &var);
    ok(hres == S_OK, "get_XMLHttpRequest failed: %08x\n", hres);
    ok(V_VT(&var) == VT_DISPATCH, "expect VT_DISPATCH, got %s\n", debugstr_variant(&var));

    factory = NULL;
    hres = IDispatch_QueryInterface(V_DISPATCH(&var), &IID_IHTMLXMLHttpRequestFactory, (void**)&factory);
    ok(hres == S_OK, "QueryInterface(&IID_IHTMLXMLHttpRequestFactory) failed: %08x\n", hres);
    ok(factory != NULL, "factory == NULL\n");

    xml = NULL;
    hres = IHTMLXMLHttpRequestFactory_create(factory, &xml);
    ok(hres == S_OK, "create failed: %08x\n", hres);
    ok(xml != NULL, "xml == NULL\n");
    test_disp((IUnknown*)xml, &DIID_DispHTMLXMLHttpRequest, "[object]");

    IHTMLXMLHttpRequest_Release(xml);
    IHTMLXMLHttpRequestFactory_Release(factory);
    VariantClear(&var);
}