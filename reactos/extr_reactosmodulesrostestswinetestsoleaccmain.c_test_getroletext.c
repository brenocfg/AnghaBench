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
typedef  int /*<<< orphan*/  buff2W ;
typedef  int /*<<< orphan*/  buff2 ;
typedef  char WCHAR ;
typedef  int INT ;
typedef  char CHAR ;

/* Variables and functions */
 int ARRAY_SIZE (char*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int GetRoleTextA (int,char*,int) ; 
 int GetRoleTextW (int,char*,int) ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int ROLE_SYSTEM_OUTLINEBUTTON ; 
 int ROLE_SYSTEM_TITLEBAR ; 
 scalar_t__ broken (int) ; 
 int lstrlenA (char*) ; 
 int lstrlenW (char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_getroletext(void)
{
    INT ret, role;
    CHAR buf[2], *buff;
    WCHAR bufW[2], *buffW;

    /* wrong role number */
    ret = GetRoleTextA(-1, NULL, 0);
    ok(ret == 0, "GetRoleTextA doesn't return zero on wrong role number, got %d\n", ret);
    buf[0] = '*';
    ret = GetRoleTextA(-1, buf, 2);
    ok(ret == 0, "GetRoleTextA doesn't return zero on wrong role number, got %d\n", ret);
    ok(buf[0] == 0, "GetRoleTextA doesn't return NULL char on wrong role number\n");
    buf[0] = '*';
    ret = GetRoleTextA(-1, buf, 0);
    ok(ret == 0, "GetRoleTextA doesn't return zero on wrong role number, got %d\n", ret);
    ok(buf[0] == '*', "GetRoleTextA modified buffer on wrong role number\n");

    ret = GetRoleTextW(-1, NULL, 0);
    ok(ret == 0, "GetRoleTextW doesn't return zero on wrong role number, got %d\n", ret);
    bufW[0] = '*';
    ret = GetRoleTextW(-1, bufW, 2);
    ok(ret == 0, "GetRoleTextW doesn't return zero on wrong role number, got %d\n", ret);
    ok(bufW[0] == '\0', "GetRoleTextW doesn't return NULL char on wrong role number\n");
    bufW[0] = '*';
    ret = GetRoleTextW(-1, bufW, 0);
    ok(ret == 0, "GetRoleTextW doesn't return zero on wrong role number, got %d\n", ret);

    /* zero role number - not documented */
    ret = GetRoleTextA(0, NULL, 0);
    ok(ret > 0, "GetRoleTextA doesn't return (>0) for zero role number, got %d\n", ret);
    ret = GetRoleTextW(0, NULL, 0);
    ok(ret > 0, "GetRoleTextW doesn't return (>0) for zero role number, got %d\n", ret);

    /* NULL buffer, return length */
    ret = GetRoleTextA(ROLE_SYSTEM_TITLEBAR, NULL, 0);
    ok(ret > 0, "GetRoleTextA doesn't return length on NULL buffer, got %d\n", ret);
    ret = GetRoleTextA(ROLE_SYSTEM_TITLEBAR, NULL, 1);
    ok(ret > 0, "GetRoleTextA doesn't return length on NULL buffer, got %d\n", ret);
    ret = GetRoleTextW(ROLE_SYSTEM_TITLEBAR, NULL, 0);
    ok(ret > 0, "GetRoleTextW doesn't return length on NULL buffer, got %d\n", ret);
    ret = GetRoleTextW(ROLE_SYSTEM_TITLEBAR, NULL, 1);
    ok(ret > 0, "GetRoleTextW doesn't return length on NULL buffer, got %d\n", ret);

    /* use a smaller buffer */
    bufW[0] = '*';
    ret = GetRoleTextA(ROLE_SYSTEM_TITLEBAR, buf, 0);
    ok(!ret, "GetRoleTextA doesn't return 0, got %d\n", ret);
    ok(buf[0] == '*', "GetRoleTextA modified buffer\n");
    buffW = NULL;
    ret = GetRoleTextW(ROLE_SYSTEM_TITLEBAR, (WCHAR*)&buffW, 0);
    ok(ret, "GetRoleTextW doesn't return length\n");
    ok(buffW != NULL, "GetRoleTextW doesn't modify buffer\n");
    buf[0] = '*';
    ret = GetRoleTextA(ROLE_SYSTEM_TITLEBAR, buf, 1);
    ok(ret == 0, "GetRoleTextA returned wrong length\n");
    ok(buf[0] == '\0', "GetRoleTextA returned not zero-length buffer\n");
    buf[0] = '*';
    ret = GetRoleTextA(ROLE_SYSTEM_TITLEBAR, buf, 2);
    ok(!ret, "GetRoleTextA returned wrong length, got %d, expected 0\n", ret);
    ok(!buf[0] || broken(buf[0]!='*') /* WinXP */,
            "GetRoleTextA returned not zero-length buffer : (%c)\n", buf[0]);

    bufW[0] = '*';
    ret = GetRoleTextW(ROLE_SYSTEM_TITLEBAR, bufW, 1);
    ok(ret == 0, "GetRoleTextW returned wrong length, got %d, expected 1\n", ret);
    ok(bufW[0] == '\0', "GetRoleTextW returned not zero-length buffer\n");
    bufW[1] = '*';
    ret = GetRoleTextW(ROLE_SYSTEM_TITLEBAR, bufW, 2);
    ok(ret == 1, "GetRoleTextW returned wrong length, got %d, expected 1\n", ret);
    ok(bufW[1] == '\0', "GetRoleTextW returned not zero-length buffer\n");

    /* use bigger buffer */
    ret = GetRoleTextA(ROLE_SYSTEM_TITLEBAR, NULL, 0);
    buff = HeapAlloc(GetProcessHeap(), 0, 2*ret);
    buff[2*ret-1] = '*';
    ret = GetRoleTextA(ROLE_SYSTEM_TITLEBAR, buff, 2*ret);
    ok(buff[2*ret-1] == '*', "GetRoleTextA shouldn't modify this part of buffer\n");
    HeapFree(GetProcessHeap(), 0, buff);

    ret = GetRoleTextW(ROLE_SYSTEM_TITLEBAR, NULL, 0);
    buffW = HeapAlloc(GetProcessHeap(), 0, 2*ret*sizeof(WCHAR));
    buffW[2*ret-1] = '*';
    ret = GetRoleTextW(ROLE_SYSTEM_TITLEBAR, buffW, 2*ret);
    ok(buffW[2*ret-1] == '*', "GetRoleTextW shouldn't modify this part of buffer\n");
    HeapFree(GetProcessHeap(), 0, buffW);

    /* check returned length for all roles */
    for(role = 0; role <= ROLE_SYSTEM_OUTLINEBUTTON; role++){
        CHAR buff2[100];
        WCHAR buff2W[100];

        /* NT4 and W2K don't clear the buffer on a nonexistent role in the A-call */
        memset(buff2, 0, sizeof(buff2));

        ret = GetRoleTextA(role, NULL, 0);
        ok(ret > 0, "Expected the role to be present\n");

        GetRoleTextA(role, buff2, sizeof(buff2));
        ok(ret == lstrlenA(buff2),
           "GetRoleTextA: returned length doesn't match returned buffer for role %d\n", role);

        /* Win98 and WinMe don't clear the buffer on a nonexistent role in the W-call */
        memset(buff2W, 0, sizeof(buff2W));

        ret = GetRoleTextW(role, NULL, 0);
        GetRoleTextW(role, buff2W, ARRAY_SIZE(buff2W));
        ok(ret == lstrlenW(buff2W),
           "GetRoleTextW: returned length doesn't match returned buffer for role %d\n", role);
    }
}