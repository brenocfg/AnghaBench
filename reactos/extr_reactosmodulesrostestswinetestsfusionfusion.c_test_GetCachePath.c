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
typedef  char WCHAR ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int ASM_CACHE_GAC ; 
 int ASM_CACHE_ROOT ; 
 int ASM_CACHE_ZAP ; 
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ E_NOT_SUFFICIENT_BUFFER ; 
 int /*<<< orphan*/  GetWindowsDirectoryA (int /*<<< orphan*/ *,int) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,int) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  lstrcatW (char*,char const*) ; 
 int /*<<< orphan*/  lstrcmpW (char const*,char*) ; 
 int /*<<< orphan*/  lstrcpyA (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lstrcpyW (char*,char const*) ; 
 scalar_t__ lstrlenW (char*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  pGetCORVersion (char*,int,scalar_t__*) ; 
 scalar_t__ pGetCachePath (int,char*,scalar_t__*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 scalar_t__ wine_dbgstr_w (char const*) ; 
 int /*<<< orphan*/  wsprintfA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_GetCachePath(void)
{
    CHAR windirA[MAX_PATH];
    WCHAR windir[MAX_PATH];
    WCHAR cachepath[MAX_PATH];
    WCHAR version[MAX_PATH];
    WCHAR path[MAX_PATH];
    DWORD size;
    HRESULT hr;

    static const WCHAR backslash[] = {'\\',0};
    static const WCHAR nochange[] = {'n','o','c','h','a','n','g','e',0};
    static const WCHAR assembly[] = {'a','s','s','e','m','b','l','y',0};
    static const WCHAR gac[] = {'G','A','C',0};

    if (!pGetCachePath)
    {
        win_skip("GetCachePath not implemented\n");
        return;
    }

    GetWindowsDirectoryA(windirA, MAX_PATH);
    MultiByteToWideChar(CP_ACP, 0, windirA, -1, windir, MAX_PATH);
    lstrcpyW(cachepath, windir);
    lstrcatW(cachepath, backslash);
    lstrcatW(cachepath, assembly);
    lstrcatW(cachepath, backslash);
    lstrcatW(cachepath, gac);

    /* NULL pwzCachePath, pcchPath is 0 */
    size = 0;
    hr = pGetCachePath(ASM_CACHE_GAC, NULL, &size);
    ok(hr == E_NOT_SUFFICIENT_BUFFER, "Expected E_NOT_SUFFICIENT_BUFFER, got %08x\n", hr);
    ok(size == lstrlenW(cachepath) + 1,
       "Expected %d, got %d\n", lstrlenW(cachepath) + 1, size);

    /* NULL pwszCachePath, pcchPath is MAX_PATH */
    size = MAX_PATH;
    hr = pGetCachePath(ASM_CACHE_GAC, NULL, &size);
    ok(hr == E_NOT_SUFFICIENT_BUFFER, "Expected E_NOT_SUFFICIENT_BUFFER, got %08x\n", hr);
    ok(size == lstrlenW(cachepath) + 1,
       "Expected %d, got %d\n", lstrlenW(cachepath) + 1, size);

    /* both pwszCachePath and pcchPath NULL */
    hr = pGetCachePath(ASM_CACHE_GAC, NULL, NULL);
    ok(hr == E_INVALIDARG, "Expected E_INVALIDARG, got %08x\n", hr);

    /* NULL pcchPath */
    lstrcpyW(path, nochange);
    hr = pGetCachePath(ASM_CACHE_GAC, path, NULL);
    ok(hr == E_INVALIDARG, "Expected E_INVALIDARG, got %08x\n", hr);
    ok( !lstrcmpW( nochange, path ), "Expected %s,  got %s\n", wine_dbgstr_w(nochange), wine_dbgstr_w(path));

    /* get the cache path */
    lstrcpyW(path, nochange);
    size = MAX_PATH;
    hr = pGetCachePath(ASM_CACHE_GAC, path, &size);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok( !lstrcmpW( cachepath, path ), "Expected %s,  got %s\n", wine_dbgstr_w(cachepath), wine_dbgstr_w(path));

    /* pcchPath has no room for NULL terminator */
    lstrcpyW(path, nochange);
    size = lstrlenW(cachepath);
    hr = pGetCachePath(ASM_CACHE_GAC, path, &size);
    ok(hr == E_NOT_SUFFICIENT_BUFFER, "Expected E_NOT_SUFFICIENT_BUFFER, got %08x\n", hr);
    ok( !lstrcmpW( nochange, path ), "Expected %s,  got %s\n", wine_dbgstr_w(nochange), wine_dbgstr_w(path));

    lstrcpyW(cachepath, windir);
    lstrcatW(cachepath, backslash);
    lstrcatW(cachepath, assembly);

    /* ASM_CACHE_ROOT */
    lstrcpyW(path, nochange);
    size = MAX_PATH;
    hr = pGetCachePath(ASM_CACHE_ROOT, path, &size);
    ok(hr == S_OK ||
       broken(hr == E_INVALIDARG), /* .NET 1.1 */
       "Expected S_OK, got %08x\n", hr);
    if (hr == S_OK)
        ok( !lstrcmpW( cachepath, path ), "Expected %s,  got %s\n", wine_dbgstr_w(cachepath), wine_dbgstr_w(path));

    if (pGetCORVersion)
    {
        CHAR versionA[MAX_PATH];
        CHAR cachepathA[MAX_PATH];
        CHAR nativeimgA[MAX_PATH];
        CHAR zapfmtA[MAX_PATH];

        if (hr == S_OK)
        {
            lstrcpyA(nativeimgA, "NativeImages_");
#ifdef _WIN64
            lstrcpyA(zapfmtA, "%s\\%s\\%s%s_64");
#else
            lstrcpyA(zapfmtA, "%s\\%s\\%s%s_32");
#endif
        }
        else
        {
            lstrcpyA(nativeimgA, "NativeImages1_");
            lstrcpyA(zapfmtA, "%s\\%s\\%s%s");
        }

        pGetCORVersion(version, MAX_PATH, &size);
        WideCharToMultiByte(CP_ACP, 0, version, -1, versionA, MAX_PATH, 0, 0);

        wsprintfA(cachepathA, zapfmtA, windirA, "assembly", nativeimgA, versionA);
        MultiByteToWideChar(CP_ACP, 0, cachepathA, -1, cachepath, MAX_PATH);

        /* ASM_CACHE_ZAP */
        lstrcpyW(path, nochange);
        size = MAX_PATH;
        hr = pGetCachePath(ASM_CACHE_ZAP, path, &size);
        ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
        ok( !lstrcmpW( cachepath, path ), "Expected %s,  got %s\n", wine_dbgstr_w(cachepath), wine_dbgstr_w(path));
    }

    /* two flags at once */
    lstrcpyW(path, nochange);
    size = MAX_PATH;
    hr = pGetCachePath(ASM_CACHE_GAC | ASM_CACHE_ROOT, path, &size);
    ok(hr == E_INVALIDARG, "Expected E_INVALIDARG, got %08x\n", hr);
    ok( !lstrcmpW( nochange, path ), "Expected %s,  got %s\n", wine_dbgstr_w(nochange), wine_dbgstr_w(path));
}