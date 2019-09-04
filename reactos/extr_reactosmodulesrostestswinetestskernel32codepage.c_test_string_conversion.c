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
typedef  int /*<<< orphan*/  mbs ;
typedef  char WCHAR ;
typedef  int* LPBOOL ;

/* Variables and functions */
 int ERROR_INSUFFICIENT_BUFFER ; 
 int FALSE ; 
 int GetLastError () ; 
 scalar_t__ IsValidCodePage (int) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int TRUE ; 
 int /*<<< orphan*/  WC_COMPOSITECHECK ; 
 int WideCharToMultiByte (int,int /*<<< orphan*/ ,char const*,int,char*,int,char const*,int*) ; 
 int /*<<< orphan*/  ZeroMemory (char*,int) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void test_string_conversion(LPBOOL bUsedDefaultChar)
{
    char mbc;
    char mbs[15];
    int ret;
    WCHAR wc1 = 228;                           /* Western Windows-1252 character */
    WCHAR wc2 = 1088;                          /* Russian Windows-1251 character not displayable for Windows-1252 */
    static const WCHAR wcs[] = {'T', 'h', 1088, 'i', 0}; /* String with ASCII characters and a Russian character */
    static const WCHAR dbwcs[] = {28953, 25152, 0}; /* String with Chinese (codepage 950) characters */
    static const WCHAR dbwcs2[] = {0x7bb8, 0x3d, 0xc813, 0xac00, 0xb77d, 0};
    static const char default_char[] = {0xa3, 0xbf, 0};

    SetLastError(0xdeadbeef);
    ret = WideCharToMultiByte(1252, 0, &wc1, 1, &mbc, 1, NULL, bUsedDefaultChar);
    ok(ret == 1, "ret is %d\n", ret);
    ok(mbc == '\xe4', "mbc is %d\n", mbc);
    if(bUsedDefaultChar) ok(*bUsedDefaultChar == FALSE, "bUsedDefaultChar is %d\n", *bUsedDefaultChar);
    ok(GetLastError() == 0xdeadbeef, "GetLastError() is %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = WideCharToMultiByte(1252, 0, &wc2, 1, &mbc, 1, NULL, bUsedDefaultChar);
    ok(ret == 1, "ret is %d\n", ret);
    ok(mbc == 63, "mbc is %d\n", mbc);
    if(bUsedDefaultChar) ok(*bUsedDefaultChar == TRUE, "bUsedDefaultChar is %d\n", *bUsedDefaultChar);
    ok(GetLastError() == 0xdeadbeef, "GetLastError() is %u\n", GetLastError());

    if (IsValidCodePage(1251))
    {
        SetLastError(0xdeadbeef);
        ret = WideCharToMultiByte(1251, 0, &wc2, 1, &mbc, 1, NULL, bUsedDefaultChar);
        ok(ret == 1, "ret is %d\n", ret);
        ok(mbc == '\xf0', "mbc is %d\n", mbc);
        if(bUsedDefaultChar) ok(*bUsedDefaultChar == FALSE, "bUsedDefaultChar is %d\n", *bUsedDefaultChar);
        ok(GetLastError() == 0xdeadbeef ||
           broken(GetLastError() == 0), /* win95 */
           "GetLastError() is %u\n", GetLastError());

        SetLastError(0xdeadbeef);
        ret = WideCharToMultiByte(1251, 0, &wc1, 1, &mbc, 1, NULL, bUsedDefaultChar);
        ok(ret == 1, "ret is %d\n", ret);
        ok(mbc == 97, "mbc is %d\n", mbc);
        if(bUsedDefaultChar) ok(*bUsedDefaultChar == FALSE, "bUsedDefaultChar is %d\n", *bUsedDefaultChar);
        ok(GetLastError() == 0xdeadbeef, "GetLastError() is %u\n", GetLastError());
    }
    else
        skip("Codepage 1251 not available\n");

    /* This call triggers the last Win32 error */
    SetLastError(0xdeadbeef);
    ret = WideCharToMultiByte(1252, 0, wcs, -1, &mbc, 1, NULL, bUsedDefaultChar);
    ok(ret == 0, "ret is %d\n", ret);
    ok(mbc == 84, "mbc is %d\n", mbc);
    if(bUsedDefaultChar) ok(*bUsedDefaultChar == FALSE, "bUsedDefaultChar is %d\n", *bUsedDefaultChar);
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER, "GetLastError() is %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = WideCharToMultiByte(1252, 0, wcs, -1, mbs, sizeof(mbs), NULL, bUsedDefaultChar);
    ok(ret == 5, "ret is %d\n", ret);
    ok(!strcmp(mbs, "Th?i"), "mbs is %s\n", mbs);
    if(bUsedDefaultChar) ok(*bUsedDefaultChar == TRUE, "bUsedDefaultChar is %d\n", *bUsedDefaultChar);
    ok(GetLastError() == 0xdeadbeef, "GetLastError() is %u\n", GetLastError());
    mbs[0] = 0;

    /* WideCharToMultiByte mustn't add any null character automatically.
       So in this case, we should get the same string again, even if we only copied the first three bytes. */
    SetLastError(0xdeadbeef);
    ret = WideCharToMultiByte(1252, 0, wcs, 3, mbs, sizeof(mbs), NULL, bUsedDefaultChar);
    ok(ret == 3, "ret is %d\n", ret);
    ok(!strcmp(mbs, "Th?i"), "mbs is %s\n", mbs);
    if(bUsedDefaultChar) ok(*bUsedDefaultChar == TRUE, "bUsedDefaultChar is %d\n", *bUsedDefaultChar);
    ok(GetLastError() == 0xdeadbeef, "GetLastError() is %u\n", GetLastError());
    ZeroMemory(mbs, 5);

    /* Now this shouldn't be the case like above as we zeroed the complete string buffer. */
    SetLastError(0xdeadbeef);
    ret = WideCharToMultiByte(1252, 0, wcs, 3, mbs, sizeof(mbs), NULL, bUsedDefaultChar);
    ok(ret == 3, "ret is %d\n", ret);
    ok(!strcmp(mbs, "Th?"), "mbs is %s\n", mbs);
    if(bUsedDefaultChar) ok(*bUsedDefaultChar == TRUE, "bUsedDefaultChar is %d\n", *bUsedDefaultChar);
    ok(GetLastError() == 0xdeadbeef, "GetLastError() is %u\n", GetLastError());

    /* Double-byte tests */
    ret = WideCharToMultiByte(1252, 0, dbwcs, 3, mbs, sizeof(mbs), NULL, bUsedDefaultChar);
    ok(ret == 3, "ret is %d\n", ret);
    ok(!strcmp(mbs, "??"), "mbs is %s\n", mbs);
    if(bUsedDefaultChar) ok(*bUsedDefaultChar == TRUE, "bUsedDefaultChar is %d\n", *bUsedDefaultChar);

    ret = WideCharToMultiByte(936, WC_COMPOSITECHECK, dbwcs2, -1, mbs, sizeof(mbs), (const char *)default_char, bUsedDefaultChar);
    ok(ret == 10, "ret is %d\n", ret);
    ok(!strcmp(mbs, "\xf3\xe7\x3d\xa3\xbf\xa3\xbf\xa3\xbf"), "mbs is %s\n", mbs);
    if(bUsedDefaultChar) ok(*bUsedDefaultChar == TRUE, "bUsedDefaultChar is %d\n", *bUsedDefaultChar);

    /* Length-only tests */
    SetLastError(0xdeadbeef);
    ret = WideCharToMultiByte(1252, 0, &wc2, 1, NULL, 0, NULL, bUsedDefaultChar);
    ok(ret == 1, "ret is %d\n", ret);
    if(bUsedDefaultChar) ok(*bUsedDefaultChar == TRUE, "bUsedDefaultChar is %d\n", *bUsedDefaultChar);
    ok(GetLastError() == 0xdeadbeef, "GetLastError() is %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = WideCharToMultiByte(1252, 0, wcs, -1, NULL, 0, NULL, bUsedDefaultChar);
    ok(ret == 5, "ret is %d\n", ret);
    if(bUsedDefaultChar) ok(*bUsedDefaultChar == TRUE, "bUsedDefaultChar is %d\n", *bUsedDefaultChar);
    ok(GetLastError() == 0xdeadbeef, "GetLastError() is %u\n", GetLastError());

    if (!IsValidCodePage(950))
    {
        skip("Codepage 950 not available\n");
        return;
    }

    /* Double-byte tests */
    SetLastError(0xdeadbeef);
    ret = WideCharToMultiByte(950, 0, dbwcs, -1, mbs, sizeof(mbs), NULL, bUsedDefaultChar);
    ok(ret == 5, "ret is %d\n", ret);
    ok(!strcmp(mbs, "\xb5H\xa9\xd2"), "mbs is %s\n", mbs);
    if(bUsedDefaultChar) ok(*bUsedDefaultChar == FALSE, "bUsedDefaultChar is %d\n", *bUsedDefaultChar);
    ok(GetLastError() == 0xdeadbeef, "GetLastError() is %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = WideCharToMultiByte(950, 0, dbwcs, 1, &mbc, 1, NULL, bUsedDefaultChar);
    ok(ret == 0, "ret is %d\n", ret);
    if(bUsedDefaultChar) ok(*bUsedDefaultChar == FALSE, "bUsedDefaultChar is %d\n", *bUsedDefaultChar);
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER, "GetLastError() is %u\n", GetLastError());
    ZeroMemory(mbs, 5);

    SetLastError(0xdeadbeef);
    ret = WideCharToMultiByte(950, 0, dbwcs, 1, mbs, sizeof(mbs), NULL, bUsedDefaultChar);
    ok(ret == 2, "ret is %d\n", ret);
    ok(!strcmp(mbs, "\xb5H"), "mbs is %s\n", mbs);
    if(bUsedDefaultChar) ok(*bUsedDefaultChar == FALSE, "bUsedDefaultChar is %d\n", *bUsedDefaultChar);
    ok(GetLastError() == 0xdeadbeef, "GetLastError() is %u\n", GetLastError());

    /* Length-only tests */
    SetLastError(0xdeadbeef);
    ret = WideCharToMultiByte(950, 0, dbwcs, 1, NULL, 0, NULL, bUsedDefaultChar);
    ok(ret == 2, "ret is %d\n", ret);
    if(bUsedDefaultChar) ok(*bUsedDefaultChar == FALSE, "bUsedDefaultChar is %d\n", *bUsedDefaultChar);
    ok(GetLastError() == 0xdeadbeef, "GetLastError() is %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = WideCharToMultiByte(950, 0, dbwcs, -1, NULL, 0, NULL, bUsedDefaultChar);
    ok(ret == 5, "ret is %d\n", ret);
    if(bUsedDefaultChar) ok(*bUsedDefaultChar == FALSE, "bUsedDefaultChar is %d\n", *bUsedDefaultChar);
    ok(GetLastError() == 0xdeadbeef, "GetLastError() is %u\n", GetLastError());
}