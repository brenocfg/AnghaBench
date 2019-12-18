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
typedef  int /*<<< orphan*/  IHTMLDocument ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int CLSCTX_INPROC_HANDLER ; 
 int CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_XMLView ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ IHTMLDocument_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IHTMLDocument_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IHTMLDocument ; 
 int /*<<< orphan*/  IID_IOleCommandTarget ; 
 int /*<<< orphan*/  IID_IOleObject ; 
 int /*<<< orphan*/  IID_IPersistHistory ; 
 int /*<<< orphan*/  IID_IPersistMoniker ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 scalar_t__ IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_QueryInterface(void)
{
    IUnknown *xmlview, *unk;
    IHTMLDocument *htmldoc;
    HRESULT hres;

    hres = CoCreateInstance(&CLSID_XMLView, NULL, CLSCTX_INPROC_SERVER|CLSCTX_INPROC_HANDLER,
            &IID_IUnknown, (void**)&xmlview);
    if(FAILED(hres)) {
        win_skip("Failed to create XMLView instance\n");
        return;
    }
    ok(hres == S_OK, "CoCreateInstance returned %x, expected S_OK\n", hres);

    hres = IUnknown_QueryInterface(xmlview, &IID_IPersistMoniker, (void**)&unk);
    ok(hres == S_OK, "QueryInterface(IID_IPersistMoniker) returned %x, expected S_OK\n", hres);
    IUnknown_Release(unk);

    hres = IUnknown_QueryInterface(xmlview, &IID_IPersistHistory, (void**)&unk);
    ok(hres == S_OK, "QueryInterface(IID_IPersistHistory) returned %x, expected S_OK\n", hres);
    IUnknown_Release(unk);

    hres = IUnknown_QueryInterface(xmlview, &IID_IOleCommandTarget, (void**)&unk);
    ok(hres == S_OK, "QueryInterface(IID_IOleCommandTarget) returned %x, expected S_OK\n", hres);
    IUnknown_Release(unk);

    hres = IUnknown_QueryInterface(xmlview, &IID_IOleObject, (void**)&unk);
    ok(hres == S_OK, "QueryInterface(IID_IOleObject) returned %x, expected S_OK\n", hres);
    IUnknown_Release(unk);

    hres = IUnknown_QueryInterface(xmlview, &IID_IHTMLDocument, (void**)&htmldoc);
    ok(hres == S_OK, "QueryInterface(IID_IHTMLDocument) returned %x, expected S_OK\n", hres);
    hres = IHTMLDocument_QueryInterface(htmldoc, &IID_IUnknown, (void**)&unk);
    ok(hres == S_OK, "QueryInterface(IID_IUnknown) returned %x, expected S_OK\n", hres);
    ok(unk == xmlview, "Aggregation is not working as expected\n");
    IUnknown_Release(unk);
    IHTMLDocument_Release(htmldoc);

    IUnknown_Release(xmlview);
}