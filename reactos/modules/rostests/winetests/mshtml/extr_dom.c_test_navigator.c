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
typedef  int /*<<< orphan*/  v40 ;
typedef  int /*<<< orphan*/  buf ;
typedef  char WCHAR ;
typedef  int VARIANT_BOOL ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IOmNavigator ;
typedef  int /*<<< orphan*/  IHTMLWindow2 ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  DIID_DispHTMLNavigator ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  IHTMLDocument2_get_parentWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IHTMLWindow2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHTMLWindow2_get_navigator (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IID_IOmNavigator ; 
 int /*<<< orphan*/  IOmNavigator_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOmNavigator_get_appCodeName (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IOmNavigator_get_appMinorVersion (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IOmNavigator_get_appName (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IOmNavigator_get_appVersion (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IOmNavigator_get_browserLanguage (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IOmNavigator_get_cpuClass (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IOmNavigator_get_onLine (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IOmNavigator_get_platform (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IOmNavigator_get_systemLanguage (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IOmNavigator_get_userAgent (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IOmNavigator_get_userLanguage (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IOmNavigator_toString (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  LOCALE_SYSTEM_DEFAULT ; 
 int /*<<< orphan*/  LOCALE_USER_DEFAULT ; 
 int /*<<< orphan*/  ObtainUserAgentString (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 int VARIANT_TRUE ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pGetUserDefaultUILanguage () ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  strcmp_wa (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  test_disp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_language_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_mime_types_col (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_navigator(IHTMLDocument2 *doc)
{
    IHTMLWindow2 *window;
    IOmNavigator *navigator, *navigator2;
    VARIANT_BOOL b;
    char buf[512];
    DWORD size;
    ULONG ref;
    BSTR bstr;
    HRESULT hres;

    static const WCHAR v40[] = {'4','.','0'};

    hres = IHTMLDocument2_get_parentWindow(doc, &window);
    ok(hres == S_OK, "parentWidnow failed: %08x\n", hres);

    hres = IHTMLWindow2_get_navigator(window, &navigator);
    ok(hres == S_OK, "get_navigator failed: %08x\n", hres);
    ok(navigator != NULL, "navigator == NULL\n");
    test_disp2((IUnknown*)navigator, &DIID_DispHTMLNavigator, &IID_IOmNavigator, "[object]");

    hres = IHTMLWindow2_get_navigator(window, &navigator2);
    ok(hres == S_OK, "get_navigator failed: %08x\n", hres);
    ok(navigator != navigator2, "navigator2 != navihgator\n");

    IHTMLWindow2_Release(window);
    IOmNavigator_Release(navigator2);

    hres = IOmNavigator_get_appCodeName(navigator, &bstr);
    ok(hres == S_OK, "get_appCodeName failed: %08x\n", hres);
    ok(!strcmp_wa(bstr, "Mozilla"), "Unexpected appCodeName %s\n", wine_dbgstr_w(bstr));
    SysFreeString(bstr);

    bstr = NULL;
    hres = IOmNavigator_get_appName(navigator, &bstr);
    ok(hres == S_OK, "get_appName failed: %08x\n", hres);
    ok(!strcmp_wa(bstr, "Microsoft Internet Explorer"), "Unexpected appCodeName %s\n", wine_dbgstr_w(bstr));
    SysFreeString(bstr);

    bstr = NULL;
    hres = IOmNavigator_get_platform(navigator, &bstr);
    ok(hres == S_OK, "get_platform failed: %08x\n", hres);
    ok(!strcmp_wa(bstr, sizeof(void*) == 8 ? "Win64" : "Win32")
       || (sizeof(void*) == 8 && broken(!strcmp_wa(bstr, "Win32") /* IE6 */)), "unexpected platform %s\n", wine_dbgstr_w(bstr));
    SysFreeString(bstr);

    bstr = NULL;
    hres = IOmNavigator_get_cpuClass(navigator, &bstr);
    ok(hres == S_OK, "get_cpuClass failed: %08x\n", hres);
    ok(!strcmp_wa(bstr, sizeof(void*) == 8 ? "x64" : "x86"), "unexpected cpuClass %s\n", wine_dbgstr_w(bstr));
    SysFreeString(bstr);

    bstr = NULL;
    hres = IOmNavigator_get_appVersion(navigator, &bstr);
    ok(hres == S_OK, "get_appVersion failed: %08x\n", hres);
    ok(!memcmp(bstr, v40, sizeof(v40)), "appVersion is %s\n", wine_dbgstr_w(bstr));
    SysFreeString(bstr);

    bstr = NULL;
    hres = IOmNavigator_get_systemLanguage(navigator, &bstr);
    ok(hres == S_OK, "get_systemLanguage failed: %08x\n", hres);
    test_language_string(bstr, LOCALE_SYSTEM_DEFAULT);
    SysFreeString(bstr);

    if (pGetUserDefaultUILanguage)
    {
        bstr = NULL;
        hres = IOmNavigator_get_browserLanguage(navigator, &bstr);
        ok(hres == S_OK, "get_browserLanguage failed: %08x\n", hres);
        test_language_string(bstr, pGetUserDefaultUILanguage());
        SysFreeString(bstr);
    }
    else
        win_skip("GetUserDefaultUILanguage not available\n");

    bstr = NULL;
    hres = IOmNavigator_get_userLanguage(navigator, &bstr);
    ok(hres == S_OK, "get_userLanguage failed: %08x\n", hres);
    test_language_string(bstr, LOCALE_USER_DEFAULT);
    SysFreeString(bstr);

    hres = IOmNavigator_toString(navigator, NULL);
    ok(hres == E_INVALIDARG, "toString failed: %08x\n", hres);

    bstr = NULL;
    hres = IOmNavigator_toString(navigator, &bstr);
    ok(hres == S_OK, "toString failed: %08x\n", hres);
    ok(!strcmp_wa(bstr, "[object]"), "toString returned %s\n", wine_dbgstr_w(bstr));
    SysFreeString(bstr);

    b = 100;
    hres = IOmNavigator_get_onLine(navigator, &b);
    ok(hres == S_OK, "get_onLine failed: %08x\n", hres);
    ok(b == VARIANT_TRUE, "onLine = %x\n", b);

    size = sizeof(buf);
    hres = ObtainUserAgentString(0, buf, &size);
    ok(hres == S_OK, "ObtainUserAgentString failed: %08x\n", hres);

    bstr = NULL;
    hres = IOmNavigator_get_userAgent(navigator, &bstr);
    ok(hres == S_OK, "get_userAgent failed: %08x\n", hres);
    ok(!strcmp_wa(bstr, buf), "userAgent returned %s, expected \"%s\"\n", wine_dbgstr_w(bstr), buf);
    SysFreeString(bstr);

    if(!strncmp(buf, "Mozilla/", 8)) {
        bstr = NULL;
        hres = IOmNavigator_get_appVersion(navigator, &bstr);
        ok(hres == S_OK, "get_appVersion failed: %08x\n", hres);
        ok(!strcmp_wa(bstr, buf+8), "appVersion returned %s, expected \"%s\"\n", wine_dbgstr_w(bstr), buf+8);
        SysFreeString(bstr);
    }else {
        skip("nonstandard user agent\n");
    }

    bstr = NULL;
    hres = IOmNavigator_get_appMinorVersion(navigator, &bstr);
    ok(hres == S_OK, "get_appMonorVersion failed: %08x\n", hres);
    ok(bstr != NULL, "appMinorVersion returned NULL\n");
    SysFreeString(bstr);

    test_mime_types_col(navigator);

    ref = IOmNavigator_Release(navigator);
    ok(!ref, "navigator should be destroyed here\n");
}