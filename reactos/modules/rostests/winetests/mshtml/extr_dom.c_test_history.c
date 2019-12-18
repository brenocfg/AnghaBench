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
typedef  int /*<<< orphan*/  IOmHistory ;
typedef  int /*<<< orphan*/  IHTMLWindow2 ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DIID_DispHTMLHistory ; 
 scalar_t__ IHTMLWindow2_get_history (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IID_IOmHistory ; 
 int /*<<< orphan*/  IOmHistory_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  iface_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  test_disp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void test_history(IHTMLWindow2 *window)
{
    IOmHistory *history, *history2;
    HRESULT hres;

    history = NULL;
    hres = IHTMLWindow2_get_history(window, &history);
    ok(hres == S_OK, "get_history failed: %08x\n", hres);
    ok(history != NULL, "history = NULL\n");

    test_disp2((IUnknown*)history, &DIID_DispHTMLHistory, &IID_IOmHistory, "[object]");

    history2 = NULL;
    hres = IHTMLWindow2_get_history(window, &history2);
    ok(hres == S_OK, "get_history failed: %08x\n", hres);
    ok(history2 != NULL, "history2 = NULL\n");
    ok(iface_cmp((IUnknown*)history, (IUnknown*)history2), "history != history2\n");

    IOmHistory_Release(history2);
    IOmHistory_Release(history);
}