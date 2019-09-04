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
typedef  int /*<<< orphan*/  IServiceProvider ;
typedef  int /*<<< orphan*/  IHlinkFrame ;
typedef  int /*<<< orphan*/  IHTMLWindow2 ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ E_NOINTERFACE ; 
 int /*<<< orphan*/  HlinkFrame ; 
 scalar_t__ IHTMLDocument2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IHTMLDocument2_get_parentWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IHTMLWindow2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IHTMLWindow2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHlinkFrame_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IHTMLWindow2 ; 
 int /*<<< orphan*/  IID_IHlinkFrame ; 
 int /*<<< orphan*/  IID_IServiceProvider ; 
 scalar_t__ IServiceProvider_QueryService (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IServiceProvider_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_QueryService(IHTMLDocument2 *doc, BOOL success)
{
    IHTMLWindow2 *window, *sp_window;
    IServiceProvider *sp;
    IHlinkFrame *hf;
    HRESULT hres;

    hres = IHTMLDocument2_QueryInterface(doc, &IID_IServiceProvider, (void**)&sp);
    ok(hres == S_OK, "QueryService returned %08x\n", hres);

    hres = IServiceProvider_QueryService(sp, &IID_IHlinkFrame, &IID_IHlinkFrame, (void**)&hf);
    if(!success) {
        ok(hres == E_NOINTERFACE, "QueryService returned %08x, expected E_NOINTERFACE\n", hres);
        IServiceProvider_Release(sp);
        return;
    }

    ok(hres == S_OK, "QueryService(IID_IHlinkFrame) failed: %08x\n", hres);
    ok(hf == &HlinkFrame, "hf != HlinkFrame\n");
    IHlinkFrame_Release(hf);

    IServiceProvider_Release(sp);

    hres = IHTMLDocument2_get_parentWindow(doc, &window);
    ok(hres == S_OK, "get_parentWindow failed: %08x\n", hres);

    hres = IHTMLWindow2_QueryInterface(window, &IID_IServiceProvider, (void**)&sp);
    ok(hres == S_OK, "Could not get IServiceProvider iface: %08x\n", hres);

    hres = IServiceProvider_QueryService(sp, &IID_IHTMLWindow2, &IID_IHTMLWindow2, (void**)&sp_window);
    ok(hres == S_OK, "QueryService(IID_IHTMLWindow2) failed: %08x\n", hres);
    /* FIXME: test returned window */
    IHTMLWindow2_Release(sp_window);

    hres = IServiceProvider_QueryService(sp, &IID_IHlinkFrame, &IID_IHlinkFrame, (void**)&hf);
    ok(hres == S_OK, "QueryService(IID_IHlinkFrame) failed: %08x\n", hres);
    ok(hf == &HlinkFrame, "hf != HlinkFrame\n");
    IHlinkFrame_Release(hf);

    IServiceProvider_Release(sp);
    IHTMLWindow2_Release(window);
}