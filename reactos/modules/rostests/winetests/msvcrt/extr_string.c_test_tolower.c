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
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int EILSEQ ; 
 int /*<<< orphan*/  LCMAP_LOWERCASE ; 
 int LCMapStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  MB_ERR_INVALID_CHARS ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int) ; 
 int WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ broken (int) ; 
 int errno ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int p_tolower (int) ; 
 int /*<<< orphan*/ * setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_tolower(void)
{
    WCHAR chw, lower;
    char ch, lch;
    int ret, len;

    /* test C locale when locale was never changed */
    ret = p_tolower(0x41);
    ok(ret == 0x61, "ret = %x\n", ret);

    ret = p_tolower(0xF4);
    ok(ret == 0xF4, "ret = %x\n", ret);

    errno = 0xdeadbeef;
    ret = p_tolower((char)0xF4);
    ok(ret == (char)0xF4, "ret = %x\n", ret);
    ok(errno == 0xdeadbeef, "errno = %d\n", errno);

    errno = 0xdeadbeef;
    ret = p_tolower((char)0xD0);
    ok(ret == (char)0xD0, "ret = %x\n", ret);
    ok(errno == 0xdeadbeef, "errno = %d\n", errno);

    setlocale(LC_ALL, "C");
    errno = 0xdeadbeef;
    ret = p_tolower((char)0xF4);
    ok(ret == (char)0xF4, "ret = %x\n", ret);
    ok(errno == 0xdeadbeef, "errno = %d\n", errno);

    /* test C locale after setting locale */
    if(!setlocale(LC_ALL, "us")) {
        win_skip("skipping tolower tests that depends on locale\n");
        return;
    }
    setlocale(LC_ALL, "C");

    ch = 0xF4;
    errno = 0xdeadbeef;
    ret = p_tolower(ch);
    if(!MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, &ch, 1, &chw, 1) ||
            LCMapStringW(CP_ACP, LCMAP_LOWERCASE, &chw, 1, &lower, 1) != 1 ||
            (len = WideCharToMultiByte(CP_ACP, 0, &lower, 1, &lch, 1, NULL, NULL)) != 1)
        len = 0;
    if(len)
        ok(ret==(unsigned char)lch || broken(ret==ch)/*WinXP-*/, "ret = %x\n", ret);
    else
        ok(ret == ch, "ret = %x\n", ret);
    if(!len || ret==(unsigned char)lch)
        ok(errno == EILSEQ, "errno = %d\n", errno);

    ch = 0xD0;
    errno = 0xdeadbeef;
    ret = p_tolower(ch);
    if(!MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, &ch, 1, &chw, 1) ||
            LCMapStringW(CP_ACP, LCMAP_LOWERCASE, &chw, 1, &lower, 1) != 1 ||
            (len = WideCharToMultiByte(CP_ACP, 0, &lower, 1, &lch, 1, NULL, NULL)) != 1)
        len = 0;
    if(len)
        ok(ret==(unsigned char)lch || broken(ret==ch)/*WinXP-*/, "ret = %x\n", ret);
    else
        ok(ret == ch, "ret = %x\n", ret);
    if(!len || ret==(unsigned char)lch)
        ok(errno == EILSEQ, "errno = %d\n", errno);

    ret = p_tolower(0xD0);
    ok(ret == 0xD0, "ret = %x\n", ret);

    ok(setlocale(LC_ALL, "us") != NULL, "setlocale failed\n");

    ret = p_tolower((char)0xD0);
    ok(ret == 0xF0, "ret = %x\n", ret);

    ret = p_tolower(0xD0);
    ok(ret == 0xF0, "ret = %x\n", ret);

    setlocale(LC_ALL, "C");
}