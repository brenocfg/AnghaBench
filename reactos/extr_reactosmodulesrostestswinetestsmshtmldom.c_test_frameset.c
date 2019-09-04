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
typedef  int /*<<< orphan*/  IHTMLFramesCollection2 ;
typedef  int /*<<< orphan*/  IHTMLElement ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ IHTMLDocument2_get_frames (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IHTMLElement_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHTMLFramesCollection2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHTMLWindow2_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLWindow2_get_frames (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/ * get_doc_elem_by_id (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * get_doc_window (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  test_elem_id (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_framebase (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_framebase_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_framebase_put_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_framebase_src (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_frames_collection (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void test_frameset(IHTMLDocument2 *doc)
{
    IHTMLWindow2 *window;
    IHTMLFramesCollection2 *frames;
    IHTMLElement *elem;
    HRESULT hres;

    window = get_doc_window(doc);

    /* test using IHTMLFramesCollection object */

    hres = IHTMLWindow2_get_frames(window, &frames);
    ok(hres == S_OK, "IHTMLWindow2_get_frames failed: 0x%08x\n", hres);
    if(FAILED(hres))
        return;

    test_frames_collection(frames, "fr1");
    IHTMLFramesCollection2_Release(frames);

    hres = IHTMLDocument2_get_frames(doc, &frames);
    ok(hres == S_OK, "IHTMLDocument2_get_frames failed: 0x%08x\n", hres);
    if(FAILED(hres))
        return;

    test_frames_collection(frames, "fr1");
    IHTMLFramesCollection2_Release(frames);

    /* test using IHTMLWindow2 inheritance */
    test_frames_collection((IHTMLFramesCollection2*)window, "fr2");

    /* getElementById with node name attributes */
    elem = get_doc_elem_by_id(doc, "nm1");
    test_elem_id((IUnknown*)elem, "fr1");

    test_framebase((IUnknown*)elem);
    test_framebase_name(elem, "nm1");
    test_framebase_put_name(elem, "frame name");
    test_framebase_put_name(elem, NULL);
    test_framebase_put_name(elem, "nm1");
    test_framebase_src(elem, "about:blank");
    IHTMLElement_Release(elem);

    /* get_name with no name attr */
    elem = get_doc_elem_by_id(doc, "fr3");
    test_framebase_name(elem, NULL);
    test_framebase_put_name(elem, "frame name");
    test_framebase_put_name(elem, NULL);
    IHTMLElement_Release(elem);

    IHTMLWindow2_Release(window);
}