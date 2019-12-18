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
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENTSITE_EXPECTPATH ; 
 int /*<<< orphan*/  CLIENTSITE_SETNULL ; 
 int /*<<< orphan*/  CallUIActivate_AfterShow ; 
 int /*<<< orphan*/  CallUIActivate_None ; 
 int /*<<< orphan*/  CustomDocHostUIHandler ; 
 int DWL_CSS ; 
 int DWL_TRYCSS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IOleDocumentView_Release (int /*<<< orphan*/ *) ; 
 int IsWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_DOLOAD ; 
 int /*<<< orphan*/  LD_NO ; 
 int /*<<< orphan*/  Moniker ; 
 int /*<<< orphan*/  OLECMDF_SUPPORTED ; 
 int /*<<< orphan*/  S_FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  call_UIActivate ; 
 int /*<<< orphan*/ * create_document () ; 
 int /*<<< orphan*/  doc_hwnd ; 
 int /*<<< orphan*/ * doc_unk ; 
 int /*<<< orphan*/  init_test (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  release_document (int /*<<< orphan*/ *) ; 
 scalar_t__ report_mime ; 
 int /*<<< orphan*/  set_custom_uihandler (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_Activate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_Advise (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_Close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_CloseView () ; 
 int /*<<< orphan*/  test_ConnectionPointContainer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_GetCurMoniker (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_Hide () ; 
 int /*<<< orphan*/  test_InPlaceDeactivate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_IsDirty (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_MSHTML_QueryStatus (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_OleCommandTarget (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_OleCommandTarget_fail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_OnAmbientPropertyChange (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_OnAmbientPropertyChange2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_Persist (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_QueryInterface (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_UIDeactivate () ; 
 int /*<<< orphan*/  test_ViewAdviseSink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_Window (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_download (int) ; 
 int /*<<< orphan*/  test_elem_from_point (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_exec_optical_zoom (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_external (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_target_container (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace (char*,char*,char*) ; 
 int /*<<< orphan*/ * view ; 

__attribute__((used)) static void test_HTMLDocument(BOOL do_load, BOOL mime)
{
    IHTMLDocument2 *doc;

    trace("Testing HTMLDocument (%s, %s)...\n", (do_load ? "load" : "no load"),
            (report_mime ? "mime" : "no mime"));

    init_test(do_load ? LD_DOLOAD : LD_NO);
    report_mime = mime;

    doc = create_document();
    doc_unk = (IUnknown*)doc;

    test_QueryInterface(doc);
    test_Advise(doc);
    test_IsDirty(doc, S_FALSE);
    test_MSHTML_QueryStatus(doc, OLECMDF_SUPPORTED);
    test_external(doc, FALSE);
    test_ViewAdviseSink(doc);
    test_ConnectionPointContainer(doc);
    test_GetCurMoniker((IUnknown*)doc, NULL, NULL, FALSE);
    test_Persist(doc, &Moniker);
    if(!do_load)
        test_OnAmbientPropertyChange2(doc);

    test_Activate(doc, CLIENTSITE_EXPECTPATH);

    if(do_load) {
        set_custom_uihandler(doc, &CustomDocHostUIHandler);
        test_download(DWL_CSS|DWL_TRYCSS);
        test_GetCurMoniker((IUnknown*)doc, &Moniker, NULL, FALSE);
        test_elem_from_point(doc);
    }

    test_MSHTML_QueryStatus(doc, OLECMDF_SUPPORTED);
    test_OleCommandTarget_fail(doc);
    test_OleCommandTarget(doc);
    test_exec_optical_zoom(doc, 200);
    test_exec_optical_zoom(doc, 100);
    test_OnAmbientPropertyChange(doc);
    test_Window(doc, TRUE);
    test_external(doc, TRUE);
    test_target_container(doc);

    test_UIDeactivate();
    test_OleCommandTarget(doc);
    test_Window(doc, TRUE);
    test_InPlaceDeactivate(doc, TRUE);

    /* Calling test_OleCommandTarget here causes Segmentation Fault with native
     * MSHTML. It doesn't with Wine. */

    test_Window(doc, FALSE);
    test_Hide();
    test_InPlaceDeactivate(doc, FALSE);
    test_CloseView();
    test_Close(doc, FALSE);

    /* Activate HTMLDocument again */
    test_Activate(doc, CLIENTSITE_SETNULL);
    test_Window(doc, TRUE);
    test_OleCommandTarget(doc);
    test_UIDeactivate();
    test_InPlaceDeactivate(doc, TRUE);
    test_Close(doc, FALSE);

    /* Activate HTMLDocument again, this time without UIActivate */
    call_UIActivate = CallUIActivate_None;
    test_Activate(doc, CLIENTSITE_SETNULL);
    test_Window(doc, TRUE);

    test_external(doc, TRUE);
    set_custom_uihandler(doc, NULL);
    test_external(doc, FALSE);

    test_UIDeactivate();
    test_InPlaceDeactivate(doc, TRUE);
    test_CloseView();
    test_CloseView();
    test_Close(doc, TRUE);
    test_OnAmbientPropertyChange2(doc);
    test_GetCurMoniker((IUnknown*)doc, do_load ? &Moniker : NULL, NULL, FALSE);

    if(!do_load) {
        /* Activate HTMLDocument again, calling UIActivate after showing the window */
        call_UIActivate = CallUIActivate_AfterShow;
        test_Activate(doc, 0);
        test_Window(doc, TRUE);
        test_OleCommandTarget(doc);
        test_UIDeactivate();
        test_InPlaceDeactivate(doc, TRUE);
        test_Close(doc, FALSE);
        call_UIActivate = CallUIActivate_None;
    }

    if(view)
        IOleDocumentView_Release(view);
    view = NULL;

    ok(IsWindow(doc_hwnd), "hwnd is destroyed\n");
    release_document(doc);
    ok(!IsWindow(doc_hwnd), "hwnd is not destroyed\n");
}