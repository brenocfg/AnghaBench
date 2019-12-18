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

/* Variables and functions */
 int ARRAY_SIZE (char const*) ; 
 int EBADF ; 
 int EINVAL ; 
 int ERANGE ; 
 int STRUNCATE ; 
 int errno ; 
 scalar_t__ lstrcmpW (char*,char const*) ; 
 int /*<<< orphan*/  memcmp (char*,char const*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int p_wcscpy_s (char*,int,char const*) ; 
 int p_wcsncpy_s (char*,int,char const*,int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int wine_dbgstr_w (char*) ; 

__attribute__((used)) static void test_wcscpy_s(void)
{
    static const WCHAR szLongText[] = { 'T','h','i','s','A','L','o','n','g','s','t','r','i','n','g',0 };
    static WCHAR szDest[18];
    static WCHAR szDestShort[8];
    int ret;

    if(!p_wcscpy_s)
    {
        win_skip("wcscpy_s not found\n");
        return;
    }

    /* Test NULL Dest */
    errno = EBADF;
    ret = p_wcscpy_s(NULL, 18, szLongText);
    ok(ret == EINVAL, "p_wcscpy_s expect EINVAL got %d\n", ret);
    ok(errno == EINVAL, "expected errno EINVAL got %d\n", errno);

    /* Test NULL Source */
    errno = EBADF;
    szDest[0] = 'A';
    ret = p_wcscpy_s(szDest, 18, NULL);
    ok(ret == EINVAL, "expected EINVAL got %d\n", ret);
    ok(errno == EINVAL, "expected errno EINVAL got %d\n", errno);
    ok(szDest[0] == 0, "szDest[0] not 0, got %c\n", szDest[0]);

    /* Test invalid size */
    errno = EBADF;
    szDest[0] = 'A';
    ret = p_wcscpy_s(szDest, 0, szLongText);
    /* Later versions changed the return value for this case to EINVAL,
     * and don't modify the result if the dest size is 0.
     */
    ok(ret == ERANGE || ret == EINVAL, "expected ERANGE/EINVAL got %d\n", ret);
    ok(errno == ERANGE || errno == EINVAL, "expected errno ERANGE/EINVAL got %d\n", errno);
    ok(szDest[0] == 0 || ret == EINVAL, "szDest[0] not 0\n");

    /* Copy same buffer size */
    ret = p_wcscpy_s(szDest, 18, szLongText);
    ok(ret == 0, "expected 0 got %d\n", ret);
    ok(lstrcmpW(szDest, szLongText) == 0, "szDest != szLongText\n");

    /* dest == source */
    ret = p_wcscpy_s(szDest, 18, szDest);
    ok(ret == 0, "expected 0 got %d\n", ret);
    ok(lstrcmpW(szDest, szLongText) == 0, "szDest != szLongText\n");

    /* Copy smaller buffer size */
    errno = EBADF;
    szDest[0] = 'A';
    ret = p_wcscpy_s(szDestShort, 8, szLongText);
    ok(ret == ERANGE || ret == EINVAL, "expected ERANGE/EINVAL got %d\n", ret);
    ok(errno == ERANGE || errno == EINVAL, "expected errno ERANGE/EINVAL got %d\n", errno);
    ok(szDestShort[0] == 0, "szDestShort[0] not 0\n");

    if(!p_wcsncpy_s)
    {
        win_skip("wcsncpy_s not found\n");
        return;
    }

    ret = p_wcsncpy_s(NULL, 18, szLongText, ARRAY_SIZE(szLongText));
    ok(ret == EINVAL, "p_wcsncpy_s expect EINVAL got %d\n", ret);

    szDest[0] = 'A';
    ret = p_wcsncpy_s(szDest, 18, NULL, 1);
    ok(ret == EINVAL, "expected EINVAL got %d\n", ret);
    ok(szDest[0] == 0, "szDest[0] not 0\n");

    szDest[0] = 'A';
    ret = p_wcsncpy_s(szDest, 18, NULL, 0);
    ok(ret == 0, "expected ERROR_SUCCESS got %d\n", ret);
    ok(szDest[0] == 0, "szDest[0] not 0\n");

    szDest[0] = 'A';
    ret = p_wcsncpy_s(szDest, 0, szLongText, ARRAY_SIZE(szLongText));
    ok(ret == ERANGE || ret == EINVAL, "expected ERANGE/EINVAL got %d\n", ret);
    ok(szDest[0] == 0 || ret == EINVAL, "szDest[0] not 0\n");

    ret = p_wcsncpy_s(szDest, 18, szLongText, ARRAY_SIZE(szLongText));
    ok(ret == 0, "expected 0 got %d\n", ret);
    ok(lstrcmpW(szDest, szLongText) == 0, "szDest != szLongText\n");

    szDest[0] = 'A';
    ret = p_wcsncpy_s(szDestShort, 8, szLongText, ARRAY_SIZE(szLongText));
    ok(ret == ERANGE || ret == EINVAL, "expected ERANGE/EINVAL got %d\n", ret);
    ok(szDestShort[0] == 0, "szDestShort[0] not 0\n");

    szDest[0] = 'A';
    ret = p_wcsncpy_s(szDest, 5, szLongText, -1);
    ok(ret == STRUNCATE, "expected STRUNCATE got %d\n", ret);
    ok(szDest[4] == 0, "szDest[4] not 0\n");
    ok(!memcmp(szDest, szLongText, 4*sizeof(WCHAR)), "szDest = %s\n", wine_dbgstr_w(szDest));

    ret = p_wcsncpy_s(NULL, 0, (void*)0xdeadbeef, 0);
    ok(ret == 0, "ret = %d\n", ret);

    szDestShort[0] = '1';
    szDestShort[1] = 0;
    ret = p_wcsncpy_s(szDestShort+1, 4, szDestShort, -1);
    ok(ret == STRUNCATE, "expected ERROR_SUCCESS got %d\n", ret);
    ok(szDestShort[0]=='1' && szDestShort[1]=='1' && szDestShort[2]=='1' && szDestShort[3]=='1',
            "szDestShort = %s\n", wine_dbgstr_w(szDestShort));
}