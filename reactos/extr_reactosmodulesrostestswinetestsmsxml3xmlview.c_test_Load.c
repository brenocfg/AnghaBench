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
typedef  int /*<<< orphan*/  MSG ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IPersistMoniker ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/  IHTMLElement ;
typedef  int /*<<< orphan*/  IConnectionPointContainer ;
typedef  int /*<<< orphan*/  IConnectionPoint ;
typedef  int /*<<< orphan*/  IBindCtx ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (char const*) ; 
 int CLSCTX_INPROC_HANDLER ; 
 int CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_XMLView ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ CreateBindCtx (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  DispatchMessageA (int /*<<< orphan*/ *) ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetMessageA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetModuleFileNameW (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  HTMLEvents ; 
 int /*<<< orphan*/  IBindCtx_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IConnectionPointContainer_FindConnectionPoint (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IConnectionPointContainer_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IConnectionPoint_Advise (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IConnectionPoint_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHTMLDocument2_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLDocument2_get_body (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IHTMLElement_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLElement_get_outerHTML (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IConnectionPointContainer ; 
 int /*<<< orphan*/  IID_IDispatch ; 
 int /*<<< orphan*/  IID_IHTMLDocument2 ; 
 int /*<<< orphan*/  IID_IPersistMoniker ; 
 int /*<<< orphan*/  IMoniker_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IPersistMoniker_Load (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IPersistMoniker_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IPersistMoniker_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TranslateMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * html_doc ; 
 int /*<<< orphan*/  html_src_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loaded ; 
 int /*<<< orphan*/  lstrcatW (char*,char const*) ; 
 int /*<<< orphan*/  lstrcpyW (char*,char const*) ; 
 int lstrlenW (char*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pCreateURLMoniker (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 scalar_t__ wine_dbgstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlview_html ; 

__attribute__((used)) static void test_Load(void)
{
    static const WCHAR xmlview_xmlW[] = {'/','x','m','l','/','x','m','l','v','i','e','w','.','x','m','l',0};
    static const WCHAR res[] = {'r','e','s',':','/','/',0};

    WCHAR buf[1024];
    IPersistMoniker *pers_mon;
    IConnectionPointContainer *cpc;
    IConnectionPoint *cp;
    IMoniker *mon;
    IBindCtx *bctx;
    IHTMLElement *elem;
    HRESULT hres;
    MSG msg;
    BSTR source;

    lstrcpyW(buf, res);
    GetModuleFileNameW(NULL, buf+lstrlenW(buf), ARRAY_SIZE(buf)-ARRAY_SIZE(res));
    lstrcatW(buf, xmlview_xmlW);

    if(!pCreateURLMoniker) {
        win_skip("CreateURLMoniker not available\n");
        return;
    }

    hres = CoCreateInstance(&CLSID_XMLView, NULL, CLSCTX_INPROC_SERVER|CLSCTX_INPROC_HANDLER,
            &IID_IPersistMoniker, (void**)&pers_mon);
    if(FAILED(hres)) {
        win_skip("Failed to create XMLView instance\n");
        return;
    }
    ok(hres == S_OK, "CoCreateInstance returned %x, expected S_OK\n", hres);

    hres = IPersistMoniker_QueryInterface(pers_mon, &IID_IHTMLDocument2, (void**)&html_doc);
    ok(hres == S_OK, "QueryInterface(HTMLDocument2) returned %x, expected S_OK\n", hres);
    hres = IPersistMoniker_QueryInterface(pers_mon, &IID_IConnectionPointContainer, (void**)&cpc);
    ok(hres == S_OK, "QueryInterface(IConnectionPointContainer) returned %x, expected S_OK\n", hres);
    hres = IConnectionPointContainer_FindConnectionPoint(cpc, &IID_IDispatch, &cp);
    ok(hres == S_OK, "FindConnectionPoint returned %x, expected S_OK\n", hres);
    hres = IConnectionPoint_Advise(cp, (IUnknown*)&HTMLEvents, NULL);
    ok(hres == S_OK, "Advise returned %x, expected S_OK\n", hres);
    IConnectionPoint_Release(cp);
    IConnectionPointContainer_Release(cpc);

    hres = CreateBindCtx(0, &bctx);
    ok(hres == S_OK, "CreateBindCtx returned %x, expected S_OK\n", hres);
    hres = pCreateURLMoniker(NULL, buf, &mon);
    ok(hres == S_OK, "CreateUrlMoniker returned %x, expected S_OK\n", hres);
    loaded = FALSE;
    hres = IPersistMoniker_Load(pers_mon, TRUE, mon, bctx, 0);
    ok(hres == S_OK, "Load returned %x, expected S_OK\n", hres);
    IBindCtx_Release(bctx);
    IMoniker_Release(mon);

    while(!loaded && GetMessageA(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    hres = IHTMLDocument2_get_body(html_doc, &elem);
    ok(hres == S_OK, "get_body returned %x, expected S_OK\n", hres);
    hres = IHTMLElement_get_outerHTML(elem, &source);
    ok(hres == S_OK, "get_outerHTML returned %x, expected S_OK\n", hres);
    ok(!html_src_compare(source, xmlview_html), "Incorrect HTML source: %s\n", wine_dbgstr_w(source));
    IHTMLElement_Release(elem);
    SysFreeString(source);

    IHTMLDocument2_Release(html_doc);
    html_doc = NULL;
    IPersistMoniker_Release(pers_mon);
}