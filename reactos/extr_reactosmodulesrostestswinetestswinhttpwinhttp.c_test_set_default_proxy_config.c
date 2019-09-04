#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int dwAccessType; int* lpszProxy; int* lpszProxyBypass; } ;
typedef  TYPE_1__ WINHTTP_PROXY_INFO ;
typedef  int WCHAR ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int ERROR_ACCESS_DENIED ; 
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_SUCCESS ; 
 int GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int WINHTTP_ACCESS_TYPE_NAMED_PROXY ; 
 int WinHttpSetDefaultProxyConfiguration (TYPE_1__*) ; 
 scalar_t__ broken (int) ; 
 scalar_t__ get_default_proxy_reg_value (int /*<<< orphan*/ *,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  set_default_proxy_reg_value (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_set_default_proxy_config(void)
{
    static WCHAR wideString[] = { 0x226f, 0x575b, 0 };
    static WCHAR normalString[] = { 'f','o','o',0 };
    DWORD type, len;
    BYTE *saved_proxy_settings = NULL;
    WINHTTP_PROXY_INFO info;
    BOOL ret;

    /* FIXME: it would be simpler to read the current settings using
     * WinHttpGetDefaultProxyConfiguration and save them using
     * WinHttpSetDefaultProxyConfiguration, but they appear to have a bug.
     *
     * If a proxy is configured in the registry, e.g. via 'proxcfg -p "foo"',
     * the access type reported by WinHttpGetDefaultProxyConfiguration is 1,
     * WINHTTP_ACCESS_TYPE_NO_PROXY, whereas it should be
     * WINHTTP_ACCESS_TYPE_NAMED_PROXY.
     * If WinHttpSetDefaultProxyConfiguration is called with dwAccessType = 1,
     * the lpszProxy and lpszProxyBypass values are ignored.
     * Thus, if a proxy is set with proxycfg, then calling
     * WinHttpGetDefaultProxyConfiguration followed by
     * WinHttpSetDefaultProxyConfiguration results in the proxy settings
     * getting deleted from the registry.
     *
     * Instead I read the current registry value and restore it directly.
     */
    len = get_default_proxy_reg_value( NULL, 0, &type );
    if (len)
    {
        saved_proxy_settings = HeapAlloc( GetProcessHeap(), 0, len );
        len = get_default_proxy_reg_value( saved_proxy_settings, len, &type );
    }

    if (0)
    {
        /* Crashes on Vista and higher */
        SetLastError(0xdeadbeef);
        ret = WinHttpSetDefaultProxyConfiguration(NULL);
        ok(!ret && GetLastError() == ERROR_INVALID_PARAMETER,
            "expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());
    }

    /* test with invalid access type */
    info.dwAccessType = 0xdeadbeef;
    info.lpszProxy = info.lpszProxyBypass = NULL;
    SetLastError(0xdeadbeef);
    ret = WinHttpSetDefaultProxyConfiguration(&info);
    ok(!ret && GetLastError() == ERROR_INVALID_PARAMETER,
        "expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

    /* at a minimum, the proxy server must be set */
    info.dwAccessType = WINHTTP_ACCESS_TYPE_NAMED_PROXY;
    info.lpszProxy = info.lpszProxyBypass = NULL;
    SetLastError(0xdeadbeef);
    ret = WinHttpSetDefaultProxyConfiguration(&info);
    ok(!ret && GetLastError() == ERROR_INVALID_PARAMETER,
        "expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());
    info.lpszProxyBypass = normalString;
    SetLastError(0xdeadbeef);
    ret = WinHttpSetDefaultProxyConfiguration(&info);
    ok(!ret && GetLastError() == ERROR_INVALID_PARAMETER,
        "expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

    /* the proxy server can't have wide characters */
    info.lpszProxy = wideString;
    SetLastError(0xdeadbeef);
    ret = WinHttpSetDefaultProxyConfiguration(&info);
    if (!ret && GetLastError() == ERROR_ACCESS_DENIED)
        skip("couldn't set default proxy configuration: access denied\n");
    else
        ok((!ret && GetLastError() == ERROR_INVALID_PARAMETER) ||
           broken(ret), /* Earlier winhttp versions on W2K/XP */
           "expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

    info.lpszProxy = normalString;
    SetLastError(0xdeadbeef);
    ret = WinHttpSetDefaultProxyConfiguration(&info);
    if (!ret && GetLastError() == ERROR_ACCESS_DENIED)
        skip("couldn't set default proxy configuration: access denied\n");
    else
    {
        ok(ret, "WinHttpSetDefaultProxyConfiguration failed: %u\n", GetLastError());
        ok(GetLastError() == ERROR_SUCCESS ||  broken(GetLastError() == 0xdeadbeef) /* < win7 */,
           "got %u\n", GetLastError());
    }
    set_default_proxy_reg_value( saved_proxy_settings, len, type );
}