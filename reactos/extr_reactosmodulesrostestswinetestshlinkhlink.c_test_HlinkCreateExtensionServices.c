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
typedef  unsigned char WCHAR ;
typedef  void* LPWSTR ;
typedef  int /*<<< orphan*/  IHttpNegotiate ;
typedef  int /*<<< orphan*/  IAuthenticate ;
typedef  void* HWND ;
typedef  void* HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CoTaskMemFree (void*) ; 
 void* E_INVALIDARG ; 
 void* HlinkCreateExtensionServices (unsigned char const*,void*,unsigned char const*,unsigned char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 void* IAuthenticate_Authenticate (int /*<<< orphan*/ *,void**,void**,void**) ; 
 void* IAuthenticate_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IAuthenticate_Release (int /*<<< orphan*/ *) ; 
 void* IHttpNegotiate_BeginningTransaction (int /*<<< orphan*/ *,void*,void*,int /*<<< orphan*/ ,void**) ; 
 void* IHttpNegotiate_OnResponse (int /*<<< orphan*/ *,int,void*,void*,void**) ; 
 int /*<<< orphan*/  IHttpNegotiate_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IAuthenticate ; 
 int /*<<< orphan*/  IID_IHttpNegotiate ; 
 void* S_OK ; 
 int /*<<< orphan*/  lstrcmpW (void*,unsigned char const*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 void* wine_dbgstr_w (void*) ; 

__attribute__((used)) static void test_HlinkCreateExtensionServices(void)
{
    IAuthenticate *authenticate;
    IHttpNegotiate *http_negotiate;
    LPWSTR password, username, headers;
    HWND hwnd;
    HRESULT hres;

    static const WCHAR usernameW[] = {'u','s','e','r',0};
    static const WCHAR passwordW[] = {'p','a','s','s',0};
    static const WCHAR headersW[] = {'h','e','a','d','e','r','s',0};
    static const WCHAR headersexW[] = {'h','e','a','d','e','r','s','\r','\n',0};

    hres = HlinkCreateExtensionServices(NULL, NULL, NULL, NULL,
                                        NULL, &IID_IAuthenticate, (void**)&authenticate);
    ok(hres == S_OK, "HlinkCreateExtensionServices failed: %08x\n", hres);
    ok(authenticate != NULL, "HlinkCreateExtensionServices returned NULL\n");

    password = username = (void*)0xdeadbeef;
    hwnd = (void*)0xdeadbeef;
    hres = IAuthenticate_Authenticate(authenticate, &hwnd, &username, &password);
    ok(hres == S_OK, "Authenticate failed: %08x\n", hres);
    ok(!hwnd, "hwnd != NULL\n");
    ok(!username, "username != NULL\n");
    ok(!password, "password != NULL\n");

    hres = IAuthenticate_QueryInterface(authenticate, &IID_IHttpNegotiate, (void**)&http_negotiate);
    ok(hres == S_OK, "Could not get IHttpNegotiate interface: %08x\n", hres);

    headers = (void*)0xdeadbeef;
    hres = IHttpNegotiate_BeginningTransaction(http_negotiate, (void*)0xdeadbeef, (void*)0xdeadbeef,
                                               0, &headers);
    ok(hres == S_OK, "BeginningTransaction failed: %08x\n", hres);
    ok(headers == NULL, "headers != NULL\n");

    hres = IHttpNegotiate_BeginningTransaction(http_negotiate, (void*)0xdeadbeef, (void*)0xdeadbeef,
                                               0, NULL);
    ok(hres == E_INVALIDARG, "BeginningTransaction failed: %08x, expected E_INVALIDARG\n", hres);

    headers = (void*)0xdeadbeef;
    hres = IHttpNegotiate_OnResponse(http_negotiate, 200, (void*)0xdeadbeef, (void*)0xdeadbeef, &headers);
    ok(hres == S_OK, "OnResponse failed: %08x\n", hres);
    ok(headers == NULL, "headers != NULL\n");

    IHttpNegotiate_Release(http_negotiate);
    IAuthenticate_Release(authenticate);


    hres = HlinkCreateExtensionServices(headersW, (HWND)0xfefefefe, usernameW, passwordW,
                                        NULL, &IID_IAuthenticate, (void**)&authenticate);
    ok(hres == S_OK, "HlinkCreateExtensionServices failed: %08x\n", hres);
    ok(authenticate != NULL, "HlinkCreateExtensionServices returned NULL\n");

    password = username = NULL;
    hwnd = NULL;
    hres = IAuthenticate_Authenticate(authenticate, &hwnd, &username, &password);
    ok(hres == S_OK, "Authenticate failed: %08x\n", hres);
    ok(hwnd == (HWND)0xfefefefe, "hwnd=%p\n", hwnd);
    ok(!lstrcmpW(username, usernameW), "unexpected username\n");
    ok(!lstrcmpW(password, passwordW), "unexpected password\n");
    CoTaskMemFree(username);
    CoTaskMemFree(password);

    password = username = (void*)0xdeadbeef;
    hwnd = (void*)0xdeadbeef;
    hres = IAuthenticate_Authenticate(authenticate, &hwnd, NULL, &password);
    ok(hres == E_INVALIDARG, "Authenticate failed: %08x\n", hres);
    ok(password == (void*)0xdeadbeef, "password = %p\n", password);
    ok(hwnd == (void*)0xdeadbeef, "hwnd = %p\n", hwnd);

    hres = IAuthenticate_QueryInterface(authenticate, &IID_IHttpNegotiate, (void**)&http_negotiate);
    ok(hres == S_OK, "Could not get IHttpNegotiate interface: %08x\n", hres);

    headers = (void*)0xdeadbeef;
    hres = IHttpNegotiate_BeginningTransaction(http_negotiate, (void*)0xdeadbeef, (void*)0xdeadbeef,
                                               0, &headers);
    ok(hres == S_OK, "BeginningTransaction failed: %08x\n", hres);
    ok(!lstrcmpW(headers, headersexW), "unexpected headers %s\n", wine_dbgstr_w(headers));
    CoTaskMemFree(headers);

    headers = (void*)0xdeadbeef;
    hres = IHttpNegotiate_OnResponse(http_negotiate, 200, (void*)0xdeadbeef, (void*)0xdeadbeef, &headers);
    ok(hres == S_OK, "OnResponse failed: %08x\n", hres);
    ok(headers == NULL, "unexpected headers %s\n", wine_dbgstr_w(headers));

    IHttpNegotiate_Release(http_negotiate);
    IAuthenticate_Release(authenticate);
}