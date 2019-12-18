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
typedef  int /*<<< orphan*/  IOleObject ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  int /*<<< orphan*/  IAdviseSink ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  AdviseSink ; 
 int /*<<< orphan*/  Advise_Close ; 
 int /*<<< orphan*/  CHECK_CALLED (int /*<<< orphan*/ ) ; 
 int CLIENTSITE_DONTSET ; 
 int CLIENTSITE_EXPECTPATH ; 
 int CLIENTSITE_SETNULL ; 
 int /*<<< orphan*/  CustomDocHostUIHandler ; 
 int DWL_TRYCSS ; 
 int DWL_VERBDONE ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IHTMLDocument2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IOleObject ; 
 int /*<<< orphan*/  IOleDocumentView_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IOleObject_Advise (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOleObject_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LD_DOLOAD ; 
 int /*<<< orphan*/  OLECMDF_SUPPORTED ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * create_document () ; 
 int /*<<< orphan*/ * doc_unk ; 
 int /*<<< orphan*/  init_test (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_from_stream ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  release_document (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_custom_uihandler (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_ClientSite (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_Close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_ConnectionPointContainer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_DoVerb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_GetCurMoniker (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_InPlaceDeactivate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_IsDirty (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_MSHTML_QueryStatus (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_QueryService (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_StreamLoad (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_UIDeactivate () ; 
 int /*<<< orphan*/  test_ViewAdviseSink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_download (int) ; 
 int /*<<< orphan*/  test_external (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_readyState (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace (char*) ; 
 int /*<<< orphan*/ * view ; 

__attribute__((used)) static void test_HTMLDocument_StreamLoad(void)
{
    IHTMLDocument2 *doc;
    IOleObject *oleobj;
    DWORD conn;
    HRESULT hres;

    trace("Testing HTMLDocument (IPersistStreamInit)...\n");

    init_test(LD_DOLOAD);
    load_from_stream = TRUE;

    doc = create_document();
    doc_unk = (IUnknown*)doc;

    hres = IHTMLDocument2_QueryInterface(doc, &IID_IOleObject, (void**)&oleobj);
    ok(hres == S_OK, "Could not get IOleObject: %08x\n", hres);

    hres = IOleObject_Advise(oleobj, (IAdviseSink*)&AdviseSink, &conn);
    ok(hres == S_OK, "Advise failed: %08x\n", hres);

    test_readyState((IUnknown*)doc);
    test_IsDirty(doc, S_FALSE);
    test_ViewAdviseSink(doc);
    test_ConnectionPointContainer(doc);
    test_QueryService(doc, FALSE);
    test_ClientSite(oleobj, CLIENTSITE_EXPECTPATH);
    test_QueryService(doc, TRUE);
    test_DoVerb(oleobj);
    test_MSHTML_QueryStatus(doc, OLECMDF_SUPPORTED);

    test_GetCurMoniker((IUnknown*)doc, NULL, NULL, FALSE);
    test_StreamLoad(doc);
    test_download(DWL_VERBDONE|DWL_TRYCSS);
    test_MSHTML_QueryStatus(doc, OLECMDF_SUPPORTED);

    test_UIDeactivate();
    test_InPlaceDeactivate(doc, TRUE);
    SET_EXPECT(Advise_Close);
    test_Close(doc, TRUE);
    CHECK_CALLED(Advise_Close);
    test_external(doc, FALSE);
    test_IsDirty(doc, S_FALSE);

    set_custom_uihandler(doc, &CustomDocHostUIHandler);
    test_ClientSite(oleobj, CLIENTSITE_SETNULL);
    test_external(doc, TRUE);
    test_ClientSite(oleobj, CLIENTSITE_SETNULL|CLIENTSITE_DONTSET);
    test_external(doc, TRUE);
    set_custom_uihandler(doc, NULL);
    test_ClientSite(oleobj, CLIENTSITE_SETNULL|CLIENTSITE_DONTSET);

    IOleObject_Release(oleobj);
    if(view) {
        IOleDocumentView_Release(view);
        view = NULL;
    }

    release_document(doc);
}