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
typedef  char WCHAR ;
typedef  char OLECHAR ;
typedef  int /*<<< orphan*/  MSG ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IHTMLElement ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ DISPID ;

/* Variables and functions */
 scalar_t__ DISPID_IHTMLBODYELEMENT_BACKGROUND ; 
 int /*<<< orphan*/  DispatchMessageW (int /*<<< orphan*/ *) ; 
 scalar_t__ GetMessageW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IHTMLDocument2_get_body (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IHTMLElement_GetIDsOfNames (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**,int,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  IHTMLElement_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IPropertyNotifySink ; 
 int /*<<< orphan*/  IID_NULL ; 
 int /*<<< orphan*/  LOCALE_USER_DEFAULT ; 
 int /*<<< orphan*/  PropertyNotifySink ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TranslateMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_advise (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  doc_complete ; 
 int /*<<< orphan*/  load_string (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void load_doc(IHTMLDocument2 *doc, const char *str)
{
    IHTMLElement *body = NULL;
    MSG msg;
    HRESULT hres;
    static const WCHAR ucPtr[] = {'b','a','c','k','g','r','o','u','n','d',0};
    DISPID dispID = -1;
    OLECHAR *name;

    load_string(doc, str);
    do_advise(doc, &IID_IPropertyNotifySink, (IUnknown*)&PropertyNotifySink);

    while(!doc_complete && GetMessageW(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    hres = IHTMLDocument2_get_body(doc, &body);
    ok(hres == S_OK, "get_body failed: %08x\n", hres);

    /* Check we can query for function on the IHTMLElementBody interface */
    name = (WCHAR*)ucPtr;
    hres = IHTMLElement_GetIDsOfNames(body, &IID_NULL, &name, 1, LOCALE_USER_DEFAULT, &dispID);
    ok(hres == S_OK, "GetIDsOfNames(background) failed %08x\n", hres);
    ok(dispID == DISPID_IHTMLBODYELEMENT_BACKGROUND, "Incorrect dispID got (%d)\n", dispID);

    IHTMLElement_Release(body);
}