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
typedef  int UINT ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  IMLangFontLink ;
typedef  int HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int E_FAIL ; 
 int E_INVALIDARG ; 
 int FS_ARABIC ; 
 int FS_BALTIC ; 
 int FS_CHINESESIMP ; 
 int FS_CHINESETRAD ; 
 int FS_CYRILLIC ; 
 int FS_GREEK ; 
 int FS_HEBREW ; 
 int FS_JISJAPAN ; 
 int FS_LATIN1 ; 
 int FS_LATIN2 ; 
 int FS_THAI ; 
 int FS_TURKISH ; 
 int FS_VIETNAMESE ; 
 int FS_WANSUNG ; 
 int IMLangFontLink_CodePageToCodePages (int /*<<< orphan*/ *,int,int*) ; 
 int IMLangFontLink_CodePagesToCodePage (int /*<<< orphan*/ *,int,int,int*) ; 
 int IMLangFontLink_GetCharCodePages (int /*<<< orphan*/ *,int,int*) ; 
 int IMLangFontLink_GetStrCodePages (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ,int*,int*) ; 
 int S_OK ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 

__attribute__((used)) static void IMLangFontLink_Test(IMLangFontLink* iMLFL)
{
    DWORD dwCodePages, dwManyCodePages;
    DWORD dwCmpCodePages;
    UINT CodePage;
    static const WCHAR str[] = { 'd', 0x0436, 0xff90 };
    LONG processed;
    HRESULT ret;

    dwCodePages = ~0u;
    ret = IMLangFontLink_CodePageToCodePages(iMLFL, -1, &dwCodePages);
    ok(ret == E_FAIL, "IMLangFontLink_CodePageToCodePages should fail: %x\n", ret);
    ok(dwCodePages == 0, "expected 0, got %u\n", dwCodePages);

    dwCodePages = 0;
    ret = IMLangFontLink_CodePageToCodePages(iMLFL, 932, &dwCodePages);
    ok(ret == S_OK, "IMLangFontLink_CodePageToCodePages error %x\n", ret);
    ok(dwCodePages == FS_JISJAPAN, "expected FS_JISJAPAN, got %08x\n", dwCodePages);
    CodePage = 0;
    ret = IMLangFontLink_CodePagesToCodePage(iMLFL, dwCodePages, 1035, &CodePage);
    ok(ret == S_OK, "IMLangFontLink_CodePagesToCodePage error %x\n", ret);
    ok(CodePage == 932, "Incorrect CodePage Returned (%i)\n",CodePage);

    dwManyCodePages = 0;
    ret = IMLangFontLink_CodePageToCodePages(iMLFL, 1252, &dwManyCodePages);
    ok(ret == S_OK, "IMLangFontLink_CodePageToCodePages error %x\n", ret);
    ok(dwManyCodePages == FS_LATIN1, "expected FS_LATIN1, got %08x\n", dwManyCodePages);
    dwCodePages = 0;
    ret = IMLangFontLink_CodePageToCodePages(iMLFL, 1256, &dwCodePages);
    ok(ret == S_OK, "IMLangFontLink_CodePageToCodePages error %x\n", ret);
    ok(dwCodePages == FS_ARABIC, "expected FS_ARABIC, got %08x\n", dwCodePages);
    dwManyCodePages |= dwCodePages;
    ret = IMLangFontLink_CodePageToCodePages(iMLFL, 874, &dwCodePages);
    ok(ret == S_OK, "IMLangFontLink_CodePageToCodePages error %x\n", ret);
    ok(dwCodePages == FS_THAI, "expected FS_THAI, got %08x\n", dwCodePages);
    dwManyCodePages |= dwCodePages;

    ret = IMLangFontLink_CodePagesToCodePage(iMLFL, dwManyCodePages, 1256, &CodePage);
    ok(ret == S_OK, "IMLangFontLink_CodePagesToCodePage error %x\n", ret);
    ok(CodePage == 1256, "Incorrect CodePage Returned (%i)\n",CodePage);

    ret = IMLangFontLink_CodePagesToCodePage(iMLFL, dwManyCodePages, 936, &CodePage);
    ok(ret == S_OK, "IMLangFontLink_CodePagesToCodePage error %x\n", ret);
    ok(CodePage == 1252, "Incorrect CodePage Returned (%i)\n",CodePage);

    /* Tests for GetCharCodePages */

    /* Latin 1 */
    dwCmpCodePages = FS_LATIN1 | FS_LATIN2 | FS_CYRILLIC | FS_GREEK | FS_TURKISH
        | FS_HEBREW | FS_ARABIC | FS_BALTIC | FS_VIETNAMESE | FS_THAI
        | FS_JISJAPAN | FS_CHINESESIMP | FS_WANSUNG | FS_CHINESETRAD;
    ret = IMLangFontLink_GetCharCodePages(iMLFL, 'd', &dwCodePages);
    ok(ret == S_OK, "IMLangFontLink_GetCharCodePages error %x\n", ret);
    ok(dwCodePages == dwCmpCodePages, "expected %x, got %x\n", dwCmpCodePages, dwCodePages);

    dwCodePages = 0;
    processed = 0;
    ret = IMLangFontLink_GetStrCodePages(iMLFL, str, 1, 0, &dwCodePages, &processed);
    ok(ret == S_OK, "IMLangFontLink_GetStrCodePages error %x\n", ret);
    ok(dwCodePages == dwCmpCodePages, "expected %x, got %x\n", dwCmpCodePages, dwCodePages);
    ok(processed == 1, "expected 1, got %d\n", processed);

    /* Cyrillic */
    dwCmpCodePages = FS_CYRILLIC | FS_JISJAPAN | FS_CHINESESIMP | FS_WANSUNG;
    ret = IMLangFontLink_GetCharCodePages(iMLFL, 0x0436, &dwCodePages);
    ok(ret == S_OK, "IMLangFontLink_GetCharCodePages error %x\n", ret);
    ok(dwCodePages == dwCmpCodePages, "expected %x, got %x\n", dwCmpCodePages, dwCodePages);

    dwCodePages = 0;
    processed = 0;
    ret = IMLangFontLink_GetStrCodePages(iMLFL, &str[1], 1, 0, &dwCodePages, &processed);
    ok(ret == S_OK, "IMLangFontLink_GetStrCodePages error %x\n", ret);
    ok(dwCodePages == dwCmpCodePages, "expected %x, got %x\n", dwCmpCodePages, dwCodePages);
    ok(processed == 1, "expected 1, got %d\n", processed);

    /* Japanese */
    dwCmpCodePages =  FS_JISJAPAN;
    ret = IMLangFontLink_GetCharCodePages(iMLFL, 0xff90, &dwCodePages);
    ok(ret == S_OK, "IMLangFontLink_GetCharCodePages error %x\n", ret);
    ok(dwCodePages == dwCmpCodePages, "expected %x, got %x\n", dwCmpCodePages, dwCodePages);

    dwCodePages = 0;
    processed = 0;
    ret = IMLangFontLink_GetStrCodePages(iMLFL, &str[2], 1, 0, &dwCodePages, &processed);
    ok(ret == S_OK, "IMLangFontLink_GetStrCodePages error %x\n", ret);
    ok(dwCodePages == dwCmpCodePages, "expected %x, got %x\n", dwCmpCodePages, dwCodePages);
    ok(processed == 1, "expected 1, got %d\n", processed);

    dwCmpCodePages = FS_CYRILLIC | FS_JISJAPAN | FS_CHINESESIMP | FS_WANSUNG;
    dwCodePages = 0;
    processed = 0;
    ret = IMLangFontLink_GetStrCodePages(iMLFL, str, 2, 0, &dwCodePages, &processed);
    ok(ret == S_OK, "IMLangFontLink_GetStrCodePages error %x\n", ret);
    ok(dwCodePages == dwCmpCodePages, "expected %x, got %x\n", dwCmpCodePages, dwCodePages);
    ok(processed == 2, "expected 2, got %d\n", processed);

    dwCmpCodePages = FS_JISJAPAN;
    dwCodePages = 0;
    processed = 0;
    ret = IMLangFontLink_GetStrCodePages(iMLFL, str, 3, 0, &dwCodePages, &processed);
    ok(ret == S_OK, "IMLangFontLink_GetStrCodePages error %x\n", ret);
    ok(dwCodePages == dwCmpCodePages, "expected %x, got %x\n", dwCmpCodePages, dwCodePages);
    ok(processed == 3, "expected 3, got %d\n", processed);

    dwCodePages = 0xffff;
    processed = -1;
    ret = IMLangFontLink_GetStrCodePages(iMLFL, &str[2], 1, 0, &dwCodePages, &processed);
    ok(ret == S_OK, "IMLangFontLink_GetStrCodePages error %x\n", ret);
    ok(dwCodePages == dwCmpCodePages, "expected %x, got %x\n", dwCmpCodePages, dwCodePages);
    ok(processed == 1, "expected 0, got %d\n", processed);

    ret = IMLangFontLink_GetStrCodePages(iMLFL, &str[2], 1, 0, NULL, NULL);
    ok(ret == S_OK, "IMLangFontLink_GetStrCodePages error %x\n", ret);

    dwCodePages = 0xffff;
    processed = -1;
    ret = IMLangFontLink_GetStrCodePages(iMLFL, str, -1, 0, &dwCodePages, &processed);
    ok(ret == E_INVALIDARG, "IMLangFontLink_GetStrCodePages should fail: %x\n", ret);
    ok(dwCodePages == 0, "expected %x, got %x\n", dwCmpCodePages, dwCodePages);
    ok(processed == 0, "expected 0, got %d\n", processed);

    dwCodePages = 0xffff;
    processed = -1;
    ret = IMLangFontLink_GetStrCodePages(iMLFL, NULL, 1, 0, &dwCodePages, &processed);
    ok(ret == E_INVALIDARG, "IMLangFontLink_GetStrCodePages should fail: %x\n", ret);
    ok(dwCodePages == 0, "expected %x, got %x\n", dwCmpCodePages, dwCodePages);
    ok(processed == 0, "expected 0, got %d\n", processed);

    dwCodePages = 0xffff;
    processed = -1;
    ret = IMLangFontLink_GetStrCodePages(iMLFL, str, 0, 0, &dwCodePages, &processed);
    ok(ret == E_INVALIDARG, "IMLangFontLink_GetStrCodePages should fail: %x\n", ret);
    ok(dwCodePages == 0, "expected %x, got %x\n", dwCmpCodePages, dwCodePages);
    ok(processed == 0, "expected 0, got %d\n", processed);
}