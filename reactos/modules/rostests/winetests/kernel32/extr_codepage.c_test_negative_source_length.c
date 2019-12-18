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
typedef  int /*<<< orphan*/  bufW ;
typedef  int /*<<< orphan*/  buf ;
typedef  char WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int ERROR_INSUFFICIENT_BUFFER ; 
 int GetLastError () ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  foobarW ; 
 int /*<<< orphan*/  lstrcmpA (char*,char*) ; 
 int /*<<< orphan*/  lstrcmpW (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_negative_source_length(void)
{
    int len;
    char buf[10];
    WCHAR bufW[10];

    /* Test, whether any negative source length works as strlen() + 1 */
    SetLastError( 0xdeadbeef );
    memset(buf,'x',sizeof(buf));
    len = WideCharToMultiByte(CP_ACP, 0, foobarW, -2002, buf, 10, NULL, NULL);
    ok(len == 7 && GetLastError() == 0xdeadbeef,
       "WideCharToMultiByte(-2002): len=%d error=%u\n", len, GetLastError());
    ok(!lstrcmpA(buf, "foobar"),
       "WideCharToMultiByte(-2002): expected \"foobar\" got \"%s\"\n", buf);

    SetLastError( 0xdeadbeef );
    memset(bufW,'x',sizeof(bufW));
    len = MultiByteToWideChar(CP_ACP, 0, "foobar", -2002, bufW, 10);
    ok(len == 7 && !lstrcmpW(bufW, foobarW) && GetLastError() == 0xdeadbeef,
       "MultiByteToWideChar(-2002): len=%d error=%u\n", len, GetLastError());

    SetLastError(0xdeadbeef);
    memset(bufW, 'x', sizeof(bufW));
    len = MultiByteToWideChar(CP_ACP, 0, "foobar", -1, bufW, 6);
    ok(len == 0 && GetLastError() == ERROR_INSUFFICIENT_BUFFER,
       "MultiByteToWideChar(-1): len=%d error=%u\n", len, GetLastError());
}