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
typedef  int /*<<< orphan*/  szReturnUrl ;
typedef  int /*<<< orphan*/  inplaceW ;
typedef  int /*<<< orphan*/  inplace ;
typedef  float WCHAR ;
struct TYPE_3__ {char* url; char const* expect; } ;
typedef  int HRESULT ;
typedef  int DWORD ;
typedef  char CHAR ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  CP_ACP ; 
 int E_INVALIDARG ; 
 int /*<<< orphan*/  FreeWideString (float*) ; 
 float* GetWideString (char const*) ; 
 int INTERNET_MAX_URL_LENGTH ; 
 int S_OK ; 
 TYPE_1__* TEST_URL_UNESCAPE ; 
 int /*<<< orphan*/  URL_UNESCAPE_INPLACE ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*,int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZeroMemory (char*,int) ; 
 scalar_t__ lstrcmpW (float*,float*) ; 
 int lstrlenW (float*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pUrlUnescapeA (char*,char*,int*,int /*<<< orphan*/ ) ; 
 int pUrlUnescapeW (float*,float*,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_UrlUnescape(void)
{
    CHAR szReturnUrl[INTERNET_MAX_URL_LENGTH];
    WCHAR ret_urlW[INTERNET_MAX_URL_LENGTH];
    WCHAR *urlW, *expected_urlW;
    DWORD dwEscaped;
    size_t i;
    static char inplace[] = "file:///C:/Program%20Files";
    static char another_inplace[] = "file:///C:/Program%20Files";
    static const char expected[] = "file:///C:/Program Files";
    static WCHAR inplaceW[] = {'f','i','l','e',':','/','/','/','C',':','/','P','r','o','g','r','a','m',' ','F','i','l','e','s',0};
    static WCHAR another_inplaceW[] ={'f','i','l','e',':','/','/','/',
                'C',':','/','P','r','o','g','r','a','m','%','2','0','F','i','l','e','s',0};
    HRESULT res;

    if (!pUrlUnescapeA) {
        win_skip("UrlUnescapeA not found\n");
        return;
    }
    for (i = 0; i < ARRAY_SIZE(TEST_URL_UNESCAPE); i++) {
        dwEscaped=INTERNET_MAX_URL_LENGTH;
        res = pUrlUnescapeA(TEST_URL_UNESCAPE[i].url, szReturnUrl, &dwEscaped, 0);
        ok(res == S_OK,
            "UrlUnescapeA returned 0x%x (expected S_OK) for \"%s\"\n",
            res, TEST_URL_UNESCAPE[i].url);
        ok(strcmp(szReturnUrl,TEST_URL_UNESCAPE[i].expect)==0, "Expected \"%s\", but got \"%s\" from \"%s\"\n", TEST_URL_UNESCAPE[i].expect, szReturnUrl, TEST_URL_UNESCAPE[i].url);

        ZeroMemory(szReturnUrl, sizeof(szReturnUrl));
        /* if we set the buffer pointer to NULL here, UrlUnescape fails and the string is not converted */
        res = pUrlUnescapeA(TEST_URL_UNESCAPE[i].url, szReturnUrl, NULL, 0);
        ok(res == E_INVALIDARG,
            "UrlUnescapeA returned 0x%x (expected E_INVALIDARG) for \"%s\"\n",
            res, TEST_URL_UNESCAPE[i].url);
        ok(strcmp(szReturnUrl,"")==0, "Expected empty string\n");

        if (pUrlUnescapeW) {
            dwEscaped = INTERNET_MAX_URL_LENGTH;
            urlW = GetWideString(TEST_URL_UNESCAPE[i].url);
            expected_urlW = GetWideString(TEST_URL_UNESCAPE[i].expect);
            res = pUrlUnescapeW(urlW, ret_urlW, &dwEscaped, 0);
            ok(res == S_OK,
                "UrlUnescapeW returned 0x%x (expected S_OK) for \"%s\"\n",
                res, TEST_URL_UNESCAPE[i].url);

            WideCharToMultiByte(CP_ACP,0,ret_urlW,-1,szReturnUrl,INTERNET_MAX_URL_LENGTH,0,0);
            ok(lstrcmpW(ret_urlW, expected_urlW)==0,
                "Expected \"%s\", but got \"%s\" from \"%s\" flags %08lx\n",
                TEST_URL_UNESCAPE[i].expect, szReturnUrl, TEST_URL_UNESCAPE[i].url, 0L);
            FreeWideString(urlW);
            FreeWideString(expected_urlW);
        }
    }

    dwEscaped = sizeof(inplace);
    res = pUrlUnescapeA(inplace, NULL, &dwEscaped, URL_UNESCAPE_INPLACE);
    ok(res == S_OK, "UrlUnescapeA returned 0x%x (expected S_OK)\n", res);
    ok(!strcmp(inplace, expected), "got %s expected %s\n", inplace, expected);
    ok(dwEscaped == 27, "got %d expected 27\n", dwEscaped);

    /* if we set the buffer pointer to NULL, the string apparently still gets converted (Google Lively does this) */
    res = pUrlUnescapeA(another_inplace, NULL, NULL, URL_UNESCAPE_INPLACE);
    ok(res == S_OK, "UrlUnescapeA returned 0x%x (expected S_OK)\n", res);
    ok(!strcmp(another_inplace, expected), "got %s expected %s\n", another_inplace, expected);

    if (pUrlUnescapeW) {
        dwEscaped = sizeof(inplaceW);
        res = pUrlUnescapeW(inplaceW, NULL, &dwEscaped, URL_UNESCAPE_INPLACE);
        ok(res == S_OK, "UrlUnescapeW returned 0x%x (expected S_OK)\n", res);
        ok(dwEscaped == 50, "got %d expected 50\n", dwEscaped);

        /* if we set the buffer pointer to NULL, the string apparently still gets converted (Google Lively does this) */
        res = pUrlUnescapeW(another_inplaceW, NULL, NULL, URL_UNESCAPE_INPLACE);
        ok(res == S_OK, "UrlUnescapeW returned 0x%x (expected S_OK)\n", res);

        ok(lstrlenW(another_inplaceW) == 24, "got %d expected 24\n", lstrlenW(another_inplaceW));
    }
}