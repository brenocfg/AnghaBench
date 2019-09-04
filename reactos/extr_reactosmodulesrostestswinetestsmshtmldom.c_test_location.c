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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IHTMLWindow2 ;
typedef  int /*<<< orphan*/  IHTMLLocation ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  DIID_DispHTMLLocation ; 
 scalar_t__ E_POINTER ; 
 scalar_t__ IHTMLDocument2_get_location (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IHTMLDocument2_get_parentWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IHTMLLocation_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLLocation_get_href (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLLocation_get_pathname (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLWindow2_get_location (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IID_IHTMLLocation ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  location_iids ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strcmp_wa (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test_disp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_ifaces (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_location(IHTMLDocument2 *doc)
{
    IHTMLLocation *location, *location2;
    IHTMLWindow2 *window;
    BSTR str;
    ULONG ref;
    HRESULT hres;

    hres = IHTMLDocument2_get_location(doc, &location);
    ok(hres == S_OK, "get_location failed: %08x\n", hres);

    hres = IHTMLDocument2_get_location(doc, &location2);
    ok(hres == S_OK, "get_location failed: %08x\n", hres);

    ok(location == location2, "location != location2\n");
    IHTMLLocation_Release(location2);

    hres = IHTMLDocument2_get_parentWindow(doc, &window);
    ok(hres == S_OK, "get_parentWindow failed: %08x\n", hres);

    hres = IHTMLWindow2_get_location(window, &location2);
    ok(hres == S_OK, "get_location failed: %08x\n", hres);
    ok(location == location2, "location != location2\n");
    IHTMLLocation_Release(location2);

    test_ifaces((IUnknown*)location, location_iids);
    test_disp2((IUnknown*)location, &DIID_DispHTMLLocation, &IID_IHTMLLocation, "about:blank");

    hres = IHTMLLocation_get_pathname(location, &str);
    ok(hres == S_OK, "get_pathname failed: %08x\n", hres);
    ok(!strcmp_wa(str, "blank"), "unexpected pathname %s\n", wine_dbgstr_w(str));
    SysFreeString(str);

    hres = IHTMLLocation_get_href(location, NULL);
    ok(hres == E_POINTER, "get_href passed: %08x\n", hres);

    hres = IHTMLLocation_get_href(location, &str);
    ok(hres == S_OK, "get_href failed: %08x\n", hres);
    ok(!strcmp_wa(str, "about:blank"), "unexpected href %s\n", wine_dbgstr_w(str));
    SysFreeString(str);

    ref = IHTMLLocation_Release(location);
    ok(!ref, "location chould be destroyed here\n");
}