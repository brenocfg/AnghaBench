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
typedef  int /*<<< orphan*/  IHTMLXMLHttpRequestFactory ;
typedef  int /*<<< orphan*/  IHTMLWindow5 ;
typedef  int /*<<< orphan*/  IHTMLWindow2 ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ IDispatch_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IHTMLDocument2_get_parentWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IHTMLWindow2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IHTMLWindow2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHTMLWindow5_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLWindow5_get_XMLHttpRequest (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHTMLXMLHttpRequestFactory_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLXMLHttpRequestFactory_create (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IID_IHTMLWindow5 ; 
 int /*<<< orphan*/  IID_IHTMLXMLHttpRequestFactory ; 
 scalar_t__ S_OK ; 
 scalar_t__ VT_DISPATCH ; 
 int /*<<< orphan*/  V_DISPATCH (int /*<<< orphan*/ *) ; 
 scalar_t__ V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int /*<<< orphan*/ * xhr ; 

__attribute__((used)) static void create_xmlhttprequest(IHTMLDocument2 *doc)
{
    IHTMLWindow2 *window;
    IHTMLWindow5 *window5;
    VARIANT var;
    IHTMLXMLHttpRequestFactory *factory;
    HRESULT hres;

    hres = IHTMLDocument2_get_parentWindow(doc, &window);
    ok(hres == S_OK, "get_parentWindow failed: %08x\n", hres);
    ok(window != NULL, "window == NULL\n");

    hres = IHTMLWindow2_QueryInterface(window, &IID_IHTMLWindow5, (void**)&window5);
    IHTMLWindow2_Release(window);
    if(FAILED(hres)) {
        win_skip("IHTMLWindow5 not supported\n");
        return;
    }

    VariantInit(&var);
    hres = IHTMLWindow5_get_XMLHttpRequest(window5, &var);
    IHTMLWindow5_Release(window5);
    ok(hres == S_OK, "get_XMLHttpRequest failed: %08x\n", hres);
    ok(V_VT(&var) == VT_DISPATCH, "V_VT(&var) is %08x, expected VT_DISPATCH\n", V_VT(&var));

    hres = IDispatch_QueryInterface(V_DISPATCH(&var), &IID_IHTMLXMLHttpRequestFactory, (void**)&factory);
    VariantClear(&var);
    ok(hres == S_OK, "QueryInterface(IID_IHTMLXMLHttpRequestFactory) failed: %08x\n", hres);
    ok(factory != NULL, "factory == NULL\n");

    hres = IHTMLXMLHttpRequestFactory_create(factory, &xhr);
    IHTMLXMLHttpRequestFactory_Release(factory);
    ok(hres == S_OK, "create failed: %08x\n", hres);
    ok(xhr != NULL, "xhr == NULL\n");
}