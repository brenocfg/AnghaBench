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
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char*) ; 
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ E_POINTER ; 
 int /*<<< orphan*/  GetLastError () ; 
 int INTERNET_MAX_URL_LENGTH ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int URL_ESCAPE_UNSAFE ; 
 int URL_WININET_COMPATIBILITY ; 
 int lstrlenW (char*) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 scalar_t__ pUrlCanonicalizeW (char*,char*,int*,int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 char* winehqW ; 

__attribute__((used)) static void test_UrlCanonicalizeW(void)
{
    WCHAR szReturnUrl[INTERNET_MAX_URL_LENGTH];
    DWORD dwSize;
    DWORD urllen;
    HRESULT hr;
    int i;


    if (!pUrlCanonicalizeW) {
        win_skip("UrlCanonicalizeW not found\n");
        return;
    }
    urllen = lstrlenW(winehqW);

    /* buffer has no space for the result */
    dwSize = (urllen-1);
    memset(szReturnUrl, '#', (urllen+4) * sizeof(WCHAR));
    szReturnUrl[urllen+4] = '\0';
    SetLastError(0xdeadbeef);
    hr = pUrlCanonicalizeW(winehqW, szReturnUrl, &dwSize, URL_WININET_COMPATIBILITY | URL_ESCAPE_UNSAFE);
    ok( (hr == E_POINTER) && (dwSize == (urllen + 1)),
        "got 0x%x with %u and size %u for %u (expected 'E_POINTER' and size %u)\n",
        hr, GetLastError(), dwSize, lstrlenW(szReturnUrl), urllen+1);


    /* buffer has no space for the terminating '\0' */
    dwSize = urllen;
    memset(szReturnUrl, '#', (urllen+4) * sizeof(WCHAR));
    szReturnUrl[urllen+4] = '\0';
    SetLastError(0xdeadbeef);
    hr = pUrlCanonicalizeW(winehqW, szReturnUrl, &dwSize, URL_WININET_COMPATIBILITY | URL_ESCAPE_UNSAFE);
    ok( (hr == E_POINTER) && (dwSize == (urllen + 1)),
        "got 0x%x with %u and size %u for %u (expected 'E_POINTER' and size %u)\n",
        hr, GetLastError(), dwSize, lstrlenW(szReturnUrl), urllen+1);

    /* buffer has the required size */
    dwSize = urllen +1;
    memset(szReturnUrl, '#', (urllen+4) * sizeof(WCHAR));
    szReturnUrl[urllen+4] = '\0';
    SetLastError(0xdeadbeef);
    hr = pUrlCanonicalizeW(winehqW, szReturnUrl, &dwSize, URL_WININET_COMPATIBILITY | URL_ESCAPE_UNSAFE);
    ok( (hr == S_OK) && (dwSize == urllen),
        "got 0x%x with %u and size %u for %u (expected 'S_OK' and size %u)\n",
        hr, GetLastError(), dwSize, lstrlenW(szReturnUrl), urllen);

    /* buffer is larger as the required size */
    dwSize = (urllen+2);
    memset(szReturnUrl, '#', (urllen+4) * sizeof(WCHAR));
    szReturnUrl[urllen+4] = '\0';
    SetLastError(0xdeadbeef);
    hr = pUrlCanonicalizeW(winehqW, szReturnUrl, &dwSize, URL_WININET_COMPATIBILITY | URL_ESCAPE_UNSAFE);
    ok( (hr == S_OK) && (dwSize == urllen),
        "got 0x%x with %u and size %u for %u (expected 'S_OK' and size %u)\n",
        hr, GetLastError(), dwSize, lstrlenW(szReturnUrl), urllen);

    /* check that the characters 1..32 are chopped from the end of the string */
    for (i = 1; i < 65536; i++)
    {
        WCHAR szUrl[128];
        BOOL choped;
        int pos;

        MultiByteToWideChar(CP_ACP, 0, "http://www.winehq.org/X", -1, szUrl, ARRAY_SIZE(szUrl));
        pos = lstrlenW(szUrl) - 1;
        szUrl[pos] = i;
        urllen = INTERNET_MAX_URL_LENGTH;
        pUrlCanonicalizeW(szUrl, szReturnUrl, &urllen, 0);
        choped = lstrlenW(szReturnUrl) < lstrlenW(szUrl);
        ok(choped == (i <= 32), "Incorrect char chopping for char %d\n", i);
    }
}