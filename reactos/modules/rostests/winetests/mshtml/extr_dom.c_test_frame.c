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
typedef  int /*<<< orphan*/  ITravelLogClient ;
typedef  int /*<<< orphan*/  IObjectIdentity ;
typedef  int /*<<< orphan*/  IHTMLWindow4 ;
typedef  int /*<<< orphan*/  IHTMLWindow2 ;
typedef  int /*<<< orphan*/  IHTMLFrameBase ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ET_FRAME ; 
 scalar_t__ E_NOINTERFACE ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IDispatch_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IHTMLDocument2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHTMLFrameBase_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLWindow2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IHTMLWindow2_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLWindow2_get_document (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IHTMLWindow2_get_parent (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IHTMLWindow2_get_top (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IHTMLWindow4_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLWindow4_get_frameElement (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IID_IHTMLWindow2 ; 
 int /*<<< orphan*/  IID_IHTMLWindow4 ; 
 int /*<<< orphan*/  IID_IObjectIdentity ; 
 int /*<<< orphan*/  IID_ITravelLogClient ; 
 scalar_t__ IObjectIdentity_IsEqualObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IObjectIdentity_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITravelLogClient_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  obj_ident_test ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  test_doc_title (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_elem_id (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  test_elem_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_frame_doc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_frame(IDispatch *disp, const char *exp_id)
{
    IHTMLWindow2 *frame2, *parent, *top;
    IHTMLDocument2 *parent_doc, *top_doc;
    IHTMLWindow4 *frame;
    IHTMLFrameBase *frame_elem;
    IObjectIdentity *obj_ident;
    ITravelLogClient *tlc;
    HRESULT hres;

    hres = IDispatch_QueryInterface(disp, &IID_IHTMLWindow4, (void**)&frame);
    ok(hres == S_OK, "Could not get IHTMLWindow4 interface: 0x%08x\n", hres);
    if(FAILED(hres))
        return;

    hres = IHTMLWindow4_get_frameElement(frame, &frame_elem);
    ok(hres == S_OK, "IHTMLWindow4_get_frameElement failed: 0x%08x\n", hres);
    IHTMLWindow4_Release(frame);
    if(FAILED(hres))
        return;

    test_elem_type((IUnknown*)frame_elem, ET_FRAME);
    test_frame_doc((IUnknown*)frame_elem, FALSE);
    test_elem_id((IUnknown*)frame_elem, exp_id);
    IHTMLFrameBase_Release(frame_elem);

    hres = IDispatch_QueryInterface(disp, &IID_IHTMLWindow2, (void**)&frame2);
    ok(hres == S_OK, "Could not get IHTMLWindow2 interface: 0x%08x\n", hres);
    if(FAILED(hres))
        return;

    hres = IHTMLWindow2_get_parent(frame2, &parent);
    ok(hres == S_OK, "IHTMLWindow2_get_parent failed: 0x%08x\n", hres);
    if(FAILED(hres)){
        IHTMLWindow2_Release(frame2);
        return;
    }

    hres = IHTMLWindow2_QueryInterface(frame2, &IID_IObjectIdentity, (void**)&obj_ident);
    ok(hres == S_OK, "Could not get IObjectIdentity interface: %08x\n", hres);
    hres = IHTMLWindow2_QueryInterface(frame2, &IID_ITravelLogClient, (void**)&tlc);
    if(hres == E_NOINTERFACE) {
        win_skip("IID_ITravelLogClient not available\n");
        tlc = NULL;
    }else {
        ok(hres == S_OK, "Could not get ITravelLogClient interface: %08x\n", hres);

        hres = IObjectIdentity_IsEqualObject(obj_ident, (IUnknown*)tlc);
        ok(hres == S_OK, "IsEqualObject returned: 0x%08x\n", hres);
        ITravelLogClient_Release(tlc);
    }

    hres = IObjectIdentity_IsEqualObject(obj_ident, (IUnknown*)obj_ident);
    ok(hres == S_OK, "IsEqualObject returned: 0x%08x\n", hres);
    hres = IObjectIdentity_IsEqualObject(obj_ident, (IUnknown*)parent);
    ok(hres == S_FALSE, "IsEqualObject returned: 0x%08x\n", hres);
    hres = IObjectIdentity_IsEqualObject(obj_ident, &obj_ident_test);
    ok(hres == E_NOINTERFACE, "IsEqualObject returned: 0x%08x\n", hres);

    IObjectIdentity_Release(obj_ident);

    hres = IHTMLWindow2_get_document(parent, &parent_doc);
    ok(hres == S_OK, "IHTMLWindow2_get_document failed: 0x%08x\n", hres);
    IHTMLWindow2_Release(parent);
    if(FAILED(hres)){
        IHTMLWindow2_Release(frame2);
        return;
    }

    test_doc_title(parent_doc, "frameset test");
    IHTMLDocument2_Release(parent_doc);

    /* test get_top */
    hres = IHTMLWindow2_get_top(frame2, &top);
    ok(hres == S_OK, "IHTMLWindow2_get_top failed: 0x%08x\n", hres);
    IHTMLWindow2_Release(frame2);
    if(FAILED(hres))
        return;

    hres = IHTMLWindow2_get_document(top, &top_doc);
    ok(hres == S_OK, "IHTMLWindow2_get_document failed: 0x%08x\n", hres);
    IHTMLWindow2_Release(top);
    if(FAILED(hres))
        return;

    test_doc_title(top_doc, "frameset test");
    IHTMLDocument2_Release(top_doc);
}