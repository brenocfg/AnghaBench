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
typedef  int /*<<< orphan*/  url ;
struct location_test {int /*<<< orphan*/  name; int /*<<< orphan*/  url; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  IPersistMoniker ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/  IHTMLLocation ;
typedef  int /*<<< orphan*/  IHTMLDocument6 ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  int /*<<< orphan*/  IBindCtx ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int CLSCTX_INPROC_HANDLER ; 
 int CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_HTMLDocument ; 
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ CreateBindCtx (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ CreateURLMoniker (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IBindCtx_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLDocument2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IHTMLDocument2_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLDocument2_get_location (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IHTMLDocument6_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHTMLLocation_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IHTMLDocument2 ; 
 int /*<<< orphan*/  IID_IHTMLDocument6 ; 
 int /*<<< orphan*/  IID_IPersistMoniker ; 
 int /*<<< orphan*/  IMoniker_Release (int /*<<< orphan*/ *) ; 
 int INTERNET_MAX_URL_LENGTH ; 
 scalar_t__ IPersistMoniker_Load (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IPersistMoniker_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int STGM_READWRITE ; 
 int STGM_SHARE_EXCLUSIVE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  test_hash (int /*<<< orphan*/ *,struct location_test const*) ; 
 int /*<<< orphan*/  test_host (int /*<<< orphan*/ *,struct location_test const*) ; 
 int /*<<< orphan*/  test_hostname (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct location_test const*) ; 
 int /*<<< orphan*/  test_href (int /*<<< orphan*/ *,struct location_test const*) ; 
 int /*<<< orphan*/  test_pathname (int /*<<< orphan*/ *,struct location_test const*) ; 
 int /*<<< orphan*/  test_port (int /*<<< orphan*/ *,struct location_test const*) ; 
 int /*<<< orphan*/  test_protocol (int /*<<< orphan*/ *,struct location_test const*) ; 
 int /*<<< orphan*/  test_search (int /*<<< orphan*/ *,struct location_test const*) ; 
 int /*<<< orphan*/  win_skip (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void perform_test(const struct location_test* test)
{
    WCHAR url[INTERNET_MAX_URL_LENGTH];
    HRESULT hres;
    IBindCtx *bc;
    IMoniker *url_mon;
    IPersistMoniker *persist_mon;
    IHTMLDocument2 *doc;
    IHTMLDocument6 *doc6;
    IHTMLLocation *location;

    hres = CreateBindCtx(0, &bc);
    ok(hres == S_OK, "%s: CreateBindCtx failed: 0x%08x\n", test->name, hres);
    if(FAILED(hres))
        return;

    MultiByteToWideChar(CP_ACP, 0, test->url, -1, url, sizeof(url)/sizeof(WCHAR));
    hres = CreateURLMoniker(NULL, url, &url_mon);
    ok(hres == S_OK, "%s: CreateURLMoniker failed: 0x%08x\n", test->name, hres);
    if(FAILED(hres)){
        IBindCtx_Release(bc);
        return;
    }

    hres = CoCreateInstance(&CLSID_HTMLDocument, NULL,
            CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER, &IID_IHTMLDocument2,
            (void**)&doc);
    ok(hres == S_OK, "%s: CoCreateInstance failed: 0x%08x\n", test->name, hres);
    if(FAILED(hres)){
        IMoniker_Release(url_mon);
        IBindCtx_Release(bc);
        return;
    }

    hres = IHTMLDocument2_QueryInterface(doc, &IID_IHTMLDocument6, (void**)&doc6);
    if(hres == S_OK){
        IHTMLDocument6_Release(doc6);
    }else{
        win_skip("%s: Could not get IHTMLDocument6, probably too old IE. Requires IE 8+\n", test->name);
        IMoniker_Release(url_mon);
        IBindCtx_Release(bc);
        return;
    }

    hres = IHTMLDocument2_QueryInterface(doc, &IID_IPersistMoniker,
            (void**)&persist_mon);
    ok(hres == S_OK, "%s: IHTMlDocument2_QueryInterface failed: 0x%08x\n", test->name, hres);
    if(FAILED(hres)){
        IHTMLDocument2_Release(doc);
        IMoniker_Release(url_mon);
        IBindCtx_Release(bc);
        return;
    }

    hres = IPersistMoniker_Load(persist_mon, FALSE, url_mon, bc,
            STGM_SHARE_EXCLUSIVE | STGM_READWRITE);
    ok(hres == S_OK, "%s: IPersistMoniker_Load failed: 0x%08x\n", test->name, hres);
    if(FAILED(hres)){
        IPersistMoniker_Release(persist_mon);
        IHTMLDocument2_Release(doc);
        IMoniker_Release(url_mon);
        IBindCtx_Release(bc);
        return;
    }

    hres = IHTMLDocument2_get_location(doc, &location);
    ok(hres == S_OK, "%s: IHTMLDocument2_get_location failed: 0x%08x\n", test->name, hres);
    if(FAILED(hres)){
        IPersistMoniker_Release(persist_mon);
        IHTMLDocument2_Release(doc);
        IMoniker_Release(url_mon);
        IBindCtx_Release(bc);
        return;
    }

    test_href(location, test);
    test_protocol(location, test);
    test_host(location, test);
    test_hostname(location, doc, test);
    test_port(location, test);
    test_pathname(location, test);
    test_search(location, test);
    test_hash(location, test);

    IHTMLLocation_Release(location);
    IPersistMoniker_Release(persist_mon);
    IHTMLDocument2_Release(doc);
    IMoniker_Release(url_mon);
    IBindCtx_Release(bc);
}