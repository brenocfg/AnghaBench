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
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CustomDocHostUIHandler ; 
 int DWL_CSS ; 
 int DWL_TRYCSS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HTTP_STATUS_OK ; 
 int /*<<< orphan*/  IOleDocumentView_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LD_DOLOAD ; 
 int /*<<< orphan*/  Moniker ; 
 int /*<<< orphan*/  OLECMDF_SUPPORTED ; 
 int /*<<< orphan*/  S_FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * create_document () ; 
 int /*<<< orphan*/ * doc_unk ; 
 int /*<<< orphan*/  init_test (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipsex ; 
 int /*<<< orphan*/  release_document (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_custom_uihandler (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  status_code ; 
 int /*<<< orphan*/  test_Close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_ConnectionPointContainer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_GetCurMoniker (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_InPlaceDeactivate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_IsDirty (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_MSHTML_QueryStatus (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_Navigate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_Persist (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_ViewAdviseSink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_Window (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_download (int) ; 
 int /*<<< orphan*/  test_exec_onunload (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace (char*) ; 
 int /*<<< orphan*/ * view ; 

__attribute__((used)) static void test_HTMLDocument_hlink(DWORD status)
{
    IHTMLDocument2 *doc;

    trace("Testing HTMLDocument (hlink)...\n");

    init_test(LD_DOLOAD);
    ipsex = TRUE;

    doc = create_document();
    doc_unk = (IUnknown*)doc;

    set_custom_uihandler(doc, &CustomDocHostUIHandler);
    test_ViewAdviseSink(doc);
    test_ConnectionPointContainer(doc);
    test_GetCurMoniker((IUnknown*)doc, NULL, NULL, FALSE);
    test_Persist(doc, &Moniker);
    test_Navigate(doc);

    status_code = status;
    test_download(DWL_CSS|DWL_TRYCSS);
    status_code = HTTP_STATUS_OK;

    test_IsDirty(doc, S_FALSE);
    test_MSHTML_QueryStatus(doc, OLECMDF_SUPPORTED);

    test_exec_onunload(doc);
    test_Window(doc, TRUE);
    test_InPlaceDeactivate(doc, TRUE);
    test_Close(doc, FALSE);
    test_IsDirty(doc, S_FALSE);
    test_GetCurMoniker((IUnknown*)doc, &Moniker, NULL, FALSE);
    test_clear(doc);
    test_GetCurMoniker((IUnknown*)doc, &Moniker, NULL, FALSE);

    if(view)
        IOleDocumentView_Release(view);
    view = NULL;

    release_document(doc);
}