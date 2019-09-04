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
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CreateURLMoniker (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  DWL_EXPECT_HISTUPDATE ; 
 int /*<<< orphan*/  DWL_EXTERNAL ; 
 int /*<<< orphan*/  DWL_HTTP ; 
 scalar_t__ FALSE ; 
 scalar_t__ IMoniker_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOleDocumentView_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LD_DOLOAD ; 
 int /*<<< orphan*/  OLECMDF_SUPPORTED ; 
 int /*<<< orphan*/  S_FALSE ; 
 scalar_t__ S_OK ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/ * create_document () ; 
 int /*<<< orphan*/ * doc_unk ; 
 int /*<<< orphan*/  http_urlW ; 
 int /*<<< orphan*/  init_test (int /*<<< orphan*/ ) ; 
 scalar_t__ ipsex ; 
 scalar_t__ is_ie_hardened () ; 
 void* nav_serv_url ; 
 void* nav_url ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/ * prev_url ; 
 int /*<<< orphan*/  release_document (int /*<<< orphan*/ *) ; 
 scalar_t__ support_wbapp ; 
 int /*<<< orphan*/  test_Close (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  test_ConnectionPointContainer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_GetCurMoniker (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  test_InPlaceDeactivate (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  test_IsDirty (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_MSHTML_QueryStatus (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_Navigate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_OmHistory (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_Persist (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_ViewAdviseSink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_binding_ui (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_cookies (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_download (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_load_history (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_open_window (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  test_put_hash (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_put_href (int /*<<< orphan*/ *,scalar_t__,char*,char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_refresh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_travellog (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_window_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace (char*,char*) ; 
 int /*<<< orphan*/ * view ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int /*<<< orphan*/  winetest_interactive ; 

__attribute__((used)) static void test_HTMLDocument_http(BOOL with_wbapp)
{
    IMoniker *http_mon;
    IHTMLDocument2 *doc;
    ULONG ref;
    HRESULT hres;

    trace("Testing HTMLDocument (http%s)...\n", with_wbapp ? " with IWebBrowserApp" : "");

    support_wbapp = with_wbapp;

    if(!winetest_interactive && is_ie_hardened()) {
        win_skip("IE running in Enhanced Security Configuration\n");
        return;
    }

    init_test(LD_DOLOAD);
    ipsex = TRUE;

    doc = create_document();
    doc_unk = (IUnknown*)doc;

    hres = CreateURLMoniker(NULL, http_urlW, &http_mon);
    ok(hres == S_OK, "CreateURLMoniker failed: %08x\n", hres);

    test_ViewAdviseSink(doc);
    test_ConnectionPointContainer(doc);
    test_GetCurMoniker((IUnknown*)doc, NULL, NULL, FALSE);
    test_Persist(doc, http_mon);
    test_Navigate(doc);
    test_download(DWL_HTTP);
    test_cookies(doc);
    test_IsDirty(doc, S_FALSE);
    test_MSHTML_QueryStatus(doc, OLECMDF_SUPPORTED);
    test_GetCurMoniker((IUnknown*)doc, http_mon, NULL, FALSE);
    test_travellog(doc);
    test_binding_ui((IUnknown*)doc);

    nav_url = nav_serv_url = "http://test.winehq.org/tests/winehq_snapshot/"; /* for valid prev nav_url */
    if(support_wbapp) {
        test_put_href(doc, FALSE, "#test", "http://test.winehq.org/tests/winehq_snapshot/#test", FALSE, TRUE, 0);
        test_put_hash(doc, "#hash_test");
        test_travellog(doc);
        test_refresh(doc);
    }
    test_put_href(doc, FALSE, NULL, "javascript:external%20&&undefined", TRUE, FALSE, 0);
    test_put_href(doc, FALSE, NULL, "about:blank", FALSE, FALSE, support_wbapp ? DWL_EXPECT_HISTUPDATE : 0);
    test_put_href(doc, TRUE, NULL, "about:replace", FALSE, FALSE, 0);
    if(support_wbapp) {
        test_load_history(doc);
        test_OmHistory(doc);
        test_put_href(doc, FALSE, NULL, "about:blank", FALSE, FALSE, support_wbapp ? DWL_EXPECT_HISTUPDATE : 0);
    }

    prev_url = nav_serv_url;
    test_open_window(doc, TRUE);
    if(!support_wbapp) /* FIXME */
        test_open_window(doc, FALSE);
    if(support_wbapp) {
        test_put_href(doc, FALSE, NULL, "http://test.winehq.org/tests/file.winetest", FALSE, FALSE, DWL_EXTERNAL);
        test_window_close(doc);
    }

    test_InPlaceDeactivate(doc, TRUE);
    test_Close(doc, FALSE);
    test_IsDirty(doc, S_FALSE);
    test_GetCurMoniker((IUnknown*)doc, NULL, prev_url, support_wbapp);

    if(view)
        IOleDocumentView_Release(view);
    view = NULL;

    release_document(doc);

    ref = IMoniker_Release(http_mon);
    ok(!ref, "ref=%d, expected 0\n", ref);
}