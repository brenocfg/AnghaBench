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
typedef  int /*<<< orphan*/  IHTMLWindow2 ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ E_FAIL ; 
 scalar_t__ E_NOINTERFACE ; 
 scalar_t__ IHTMLDocument2_get_parentWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IHTMLWindow2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IHTMLWindow2_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLWindow2_get_top (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IID_ITravelLogClient ; 
 scalar_t__ ITravelLogClient_FindWindowByIndex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITravelLogClient_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  no_travellog ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_travellog(IHTMLDocument2 *doc)
{
    ITravelLogClient *travellog_client;
    IHTMLWindow2 *window, *top_window;
    IUnknown *unk;
    HRESULT hres;

    window = NULL;
    hres = IHTMLDocument2_get_parentWindow(doc, &window);
    ok(hres == S_OK, "get_parentWindow failed: %08x\n", hres);
    ok(window != NULL, "window = NULL\n");

    hres = IHTMLWindow2_get_top(window, &top_window);
    IHTMLWindow2_Release(window);
    ok(hres == S_OK, "get_top failed: %08x\n", hres);

    hres = IHTMLWindow2_QueryInterface(top_window, &IID_ITravelLogClient, (void**)&travellog_client);
    IHTMLWindow2_Release(top_window);
    if(hres == E_NOINTERFACE) {
        win_skip("ITravelLogClient not supported\n");
        no_travellog = TRUE;
        return;
    }
    ok(hres == S_OK, "Could not get ITraveLogClient iface: %08x\n", hres);

    unk = (void*)0xdeadbeef;
    hres = ITravelLogClient_FindWindowByIndex(travellog_client, 0, &unk);
    ok(hres == E_FAIL, "FindWindowByIndex failed: %08x\n", hres);
    ok(!unk, "unk != NULL\n");

    ITravelLogClient_Release(travellog_client);
}