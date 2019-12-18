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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {size_t newlen; int /*<<< orphan*/  flags; int /*<<< orphan*/ * url; int /*<<< orphan*/  newurl; int /*<<< orphan*/  res; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  E_POINTER ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,size_t) ; 
 TYPE_1__* TEST_APPLY ; 
 int TEST_APPLY_MAX_LENGTH ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcmpA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcpyA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t lstrlenA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,size_t,...) ; 
 int /*<<< orphan*/  pUrlApplySchemeA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pUrlApplySchemeW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  untouchedA ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_UrlApplyScheme(void)
{
    CHAR newurl[TEST_APPLY_MAX_LENGTH];
    WCHAR urlW[TEST_APPLY_MAX_LENGTH];
    WCHAR newurlW[TEST_APPLY_MAX_LENGTH];
    HRESULT res;
    DWORD len;
    DWORD i;

    if (!pUrlApplySchemeA) {
        win_skip("UrlApplySchemeA not found\n");
        return;
    }

    for (i = 0; i < ARRAY_SIZE(TEST_APPLY); i++) {
        len = TEST_APPLY_MAX_LENGTH;
        lstrcpyA(newurl, untouchedA);
        res = pUrlApplySchemeA(TEST_APPLY[i].url, newurl, &len, TEST_APPLY[i].flags);
        ok( res == TEST_APPLY[i].res,
            "#%dA: got HRESULT 0x%x (expected 0x%x)\n", i, res, TEST_APPLY[i].res);

        ok( len == TEST_APPLY[i].newlen,
            "#%dA: got len %d (expected %d)\n", i, len, TEST_APPLY[i].newlen);

        ok( !lstrcmpA(newurl, TEST_APPLY[i].newurl),
            "#%dA: got '%s' (expected '%s')\n", i, newurl, TEST_APPLY[i].newurl);

        /* returned length is in character */
        len = TEST_APPLY_MAX_LENGTH;
        lstrcpyA(newurl, untouchedA);
        MultiByteToWideChar(CP_ACP, 0, newurl, -1, newurlW, len);
        MultiByteToWideChar(CP_ACP, 0, TEST_APPLY[i].url, -1, urlW, len);

        res = pUrlApplySchemeW(urlW, newurlW, &len, TEST_APPLY[i].flags);
        WideCharToMultiByte(CP_ACP, 0, newurlW, -1, newurl, TEST_APPLY_MAX_LENGTH, NULL, NULL);
        ok( res == TEST_APPLY[i].res,
            "#%dW: got HRESULT 0x%x (expected 0x%x)\n", i, res, TEST_APPLY[i].res);

        ok( len == TEST_APPLY[i].newlen,
            "#%dW: got len %d (expected %d)\n", i, len, TEST_APPLY[i].newlen);

        ok( !lstrcmpA(newurl, TEST_APPLY[i].newurl),
            "#%dW: got '%s' (expected '%s')\n", i, newurl, TEST_APPLY[i].newurl);

    }

    /* buffer too small */
    lstrcpyA(newurl, untouchedA);
    len = lstrlenA(TEST_APPLY[0].newurl);
    res = pUrlApplySchemeA(TEST_APPLY[0].url, newurl, &len, TEST_APPLY[0].flags);
    ok(res == E_POINTER, "got HRESULT 0x%x (expected E_POINTER)\n", res);
    /* The returned length include the space for the terminating 0 */
    i = lstrlenA(TEST_APPLY[0].newurl)+1;
    ok(len == i, "got len %d (expected %d)\n", len, i);
    ok(!lstrcmpA(newurl, untouchedA), "got '%s' (expected '%s')\n", newurl, untouchedA);

    /* NULL as parameter. The length and the buffer are not modified */
    lstrcpyA(newurl, untouchedA);
    len = TEST_APPLY_MAX_LENGTH;
    res = pUrlApplySchemeA(NULL, newurl, &len, TEST_APPLY[0].flags);
    ok(res == E_INVALIDARG, "got HRESULT 0x%x (expected E_INVALIDARG)\n", res);
    ok(len == TEST_APPLY_MAX_LENGTH, "got len %d\n", len);
    ok(!lstrcmpA(newurl, untouchedA), "got '%s' (expected '%s')\n", newurl, untouchedA);

    len = TEST_APPLY_MAX_LENGTH;
    res = pUrlApplySchemeA(TEST_APPLY[0].url, NULL, &len, TEST_APPLY[0].flags);
    ok(res == E_INVALIDARG, "got HRESULT 0x%x (expected E_INVALIDARG)\n", res);
    ok(len == TEST_APPLY_MAX_LENGTH, "got len %d\n", len);

    lstrcpyA(newurl, untouchedA);
    res = pUrlApplySchemeA(TEST_APPLY[0].url, newurl, NULL, TEST_APPLY[0].flags);
    ok(res == E_INVALIDARG, "got HRESULT 0x%x (expected E_INVALIDARG)\n", res);
    ok(!lstrcmpA(newurl, untouchedA), "got '%s' (expected '%s')\n", newurl, untouchedA);

}