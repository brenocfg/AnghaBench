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
typedef  int /*<<< orphan*/  (* testfunc_t ) (int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  MSG ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IHTMLElement ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DispatchMessageA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetMessageA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IHTMLDocument2_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLDocument2_get_body (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IHTMLDocument2_get_parentWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IHTMLElement_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHTMLWindow2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IPropertyNotifySink ; 
 int /*<<< orphan*/  PropertyNotifySink ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TranslateMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * create_document () ; 
 int /*<<< orphan*/  do_advise (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  doc_complete ; 
 int /*<<< orphan*/  doc_load_string (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  set_client_site (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/ * window ; 

__attribute__((used)) static void run_test(const char *str, testfunc_t test)
{
    IHTMLDocument2 *doc;
    IHTMLElement *body = NULL;
    MSG msg;
    HRESULT hres;

    doc = create_document();
    if (!doc)
        return;
    set_client_site(doc, TRUE);
    doc_load_string(doc, str);
    do_advise((IUnknown*)doc, &IID_IPropertyNotifySink, (IUnknown*)&PropertyNotifySink);

    while(!doc_complete && GetMessageA(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    hres = IHTMLDocument2_get_body(doc, &body);
    ok(hres == S_OK, "get_body failed: %08x\n", hres);

    if(body) {
        IHTMLElement_Release(body);

        hres = IHTMLDocument2_get_parentWindow(doc, &window);
        ok(hres == S_OK, "get_parentWindow failed: %08x\n", hres);
        ok(window != NULL, "window == NULL\n");

        test(doc);

        IHTMLWindow2_Release(window);
        window = NULL;
    }else {
        skip("Could not get document body. Assuming no Gecko installed.\n");
    }

    set_client_site(doc, FALSE);
    IHTMLDocument2_Release(doc);
}