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
typedef  int /*<<< orphan*/  val ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int ERROR_BAD_ARGUMENTS ; 
 int ERROR_INTERNET_BAD_OPTION_LENGTH ; 
 int GetLastError () ; 
 int /*<<< orphan*/  INTERNET_OPTION_MAX_CONNS_PER_1_0_SERVER ; 
 int /*<<< orphan*/  INTERNET_OPTION_MAX_CONNS_PER_SERVER ; 
 int InternetQueryOptionA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int*) ; 
 int InternetSetOptionA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  trace (char*,int) ; 

__attribute__((used)) static void test_max_conns(void)
{
    DWORD len, val;
    BOOL res;

    len = sizeof(val);
    val = 0xdeadbeef;
    res = InternetQueryOptionA(NULL, INTERNET_OPTION_MAX_CONNS_PER_SERVER, &val, &len);
    ok(res,"Got wrong return value %x\n", res);
    ok(len == sizeof(val), "got %d\n", len);
    trace("INTERNET_OPTION_MAX_CONNS_PER_SERVER: %d\n", val);

    len = sizeof(val);
    val = 0xdeadbeef;
    res = InternetQueryOptionA(NULL, INTERNET_OPTION_MAX_CONNS_PER_1_0_SERVER, &val, &len);
    ok(res,"Got wrong return value %x\n", res);
    ok(len == sizeof(val), "got %d\n", len);
    trace("INTERNET_OPTION_MAX_CONNS_PER_1_0_SERVER: %d\n", val);

    val = 3;
    res = InternetSetOptionA(NULL, INTERNET_OPTION_MAX_CONNS_PER_SERVER, &val, sizeof(val));
    ok(res, "InternetSetOptionA(INTERNET_OPTION_MAX_CONNS_PER_SERVER) failed: %x\n", res);

    len = sizeof(val);
    val = 0xdeadbeef;
    res = InternetQueryOptionA(NULL, INTERNET_OPTION_MAX_CONNS_PER_SERVER, &val, &len);
    ok(res,"Got wrong return value %x\n", res);
    ok(len == sizeof(val), "got %d\n", len);
    ok(val == 3, "got %d\n", val);

    val = 0;
    res = InternetSetOptionA(NULL, INTERNET_OPTION_MAX_CONNS_PER_SERVER, &val, sizeof(val));
    ok(!res || broken(res), /* <= w2k3 */
       "InternetSetOptionA(INTERNET_OPTION_MAX_CONNS_PER_SERVER, 0) succeeded\n");
    if (!res) ok(GetLastError() == ERROR_BAD_ARGUMENTS, "GetLastError() = %u\n", GetLastError());

    val = 2;
    res = InternetSetOptionA(NULL, INTERNET_OPTION_MAX_CONNS_PER_SERVER, &val, sizeof(val)-1);
    ok(!res, "InternetSetOptionA(INTERNET_OPTION_MAX_CONNS_PER_SERVER) succeeded\n");
    ok(GetLastError() == ERROR_INTERNET_BAD_OPTION_LENGTH, "GetLastError() = %u\n", GetLastError());

    val = 2;
    res = InternetSetOptionA(NULL, INTERNET_OPTION_MAX_CONNS_PER_SERVER, &val, sizeof(val)+1);
    ok(!res, "InternetSetOptionA(INTERNET_OPTION_MAX_CONNS_PER_SERVER) succeeded\n");
    ok(GetLastError() == ERROR_INTERNET_BAD_OPTION_LENGTH, "GetLastError() = %u\n", GetLastError());
}