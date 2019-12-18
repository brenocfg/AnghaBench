#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  e ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_4__ {char* szMachineName; char* szObjectName; char* szInstanceName; char* szParentInstance; int dwInstanceIndex; char* szCounterName; } ;
typedef  char* PDH_STATUS ;
typedef  TYPE_1__ PDH_COUNTER_PATH_ELEMENTS_A ;
typedef  int DWORD ;

/* Variables and functions */
 char* ERROR_SUCCESS ; 
 char* PDH_INVALID_ARGUMENT ; 
 char* PdhMakeCounterPathA (TYPE_1__*,char*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void test_PdhMakeCounterPathA(void)
{
    PDH_STATUS ret;
    PDH_COUNTER_PATH_ELEMENTS_A e;
    char buffer[1024];
    DWORD buflen;

    ret = PdhMakeCounterPathA(NULL, NULL, NULL, 0);
    ok(ret == PDH_INVALID_ARGUMENT, "PdhMakeCounterPathA failed 0x%08x\n", ret);

    buflen = 0;
    ret = PdhMakeCounterPathA(NULL, NULL, &buflen, 0);
    ok(ret == PDH_INVALID_ARGUMENT, "PdhMakeCounterPathA failed 0x%08x\n", ret);

    buflen = 0;
    ret = PdhMakeCounterPathA(NULL, buffer, &buflen, 0);
    ok(ret == PDH_INVALID_ARGUMENT, "PdhMakeCounterPathA failed 0x%08x\n", ret);

    buflen = sizeof(buffer);
    memset(&e, 0, sizeof(e));
    ret = PdhMakeCounterPathA(&e, buffer, &buflen, 0);
    ok(ret == PDH_INVALID_ARGUMENT, "PdhMakeCounterPathA failed 0x%08x\n", ret);

    buffer[0] = 0;
    buflen = sizeof(buffer);
    e.szMachineName = (char *)"machine";
    ret = PdhMakeCounterPathA(&e, buffer, &buflen, 0);
    ok(ret == PDH_INVALID_ARGUMENT, "PdhMakeCounterPathA failed 0x%08x\n", ret);
    ok(!strcmp(buffer, ""), "expected \"machine\" got %s\n", buffer);

    buffer[0] = 0;
    buflen = sizeof(buffer);
    e.szObjectName = (char *)"object";
    ret = PdhMakeCounterPathA(&e, buffer, &buflen, 0);
    ok(ret == PDH_INVALID_ARGUMENT, "PdhMakeCounterPathA failed 0x%08x\n", ret);
    ok(!strcmp(buffer, ""), "expected \"machine\" got %s\n", buffer);

    buffer[0] = 0;
    buflen = sizeof(buffer);
    e.szInstanceName = (char *)"instance";
    ret = PdhMakeCounterPathA(&e, buffer, &buflen, 0);
    ok(ret == PDH_INVALID_ARGUMENT, "PdhMakeCounterPathA failed 0x%08x\n", ret);
    ok(!strcmp(buffer, ""), "expected \"machine\" got %s\n", buffer);

    buffer[0] = 0;
    buflen = sizeof(buffer);
    e.szParentInstance = (char *)"parent";
    ret = PdhMakeCounterPathA(&e, buffer, &buflen, 0);
    ok(ret == PDH_INVALID_ARGUMENT, "PdhMakeCounterPathA failed 0x%08x\n", ret);
    ok(!strcmp(buffer, ""), "expected \"machine\" got %s\n", buffer);

    buffer[0] = 0;
    buflen = sizeof(buffer);
    e.dwInstanceIndex = 1;
    ret = PdhMakeCounterPathA(&e, buffer, &buflen, 0);
    ok(ret == PDH_INVALID_ARGUMENT, "PdhMakeCounterPathA failed 0x%08x\n", ret);
    ok(!strcmp(buffer, ""), "expected \"machine\" got %s\n", buffer);

    buffer[0] = 0;
    buflen = sizeof(buffer);
    e.szCounterName = (char *)"counter";
    ret = PdhMakeCounterPathA(&e, buffer, &buflen, 0);
    ok(ret == ERROR_SUCCESS, "PdhMakeCounterPathA failed 0x%08x\n", ret);
    ok(!strcmp(buffer, "\\\\machine\\object(parent/instance#1)\\counter"),
       "expected \"\\\\machine\\object(parent/instance#1)\\counter\" got %s\n", buffer);

    buffer[0] = 0;
    buflen = sizeof(buffer);
    e.szParentInstance = NULL;
    ret = PdhMakeCounterPathA(&e, buffer, &buflen, 0);
    ok(ret == ERROR_SUCCESS, "PdhMakeCounterPathA failed 0x%08x\n", ret);
    ok(!strcmp(buffer, "\\\\machine\\object(instance#1)\\counter"),
       "expected \"\\\\machine\\object(instance#1)\\counter\" got %s\n", buffer);

    buffer[0] = 0;
    buflen = sizeof(buffer);
    e.szInstanceName = NULL;
    ret = PdhMakeCounterPathA(&e, buffer, &buflen, 0);
    ok(ret == ERROR_SUCCESS, "PdhMakeCounterPathA failed 0x%08x\n", ret);
    ok(!strcmp(buffer, "\\\\machine\\object\\counter"),
       "expected \"\\\\machine\\object\\counter\" got %s\n", buffer);

    buffer[0] = 0;
    buflen = sizeof(buffer);
    e.szMachineName = NULL;
    ret = PdhMakeCounterPathA(&e, buffer, &buflen, 0);
    ok(ret == ERROR_SUCCESS, "PdhMakeCounterPathA failed 0x%08x\n", ret);
    ok(!strcmp(buffer, "\\object\\counter"),
       "expected \"\\object\\counter\" got %s\n", buffer);

    buffer[0] = 0;
    buflen = sizeof(buffer);
    e.szObjectName = NULL;
    ret = PdhMakeCounterPathA(&e, buffer, &buflen, 0);
    ok(ret == PDH_INVALID_ARGUMENT, "PdhMakeCounterPathA failed 0x%08x\n", ret);
}