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
typedef  int /*<<< orphan*/  IHTMLWindow2 ;
typedef  int /*<<< orphan*/  IHTMLFrameElement3 ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHTMLDocument2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHTMLFrameElement3_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHTMLFrameElement3_get_contentDocument (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IHTMLWindow2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IHTMLFrameElement3 ; 
 int /*<<< orphan*/  IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/ * get_elem_doc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_frame_content_window (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_window_doc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iface_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  test_ifaces (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int /*<<< orphan*/  window_iids ; 

__attribute__((used)) static void test_frame_doc(IUnknown *frame_elem, BOOL iframe)
{
    IHTMLDocument2 *window_doc, *elem_doc;
    IHTMLFrameElement3 *frame_elem3;
    IHTMLWindow2 *content_window;
    HRESULT hres;

    content_window = get_frame_content_window(frame_elem);
    test_ifaces((IUnknown*)content_window, window_iids);
    window_doc = get_window_doc(content_window);
    IHTMLWindow2_Release(content_window);

    elem_doc = get_elem_doc(frame_elem);
    ok(iface_cmp((IUnknown*)window_doc, (IUnknown*)elem_doc), "content_doc != elem_doc\n");

    if(!iframe) {
        hres = IUnknown_QueryInterface(frame_elem, &IID_IHTMLFrameElement3, (void**)&frame_elem3);
        if(SUCCEEDED(hres)) {
            IDispatch *disp = NULL;

            hres = IHTMLFrameElement3_get_contentDocument(frame_elem3, &disp);
            ok(hres == S_OK, "get_contentDocument failed: %08x\n", hres);
            ok(disp != NULL, "contentDocument == NULL\n");
            ok(iface_cmp((IUnknown*)disp, (IUnknown*)window_doc), "contentDocument != contentWindow.document\n");

            IDispatch_Release(disp);
            IHTMLFrameElement3_Release(frame_elem3);
        }else {
            win_skip("IHTMLFrameElement3 not supported\n");
        }
    }

    IHTMLDocument2_Release(elem_doc);
    IHTMLDocument2_Release(window_doc);
}