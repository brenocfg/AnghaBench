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
typedef  int /*<<< orphan*/  strW ;
typedef  int /*<<< orphan*/  strA ;
typedef  int /*<<< orphan*/  buf ;
typedef  char WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (char*,char const*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_overlapped_buffers(void)
{
    static const WCHAR strW[] = {'j','u','s','t',' ','a',' ','t','e','s','t',0};
    static const char strA[] = "just a test";
    char buf[256];
    int ret;

    SetLastError(0xdeadbeef);
    memcpy(buf + 1, strW, sizeof(strW));
    ret = WideCharToMultiByte(CP_ACP, 0, (WCHAR *)(buf + 1), -1, buf, sizeof(buf), NULL, NULL);
    ok(ret == sizeof(strA), "unexpected ret %d\n", ret);
    ok(!memcmp(buf, strA, sizeof(strA)), "conversion failed: %s\n", buf);
    ok(GetLastError() == 0xdeadbeef, "GetLastError() is %u\n", GetLastError());
}