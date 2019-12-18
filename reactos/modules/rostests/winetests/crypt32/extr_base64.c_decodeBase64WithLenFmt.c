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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  size_t DWORD ;
typedef  scalar_t__ BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CryptStringToBinaryA (int /*<<< orphan*/ ,int,size_t,scalar_t__*,size_t*,int /*<<< orphan*/ *,size_t*) ; 
 int GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  decodeBase64WithLenFmtW (int /*<<< orphan*/ ,int,size_t,scalar_t__,scalar_t__*,size_t,size_t) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,int,...) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void decodeBase64WithLenFmt(LPCSTR str, int len, DWORD fmt, LPCSTR expected, int le, BOOL isBroken)
{
    BYTE buf[8] = {0};
    DWORD bufLen = sizeof(buf)-1, fmtUsed = 0xdeadbeef;
    BOOL ret;
    SetLastError(0xdeadbeef);
    ret = CryptStringToBinaryA(str, len, fmt, buf, &bufLen, NULL, &fmtUsed);
    buf[bufLen] = 0;
    if (expected) {
        BOOL correct = ret && strcmp(expected, (char*)buf) == 0;
        ok(correct || (isBroken && broken(!ret)),
         "base64 \"%s\" len %d: expected \"%s\", got \"%s\" (ret %d, le %d)\n",
         str, len, expected, (char*)buf, ret, GetLastError());
        if (correct)
            ok(fmtUsed == fmt, "base64 \"%s\" len %d: expected fmt %d, used %d\n",
             str, len, fmt, fmtUsed);
    } else {
        ok(!ret && GetLastError() == le,
         "base64 \"%s\" len %d: expected failure, got \"%s\" (ret %d, le %d)\n",
         str, len, (char*)buf, ret, GetLastError());
    }

    decodeBase64WithLenFmtW(str, len, fmt, ret, buf, bufLen, fmtUsed);
}