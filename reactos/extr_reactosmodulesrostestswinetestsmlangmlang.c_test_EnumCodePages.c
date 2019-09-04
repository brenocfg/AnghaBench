#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  int ULONG ;
typedef  int UINT ;
struct TYPE_13__ {int ciCharset; } ;
struct TYPE_12__ {int dwFlags; int uiFamilyCodePage; int bGDICharset; int uiCodePage; int /*<<< orphan*/  wszBodyCharset; int /*<<< orphan*/  wszHeaderCharset; int /*<<< orphan*/  wszWebCharset; } ;
struct TYPE_11__ {int uiInternetEncoding; int uiCodePage; int /*<<< orphan*/  wszCharset; } ;
typedef  TYPE_1__ MIMECSETINFO ;
typedef  TYPE_2__ MIMECPINFO ;
typedef  scalar_t__ INT_PTR ;
typedef  int /*<<< orphan*/  IMultiLanguage2 ;
typedef  int /*<<< orphan*/  IEnumCodePage ;
typedef  int HRESULT ;
typedef  int DWORD ;
typedef  TYPE_3__ CHARSETINFO ;

/* Variables and functions */
 int CP_UNICODE ; 
 int CP_UTF8 ; 
 int E_FAIL ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int IEnumCodePage_Next (int /*<<< orphan*/ *,int,TYPE_2__*,int*) ; 
 int /*<<< orphan*/  IEnumCodePage_Release (int /*<<< orphan*/ *) ; 
 int IEnumCodePage_Reset (int /*<<< orphan*/ *) ; 
 int IEnumCodePage_Skip (int /*<<< orphan*/ *,int) ; 
 int IMultiLanguage2_EnumCodePages (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int IMultiLanguage2_GetCharsetInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int IMultiLanguage2_GetNumberOfCodePageInfo (int /*<<< orphan*/ *,int*) ; 
 int IMultiLanguage2_IsConvertible (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ IsValidCodePage (int) ; 
 int /*<<< orphan*/  LANG_NEUTRAL ; 
 int MIMECONTF_MIME_LATEST ; 
 int S_FALSE ; 
 int S_OK ; 
 int /*<<< orphan*/  TCI_SRCCODEPAGE ; 
 scalar_t__ TranslateCharsetInfo (int*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int check_convertible (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  cpinfo_cmp (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  lstrcmpiW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  trace (char*,int,...) ; 
 int wine_dbgstr_w (int /*<<< orphan*/ ) ; 
 int winetest_debug ; 

__attribute__((used)) static void test_EnumCodePages(IMultiLanguage2 *iML2, DWORD flags)
{
    IEnumCodePage *iEnumCP = NULL;
    MIMECPINFO *cpinfo;
    MIMECPINFO cpinfo2;
    HRESULT ret;
    ULONG i, n;
    UINT total;

    total = 0;
    ret = IMultiLanguage2_GetNumberOfCodePageInfo(iML2, &total);
    ok(ret == S_OK && total != 0, "IMultiLanguage2_GetNumberOfCodePageInfo: expected S_OK/!0, got %08x/%u\n", ret, total);

    trace("total mlang supported codepages %u\n", total);

    ret = IMultiLanguage2_EnumCodePages(iML2, flags, LANG_NEUTRAL, &iEnumCP);
    ok(ret == S_OK && iEnumCP, "IMultiLanguage2_EnumCodePages: expected S_OK/!NULL, got %08x/%p\n", ret, iEnumCP);

    ret = IEnumCodePage_Reset(iEnumCP);
    ok(ret == S_OK, "IEnumCodePage_Reset: expected S_OK, got %08x\n", ret);
    n = 65536;
    ret = IEnumCodePage_Next(iEnumCP, 0, NULL, &n);
    ok(ret == S_FALSE || ret == E_FAIL,
            "IEnumCodePage_Next: expected S_FALSE or E_FAIL, got %08x\n", ret);
    if (ret == S_FALSE)
        ok(n == 0, "IEnumCodePage_Next: expected 0/S_FALSE, got %u/%08x\n", n, ret);
    else if (ret == E_FAIL)
        ok(n == 65536, "IEnumCodePage_Next: expected 65536/E_FAIL, got %u/%08x\n", n, ret);
    ret = IEnumCodePage_Next(iEnumCP, 0, NULL, NULL);
    ok(ret == S_FALSE || ret == E_FAIL,
            "IEnumCodePage_Next: expected S_FALSE or E_FAIL, got %08x\n", ret);

    cpinfo = HeapAlloc(GetProcessHeap(), 0, sizeof(*cpinfo) * total * 2);

    n = total * 2;
    ret = IEnumCodePage_Next(iEnumCP, 0, cpinfo, &n);
    ok(ret == S_FALSE && n == 0, "IEnumCodePage_Next: expected S_FALSE/0, got %08x/%u\n", ret, n);

    n = total * 2;
    ret = IEnumCodePage_Next(iEnumCP, n, cpinfo, &n);
    ok(ret == S_OK && n != 0, "IEnumCodePage_Next: expected S_OK/!0, got %08x/%u\n", ret, n);

    trace("flags %08x, enumerated codepages %u\n", flags, n);

    if (!flags)
    {
	ok(n == total, "IEnumCodePage_Next: expected %u, got %u\n", total, n);

	flags = MIMECONTF_MIME_LATEST;
    }

    total = n;

    for (i = 0; i < n; i++)
    {
	CHARSETINFO csi;
	MIMECSETINFO mcsi;
        HRESULT convertible = S_OK;
	static const WCHAR autoW[] = {'_','a','u','t','o',0};
	static const WCHAR feffW[] = {'u','n','i','c','o','d','e','F','E','F','F',0};

#ifdef DUMP_CP_INFO
	trace("MIMECPINFO #%u:\n"
	      "dwFlags %08x %s\n"
	      "uiCodePage %u\n"
	      "uiFamilyCodePage %u\n"
	      "wszDescription %s\n"
	      "wszWebCharset %s\n"
	      "wszHeaderCharset %s\n"
	      "wszBodyCharset %s\n"
	      "wszFixedWidthFont %s\n"
	      "wszProportionalFont %s\n"
	      "bGDICharset %d\n\n",
	      i,
	      cpinfo[i].dwFlags, dump_mime_flags(cpinfo[i].dwFlags),
	      cpinfo[i].uiCodePage,
	      cpinfo[i].uiFamilyCodePage,
	      wine_dbgstr_w(cpinfo[i].wszDescription),
	      wine_dbgstr_w(cpinfo[i].wszWebCharset),
	      wine_dbgstr_w(cpinfo[i].wszHeaderCharset),
	      wine_dbgstr_w(cpinfo[i].wszBodyCharset),
	      wine_dbgstr_w(cpinfo[i].wszFixedWidthFont),
	      wine_dbgstr_w(cpinfo[i].wszProportionalFont),
	      cpinfo[i].bGDICharset);
#endif
	ok(cpinfo[i].dwFlags & flags, "enumerated flags %08x do not include requested %08x\n", cpinfo[i].dwFlags, flags);

	if (TranslateCharsetInfo((DWORD *)(INT_PTR)cpinfo[i].uiFamilyCodePage, &csi, TCI_SRCCODEPAGE))
	    ok(cpinfo[i].bGDICharset == csi.ciCharset, "%d != %d\n", cpinfo[i].bGDICharset, csi.ciCharset);
	else
            if (winetest_debug > 1)
                trace("TranslateCharsetInfo failed for cp %u\n", cpinfo[i].uiFamilyCodePage);

#ifdef DUMP_CP_INFO
        trace("%u: codepage %u family %u\n", i, cpinfo[i].uiCodePage, cpinfo[i].uiFamilyCodePage);
#endif

	/* support files for some codepages might be not installed, or
	 * the codepage is just an alias.
	 */
	if (IsValidCodePage(cpinfo[i].uiCodePage))
	{
	    ret = IMultiLanguage2_IsConvertible(iML2, cpinfo[i].uiCodePage, CP_UNICODE);
	    ok(ret == S_OK, "IMultiLanguage2_IsConvertible(%u -> CP_UNICODE) = %08x\n", cpinfo[i].uiCodePage, ret);
	    ret = IMultiLanguage2_IsConvertible(iML2, CP_UNICODE, cpinfo[i].uiCodePage);
	    ok(ret == S_OK, "IMultiLanguage2_IsConvertible(CP_UNICODE -> %u) = %08x\n", cpinfo[i].uiCodePage, ret);

            convertible = check_convertible(iML2, cpinfo[i].uiCodePage, CP_UTF8);
            if (convertible != E_FAIL)
            {
                ret = IMultiLanguage2_IsConvertible(iML2, cpinfo[i].uiCodePage, CP_UTF8);
                ok(ret == convertible, "IMultiLanguage2_IsConvertible(%u -> CP_UTF8) = %08x\n", cpinfo[i].uiCodePage, ret);
                ret = IMultiLanguage2_IsConvertible(iML2, CP_UTF8, cpinfo[i].uiCodePage);
                ok(ret == convertible, "IMultiLanguage2_IsConvertible(CP_UTF8 -> %u) = %08x\n", cpinfo[i].uiCodePage, ret);
            }
	}
	else
            if (winetest_debug > 1)
                trace("IsValidCodePage failed for cp %u\n", cpinfo[i].uiCodePage);

    if (memcmp(cpinfo[i].wszWebCharset,feffW,sizeof(WCHAR)*11)==0)
        skip("Legacy windows bug returning invalid charset of unicodeFEFF\n");
    else
    {
        ret = IMultiLanguage2_GetCharsetInfo(iML2, cpinfo[i].wszWebCharset, &mcsi);
        /* _autoxxx charsets are a fake and GetCharsetInfo fails for them */
        if (memcmp(cpinfo[i].wszWebCharset, autoW, 5 * sizeof(WCHAR)))
        {
            ok (ret == S_OK, "IMultiLanguage2_GetCharsetInfo failed: %08x\n", ret);
#ifdef DUMP_CP_INFO
            trace("%s: %u %u %s\n", wine_dbgstr_w(cpinfo[i].wszWebCharset), mcsi.uiCodePage, mcsi.uiInternetEncoding, wine_dbgstr_w(mcsi.wszCharset));
#endif
            ok(!lstrcmpiW(cpinfo[i].wszWebCharset, mcsi.wszCharset), "%s != %s\n",
               wine_dbgstr_w(cpinfo[i].wszWebCharset), wine_dbgstr_w(mcsi.wszCharset));

        if (0)
        {
            /* native mlang returns completely messed up encodings in some cases */
            ok(mcsi.uiInternetEncoding == cpinfo[i].uiCodePage || mcsi.uiInternetEncoding == cpinfo[i].uiFamilyCodePage,
            "%u != %u || %u\n", mcsi.uiInternetEncoding, cpinfo[i].uiCodePage, cpinfo[i].uiFamilyCodePage);
            ok(mcsi.uiCodePage == cpinfo[i].uiCodePage || mcsi.uiCodePage == cpinfo[i].uiFamilyCodePage,
            "%u != %u || %u\n", mcsi.uiCodePage, cpinfo[i].uiCodePage, cpinfo[i].uiFamilyCodePage);
            }
        }
    }

    if (memcmp(cpinfo[i].wszHeaderCharset,feffW,sizeof(WCHAR)*11)==0)
        skip("Legacy windows bug returning invalid charset of unicodeFEFF\n");
    else
    {
        ret = IMultiLanguage2_GetCharsetInfo(iML2, cpinfo[i].wszHeaderCharset, &mcsi);
        /* _autoxxx charsets are a fake and GetCharsetInfo fails for them */
        if (memcmp(cpinfo[i].wszHeaderCharset, autoW, 5 * sizeof(WCHAR)))
        {
            ok (ret == S_OK, "IMultiLanguage2_GetCharsetInfo failed: %08x\n", ret);
#ifdef DUMP_CP_INFO
            trace("%s: %u %u %s\n", wine_dbgstr_w(cpinfo[i].wszHeaderCharset), mcsi.uiCodePage, mcsi.uiInternetEncoding, wine_dbgstr_w(mcsi.wszCharset));
#endif
            ok(!lstrcmpiW(cpinfo[i].wszHeaderCharset, mcsi.wszCharset), "%s != %s\n",
               wine_dbgstr_w(cpinfo[i].wszHeaderCharset), wine_dbgstr_w(mcsi.wszCharset));

        if (0)
        {
            /* native mlang returns completely messed up encodings in some cases */
            ok(mcsi.uiInternetEncoding == cpinfo[i].uiCodePage || mcsi.uiInternetEncoding == cpinfo[i].uiFamilyCodePage,
            "%u != %u || %u\n", mcsi.uiInternetEncoding, cpinfo[i].uiCodePage, cpinfo[i].uiFamilyCodePage);
            ok(mcsi.uiCodePage == cpinfo[i].uiCodePage || mcsi.uiCodePage == cpinfo[i].uiFamilyCodePage,
            "%u != %u || %u\n", mcsi.uiCodePage, cpinfo[i].uiCodePage, cpinfo[i].uiFamilyCodePage);
        }
        }
    }

    if (memcmp(cpinfo[i].wszBodyCharset,feffW,sizeof(WCHAR)*11)==0)
        skip("Legacy windows bug returning invalid charset of unicodeFEFF\n");
    else
    {
        ret = IMultiLanguage2_GetCharsetInfo(iML2, cpinfo[i].wszBodyCharset, &mcsi);
        /* _autoxxx charsets are a fake and GetCharsetInfo fails for them */
        if (memcmp(cpinfo[i].wszBodyCharset, autoW, 5 * sizeof(WCHAR)))
        {
            ok (ret == S_OK, "IMultiLanguage2_GetCharsetInfo failed: %08x\n", ret);
#ifdef DUMP_CP_INFO
            trace("%s: %u %u %s\n", wine_dbgstr_w(cpinfo[i].wszBodyCharset), mcsi.uiCodePage, mcsi.uiInternetEncoding, wine_dbgstr_w(mcsi.wszCharset));
#endif
            ok(!lstrcmpiW(cpinfo[i].wszBodyCharset, mcsi.wszCharset), "%s != %s\n",
               wine_dbgstr_w(cpinfo[i].wszBodyCharset), wine_dbgstr_w(mcsi.wszCharset));

        if (0)
        {
            /* native mlang returns completely messed up encodings in some cases */
            ok(mcsi.uiInternetEncoding == cpinfo[i].uiCodePage || mcsi.uiInternetEncoding == cpinfo[i].uiFamilyCodePage,
            "%u != %u || %u\n", mcsi.uiInternetEncoding, cpinfo[i].uiCodePage, cpinfo[i].uiFamilyCodePage);
            ok(mcsi.uiCodePage == cpinfo[i].uiCodePage || mcsi.uiCodePage == cpinfo[i].uiFamilyCodePage,
            "%u != %u || %u\n", mcsi.uiCodePage, cpinfo[i].uiCodePage, cpinfo[i].uiFamilyCodePage);
        }
        }
    }
    }

    /* now IEnumCodePage_Next should fail, since pointer is at the end */
    n = 1;
    ret = IEnumCodePage_Next(iEnumCP, 1, &cpinfo2, &n);
    ok(ret == S_FALSE && n == 0, "IEnumCodePage_Next: expected S_FALSE/0, got %08x/%u\n", ret, n);

    ret = IEnumCodePage_Reset(iEnumCP);
    ok(ret == S_OK, "IEnumCodePage_Reset: expected S_OK, got %08x\n", ret);
    n = 0;
    ret = IEnumCodePage_Next(iEnumCP, 1, &cpinfo2, &n);
    ok(n == 1 && ret == S_OK, "IEnumCodePage_Next: expected 1/S_OK, got %u/%08x\n", n, ret);
    cpinfo_cmp(cpinfo, &cpinfo2);

    if (0)
    {
    /* Due to a bug in MS' implementation of IEnumCodePage_Skip
     * it's not used here.
     */
    ret = IEnumCodePage_Skip(iEnumCP, 1);
    ok(ret == S_OK, "IEnumCodePage_Skip: expected S_OK, got %08x\n", ret);
    }
    for (i = 0; i < total - 1; i++)
    {
        n = 0;
        ret = IEnumCodePage_Next(iEnumCP, 1, &cpinfo2, &n);
        ok(n == 1 && ret == S_OK, "IEnumCodePage_Next: expected 1/S_OK, got %u/%08x\n", n, ret);
        cpinfo_cmp(&cpinfo[i + 1], &cpinfo2);
    }

    HeapFree(GetProcessHeap(), 0, cpinfo);
    IEnumCodePage_Release(iEnumCP);
}