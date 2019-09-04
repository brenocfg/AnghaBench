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
typedef  int /*<<< orphan*/  IHTMLWindow2 ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_CALLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetExternal ; 
 scalar_t__ IHTMLDocument2_get_parentWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IHTMLWindow2_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLWindow2_get_external (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_external(IHTMLDocument2 *doc, BOOL initialized)
{
    IDispatch *external;
    IHTMLWindow2 *htmlwin;
    HRESULT hres;

    hres = IHTMLDocument2_get_parentWindow(doc, &htmlwin);
    ok(hres == S_OK, "get_parentWindow failed: %08x\n", hres);

    if(initialized)
        SET_EXPECT(GetExternal);
    external = (void*)0xdeadbeef;
    hres = IHTMLWindow2_get_external(htmlwin, &external);
    if(initialized) {
        ok(hres == S_FALSE || hres == S_OK, "get_external failed: %08x\n", hres);
        CHECK_CALLED(GetExternal);
        ok(external != NULL, "external == NULL\n");
    }else {
        ok(hres == S_OK, "get_external failed: %08x\n", hres);
        ok(external == NULL, "external != NULL\n");
    }

    IHTMLWindow2_Release(htmlwin);
}