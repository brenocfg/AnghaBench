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
typedef  int /*<<< orphan*/  urlA ;
typedef  int /*<<< orphan*/  url ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  MSG ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IPersistMoniker ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_CALLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ CreateURLMoniker (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  DispatchMessageW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetMessageW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetModuleFileNameA (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ IHTMLDocument2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IHTMLDocument2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IPersistMoniker ; 
 int /*<<< orphan*/  IID_IPropertyNotifySink ; 
 int /*<<< orphan*/  IMoniker_Release (int /*<<< orphan*/ *) ; 
 int INTERNET_MAX_URL_LENGTH ; 
 scalar_t__ IPersistMoniker_Load (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPersistMoniker_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PropertyNotifySink ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TranslateMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  called_external_success ; 
 int /*<<< orphan*/ * create_document () ; 
 int /*<<< orphan*/  do_advise (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  external_success ; 
 int /*<<< orphan*/  lstrcatA (char*,char const*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,char const*) ; 
 int lstrlenA (char const*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  set_client_site (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (char*,char const*) ; 

__attribute__((used)) static void run_js_script(const char *test_name)
{
    WCHAR url[INTERNET_MAX_URL_LENGTH];
    char urlA[INTERNET_MAX_URL_LENGTH];
    IPersistMoniker *persist;
    IHTMLDocument2 *doc;
    IMoniker *mon;
    MSG msg;
    HRESULT hres;

    static const char res[] = "res://";

    trace("running %s...\n", test_name);

    doc = create_document();
    if(!doc)
        return;

    set_client_site(doc, TRUE);
    do_advise(doc, &IID_IPropertyNotifySink, (IUnknown*)&PropertyNotifySink);

    lstrcpyA(urlA, res);
    GetModuleFileNameA(NULL, urlA + lstrlenA(res), sizeof(urlA) - lstrlenA(res));
    lstrcatA(urlA, "/");
    lstrcatA(urlA, test_name);
    MultiByteToWideChar(CP_ACP, 0, urlA, -1, url, sizeof(url)/sizeof(WCHAR));

    hres = CreateURLMoniker(NULL, url, &mon);
    ok(hres == S_OK, "CreateURLMoniker failed: %08x\n", hres);

    hres = IHTMLDocument2_QueryInterface(doc, &IID_IPersistMoniker, (void**)&persist);
    ok(hres == S_OK, "Could not get IPersistMoniker iface: %08x\n", hres);

    hres = IPersistMoniker_Load(persist, FALSE, mon, NULL, 0);
    ok(hres == S_OK, "Load failed: %08x\n", hres);

    IMoniker_Release(mon);
    IPersistMoniker_Release(persist);

    SET_EXPECT(external_success);

    while(!called_external_success && GetMessageW(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    CHECK_CALLED(external_success);

    set_client_site(doc, FALSE);
    IHTMLDocument2_Release(doc);
}